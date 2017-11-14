#include "inc/enemy.hpp"
#include <string>
#include <SFML/System/Clock.hpp>
#include "inc/utility.hpp"

namespace astroblaster {
	Enemy::Enemy(sf::RenderWindow &window, TextureManager &tm, MainState &state, AI_TYPE type) : window(window), state(state), type(type), energy(10) {
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		std::string texture_name = u8"enemyBlack3.png";
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

	void Enemy::integrate() {
		if (this->type == AI_TYPE::NORMAL) {
			this->integrate_normal();
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