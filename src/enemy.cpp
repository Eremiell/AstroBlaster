#include "inc/enemy.hpp"
#include <string>
#include "inc/utility.hpp"

namespace astroblaster {
	Enemy::Enemy(sf::RenderWindow &window, TextureManager &tm, MainState &state, sf::Vector2<float> position, AIType type, bool up) : window(window), state(state), type(type), up(up), counter(0), energy(10), score(10) {
		std::string texture_name{u8"enemyBlack1.png"};
		switch (this->type) {
			case AIType::MOVING:
				texture_name = u8"enemyBlue3.png";
				this->energy = 20;
				this->score = 20;
				break;
			case AIType::RAPID:
				texture_name = u8"enemyRed5.png";
				this->energy = 40;
				this->score = 60;
				break;
			case AIType::SMART:
				texture_name = u8"enemyGreen2.png";
				this->energy = 60;
				this->score = 50;
				break;
			case AIType::NORMAL:
			default:
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
		this->sprite.setPosition(position);
	}

	void Enemy::integrate(sf::Vector2<float> player_position) {
		switch (this->type) {
			case AIType::MOVING:
				this->integrate_moving();
				break;
			case AIType::RAPID:
				this->integrate_rapid();
				break;
			case AIType::SMART:
				this->integrate_smart(player_position);
				break;
			case AIType::NORMAL:
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

	std::size_t Enemy::get_score() const {
		return this->score;
	}

	sf::Vector2<float> Enemy::weapon_position() const {
		auto bounds = this->sprite.getGlobalBounds();
		return sf::Vector2<float>{bounds.left - 5.0f, bounds.top + bounds.height / 2};
	}

	void Enemy::integrate_normal() {
		this->sprite.move(-speed, 0.0f);
		if (weapon_clock.getElapsedTime().asSeconds() > 0.5f) {
			weapon_clock.restart();
			this->fire();
		}
		return;
	}

	void Enemy::integrate_moving() {
		this->sprite.move(-speed, this->up?-3.0f:3.0f);
		++this->counter;
		if (this->counter == 50u) {
			this->up = !this->up;
			this->counter = -50u;
		}
		if (weapon_clock.getElapsedTime().asSeconds() > 0.5f) {
			weapon_clock.restart();
			this->fire();
		}
		return;
	}

	void Enemy::integrate_rapid() {
		this->sprite.move(-speed, this->up?-10.0f:10.0f);
		if (this->up && this->sprite.getGlobalBounds().top < 10.0f) {
			this->up = false;
		}
		else if (!this->up && this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height > height - 10.0f) {
			this->up = true;
		}
		if (weapon_clock.getElapsedTime().asSeconds() > 0.3f) {
			weapon_clock.restart();
			this->fire();
		}
		return;
	}

	void Enemy::integrate_smart(sf::Vector2<float> player_position) {
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
			this->fire();
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

	void Enemy::fire() {
		sf::Rect<float> window_box(0.0f, 0.0f, this->window.getSize().x, this->window.getSize().y);
		if (window_box.contains(this->sprite.getPosition())) {
			this->state.emplace_projectile(this->weapon_position(), false);
		}
		return;
	}
}