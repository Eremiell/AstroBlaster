#include "inc/enemy.hpp"
#include <string>
#include <SFML/System/Clock.hpp>
#include "inc/utility.hpp"

namespace astroblaster {
	Enemy::Enemy(sf::RenderWindow &window, TextureManager &tm, MainState &state, AI_TYPE type) : window(window), state(state), type(type), up(false), counter(0) {
		std::string texture_name{u8"enemyBlack1.png"};
		switch (this->type) {
			case AI_TYPE::MOVING:
				texture_name = u8"enemyBlue3.png";
				this->energy = 20;
				break;
			case AI_TYPE::RAPID:
				texture_name = u8"enemyRed5.png";
				this->energy = 40;
				break;
			case AI_TYPE::SMART:
				texture_name = u8"enemyGreen2.png";
				this->energy = 60;
				break;
			case AI_TYPE::NORMAL:
			default:
				this->energy = 10;
				break;
		}
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		auto subtexture = tm.get_subtexture(texture_name);
		if (!subtexture.first) {
			throw texture_not_found(texture_name);
		}
		this->sprite.setTexture(*subtexture.first, true);
		this->sprite.setTextureRect(subtexture.second);
		this->sprite.setOrigin(subtexture.second.width / 2, subtexture.second.height / 2);
		this->sprite.setRotation(90);
		this->sprite.setPosition(1000.0f, 400.0f);
	}

	void Enemy::integrate(sf::Vector2<float> player_position) {
		switch (this->type) {
			case AI_TYPE::MOVING:
				this->integrate_moving();
				break;
			case AI_TYPE::RAPID:
				this->integrate_rapid();
				break;
			case AI_TYPE::SMART:
				this->integrate_smart(player_position);
				break;
			case AI_TYPE::NORMAL:
			default:
				this->integrate_normal();
				break;
		}
		return;
	}
	
	void Enemy::render() {
		this->window.draw(this->sprite);
		return;
	}

	sf::Rect<float> Enemy::get_collision_box() const {
		return this->sprite.getGlobalBounds();
	}

	void Enemy::collide_with(unsigned int type) {
		if (type & static_cast<unsigned int>(CollisionType::Projectile)) {
			this->deduce_energy(10);
		}
		return;
	}

	std::size_t Enemy::get_energy() const {
		return this->energy;
	}

	sf::Vector2<float> Enemy::weapon_position() const {
		auto bounds = this->sprite.getGlobalBounds();
		return sf::Vector2<float>{bounds.left - 5.0f, bounds.top + bounds.height / 2};
	}

	void Enemy::integrate_normal() {
		static sf::Clock weapon_clock;
		this->sprite.move(-speed, 0.0f);
		if (weapon_clock.getElapsedTime().asSeconds() > 0.5f) {
			weapon_clock.restart();
			this->state.emplace_projectile(this->weapon_position(), false);
		}
		return;
	}

	void Enemy::integrate_moving() {
		static sf::Clock weapon_clock;
		this->sprite.move(-speed, this->up?-5.0f:5.0f);
		++this->counter;
		if (this->counter == 20u) {
			this->up = !this->up;
			this->counter = 0u;
		}
		if (weapon_clock.getElapsedTime().asSeconds() > 0.5f) {
			weapon_clock.restart();
			this->state.emplace_projectile(this->weapon_position(), false);
		}
		return;
	}

	void Enemy::integrate_rapid() {
		static sf::Clock weapon_clock;
		this->sprite.move(-speed, this->up?-10.0f:10.0f);
		if (this->up && this->sprite.getGlobalBounds().top < 10.0f) {
			this->up = false;
		}
		else if (!this->up && this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height > height - 10.0f) {
			this->up = true;
		}
		if (weapon_clock.getElapsedTime().asSeconds() > 0.3f) {
			weapon_clock.restart();
			this->state.emplace_projectile(this->weapon_position(), false);
		}
		return;
	}

	void Enemy::integrate_smart(sf::Vector2<float> player_position) {
		static sf::Clock weapon_clock;
		float follow{0.0f};
		if (this->weapon_position().y - player_position.y > 25.0f) {
			follow = -5.0f;
		}
		else if (this->weapon_position().y - player_position.y < -25.0f) {
			follow = 5.0f;
		}
		this->sprite.move(-speed, follow);
		if (weapon_clock.getElapsedTime().asSeconds() > 0.4f) {
			weapon_clock.restart();
			this->state.emplace_projectile(this->weapon_position(), false);
		}
		return;
	}

	void Enemy::deduce_energy(std::size_t damage) {
		if (this->energy > damage) {
			this->energy -= damage;
		}
		else {
			this->energy = 0u;
		}
		return;
	}
}