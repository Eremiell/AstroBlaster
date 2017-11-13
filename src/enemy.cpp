#include "inc/enemy.hpp"
#include "inc/utility.hpp"

namespace astroblaster {
	Enemy::Enemy(sf::RenderWindow &window, TextureManager &tm) : window(window) {
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		auto subtexture = tm.get_subtexture(u8"enemyBlack3.png");
		if (!subtexture.first) {
			throw texture_not_found(u8"enemyBlack3.png");
		}
		this->sprite.setTexture(*subtexture.first, true);
		this->sprite.setTextureRect(subtexture.second);
		this->sprite.setOrigin(subtexture.second.width / 2, subtexture.second.height / 2);
		this->sprite.setRotation(90);
		this->sprite.setPosition(1000.0f, 400.0f);
	}

	void Enemy::integrate() {
		this->sprite.move(-speed, 0.0f);
		return;
	}
	
	void Enemy::render() {
		this->window.draw(this->sprite);
		return;
	}

	sf::Rect<float> Enemy::get_collision_box() const {
		return this->sprite.getGlobalBounds();
	}
}