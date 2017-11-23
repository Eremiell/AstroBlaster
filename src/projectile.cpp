#include "inc/projectile.hpp"
#include <string>
#include "inc/utility.hpp"

namespace astroblaster {
	Projectile::Projectile(sf::RenderWindow &window, TextureManager &tm, sf::Vector2<float> position, bool direction, std::size_t source) : window(window), direction(direction), source(source) {
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		std::string texture_name = u8"laserGreen05.png";
		if (!direction) {
			texture_name = u8"laserRed03.png";
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

	void Projectile::integrate() {
		if (this->direction) {
			this->sprite.move(speed * 2, 0.0f);
		}
		else {
			this->sprite.move(-speed * 2, 0.0f);
		}
		return;
	}

	void Projectile::render() {
		this->window.draw(this->sprite);
		return;
	}

	bool Projectile::get_direction() const {
		return this->direction;
	}

	std::size_t Projectile::get_source() const {
		return this->source;
	}

	sf::Rect<float> Projectile::get_collision_box() {
		return this->sprite.getGlobalBounds();
	}
}