#include "inc/parallax_background.hpp"

namespace astroblaster {
	ParallaxBackground::ParallaxBackground(sf::RenderWindow &window, TextureManager &tm) : window(window) {
		for (std::size_t i = 0; i < 8; ++i) {
			if (!tm.add_texture(u8"bkgd_" + std::to_string(i) + u8".png", static_cast<unsigned int>(TextureModes::Repeat))) {
				throw file_not_found(u8"bkgd_" + std::to_string(i) + u8".png");
			}
			auto texture = tm.get_texture(u8"bkgd_" + std::to_string(i) + u8".png");
			if (!texture) {
				throw texture_not_found(u8"bkgd_" + std::to_string(i) + u8".png");
			}
			this->bg_sprites[i].setTexture(*texture, true);
			this->bg_sprites[i].setTextureRect(sf::Rect<int>(0, 0, width, height));
		}
		//this->bg_sprites[0].setColor(sf::Color::Black);
	}

	void ParallaxBackground::integrate() {
		for (std::size_t i = 0; i < 8; ++i) {
			auto rect = this->bg_sprites[i].getTextureRect();
			rect.left += 1.0f * (i + 1);
			this->bg_sprites[i].setTextureRect(rect);
		}
		return;
	}

	void ParallaxBackground::render() {
		for (std::size_t i = 0; i < 8; ++i) {
			this->window.draw(this->bg_sprites[i]);
		}
		return;
	}
}