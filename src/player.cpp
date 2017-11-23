#include "inc/player.hpp"
#include <cmath>
#include "inc/utility.hpp"

namespace astroblaster {
	Player::Player(sf::RenderWindow &window, TextureManager &tm, MainState &state, std::string name, std::size_t number, bool multiplayer) : window(window), state(state), name(name), energy(100u), lives(3u), score(0ull), number(number), multiplayer(multiplayer) {
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		auto subtexture = tm.get_subtexture(u8"playerShip1_" + colours.at(number) + ".png");
		if (!subtexture.first) {
			throw texture_not_found(u8"playerShip1_" + colours.at(number) + ".png");
		}
		this->sprite.setTexture(*subtexture.first, true);
		this->sprite.setTextureRect(subtexture.second);
		this->sprite.setOrigin(subtexture.second.width / 2, subtexture.second.height / 2);
		this->sprite.setRotation(90);
		this->sprite.setPosition(600.0f, 400.0f);
		if (multiplayer) {
			if (number == 1) {
				this->sprite.setPosition(600.0f, 300.0f);
			}
			else {
				this->sprite.setPosition(600.0f, 500.0f);
			}
		}
	}

	void Player::integrate(unsigned int controls) {
		sf::Vector2<float> movement(0.0f, 0.0f);
		if (multiplayer) {
			if (!this->number) {
				if ((controls & static_cast<unsigned int>(Controls::P1Up)) && !(controls & static_cast<unsigned int>(Controls::P1Down))) {
					movement.y -= 1.0f;
				}
				else if ((controls & static_cast<unsigned int>(Controls::P1Down)) && !(controls & static_cast<unsigned int>(Controls::P1Up))) {
					movement.y += 1.0f;
				}
				if ((controls & static_cast<unsigned int>(Controls::P1Left)) && !(controls & static_cast<unsigned int>(Controls::P1Right))) {
					movement.x -= 1.0f;
				}
				else if ((controls & static_cast<unsigned int>(Controls::P1Right)) && !(controls & static_cast<unsigned int>(Controls::P1Left))) {
					movement.x += 1.0f;
				}
				if (controls & static_cast<unsigned int>(Controls::P1Shoot) && this->weapon_cooldown.getElapsedTime().asSeconds() >= 0.1f) {
					this->weapon_cooldown.restart();
					this->state.emplace_projectile(this->weapon_position(), true, this->number);
				}
			}
			else {
				if ((controls & static_cast<unsigned int>(Controls::P2Up)) && !(controls & static_cast<unsigned int>(Controls::P2Down))) {
					movement.y -= 1.0f;
				}
				else if ((controls & static_cast<unsigned int>(Controls::P2Down)) && !(controls & static_cast<unsigned int>(Controls::P2Up))) {
					movement.y += 1.0f;
				}
				if ((controls & static_cast<unsigned int>(Controls::P2Left)) && !(controls & static_cast<unsigned int>(Controls::P2Right))) {
					movement.x -= 1.0f;
				}
				else if ((controls & static_cast<unsigned int>(Controls::P2Right)) && !(controls & static_cast<unsigned int>(Controls::P2Left))) {
					movement.x += 1.0f;
				}
				if (controls & static_cast<unsigned int>(Controls::P2Shoot) && this->weapon_cooldown.getElapsedTime().asSeconds() >= 0.1f) {
					this->weapon_cooldown.restart();
					this->state.emplace_projectile(this->weapon_position(), true, this->number);
				}
			}
		}
		else {
			if ((controls & static_cast<unsigned int>(Controls::P1Up) || controls & static_cast<unsigned int>(Controls::P2Up)) && !(controls & static_cast<unsigned int>(Controls::P1Down) || controls & static_cast<unsigned int>(Controls::P2Down))) {
				movement.y -= 1.0f;
			}
			if ((controls & static_cast<unsigned int>(Controls::P1Down) || controls & static_cast<unsigned int>(Controls::P2Down)) && !(controls & static_cast<unsigned int>(Controls::P1Up) || controls & static_cast<unsigned int>(Controls::P2Up))) {
				movement.y += 1.0f;
			}
			if ((controls & static_cast<unsigned int>(Controls::P1Left) || controls & static_cast<unsigned int>(Controls::P2Left)) && !(controls & static_cast<unsigned int>(Controls::P1Right) || controls & static_cast<unsigned int>(Controls::P2Right))) {
				movement.x -= 1.0f;
			}
			if ((controls & static_cast<unsigned int>(Controls::P1Right) || controls & static_cast<unsigned int>(Controls::P2Right)) && !(controls & static_cast<unsigned int>(Controls::P1Left) || controls & static_cast<unsigned int>(Controls::P2Left))) {
				movement.x += 1.0f;
			}
			if ((controls & static_cast<unsigned int>(Controls::P1Shoot) || controls & static_cast<unsigned int>(Controls::P2Shoot)) && this->weapon_cooldown.getElapsedTime().asSeconds() >= 0.1f) {
				this->weapon_cooldown.restart();
				this->state.emplace_projectile(this->weapon_position(), true, this->number);
			}
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

	std::size_t Player::get_lives() const {
		return this->lives;
	}

	std::uint64_t Player::get_score() const {
		return this->score;
	}

	std::string Player::get_name() const {
		return this->name;
	}

	void Player::add_score(std::size_t score) {
		this->score += score;
		return;
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
			if (this->lives > 1) {
				this->energy = 100u;
			}
			else {
				this->energy = 0u;
			}
			--this->lives;
		}
		return;
	}
}