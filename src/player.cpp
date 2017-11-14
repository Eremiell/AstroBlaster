#include "inc/player.hpp"
#include <cmath>
#include "inc/utility.hpp"

namespace astroblaster {
	Player::Player(sf::RenderWindow &window, TextureManager &tm) : window(window), energy(100) {
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		auto subtexture = tm.get_subtexture(u8"playerShip1_red.png");
		if (!subtexture.first) {
			throw texture_not_found(u8"playerShip1_red.png");
		}
		this->sprite.setTexture(*subtexture.first, true);
		this->sprite.setTextureRect(subtexture.second);
		this->sprite.setOrigin(subtexture.second.width / 2, subtexture.second.height / 2);
		this->sprite.setRotation(90);
		this->sprite.setPosition(600.0f, 400.0f);
	}

	void Player::integrate(unsigned int controls) {
		sf::Vector2<float> movement(0.0f, 0.0f);
		if ((controls & static_cast<unsigned int>(Controls::Up)) && !(controls & static_cast<unsigned int>(Controls::Down))) {
			movement.y -= 1.0f;
		}
		else if ((controls & static_cast<unsigned int>(Controls::Down)) && !(controls & static_cast<unsigned int>(Controls::Up))) {
			movement.y += 1.0f;
		}
		if ((controls & static_cast<unsigned int>(Controls::Left)) && !(controls & static_cast<unsigned int>(Controls::Right))) {
			movement.x -= 1.0f;
		}
		else if ((controls & static_cast<unsigned int>(Controls::Right)) && !(controls & static_cast<unsigned int>(Controls::Left))) {
			movement.x += 1.0f;
		}
		if ((std::fabs(movement.x) > 0.001f) && (std::fabs(movement.y) > 0.001f)) {
			movement.x *= std::sqrt(speed * speed / 2);
			movement.y *= std::sqrt(speed * speed / 2);
		}
		else {
			movement.x *= speed;
			movement.y *= speed;
		}
		this->sprite.move(movement);
		this->collide_against_bounds();
		return;
	}

	void Player::render() {
		this->window.draw(this->sprite);
		return;
	}

	sf::Rect<float> Player::get_collision_box() const {
		return this->sprite.getGlobalBounds();
	}

	void Player::collide_with(unsigned int type) {
		if (type & static_cast<unsigned int>(CollisionType::Enemy)) {
			this->deduce_energy(20);
		}
		else if (type & static_cast<unsigned int>(CollisionType::Projectile)) {
			this->deduce_energy(10);
		}
		return;
	}

	std::size_t Player::get_energy() const {
		return this->energy;
	}

	sf::Vector2<float> Player::weapon_position() const {
		auto bounds = this->sprite.getGlobalBounds();
		return sf::Vector2<float>{bounds.left + bounds.width + 5.0f, bounds.top + bounds.height / 2};
	}

	void Player::collide_against_bounds() {
		sf::Rect<float> boundary{0.0f - 2 * speed, 0.0f - 2 * speed, width + 4 * speed, 2 * speed};
		sf::Rect<float> intersection;
		if (this->sprite.getGlobalBounds().intersects(boundary, intersection)) {
			this->sprite.move(0.0f, intersection.height);
		}
		boundary.top = height;
		if (this->sprite.getGlobalBounds().intersects(boundary, intersection)) {
			this->sprite.move(0.0f, -intersection.height);
		}
		boundary.top = 0.0f - 2 * speed;
		boundary.width = 2 * speed;
		boundary.height = height + 4 * speed;
		if (this->sprite.getGlobalBounds().intersects(boundary, intersection)) {
			this->sprite.move(intersection.width, 0.0f);
		}
		boundary.left = width;
		if (this->sprite.getGlobalBounds().intersects(boundary, intersection)) {
			this->sprite.move(-intersection.width, 0.0f);
		}
		return;
	}

	void Player::deduce_energy(std::size_t damage) {
		if (this->energy > damage) {
			this->energy -= damage;
		}
		else {
			this->energy = 0u;
		}
		return;
	}
}