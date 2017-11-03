#include "inc/main_state.hpp"
#include <cmath>
#include <inc/utility.hpp>

namespace astroblaster {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm) : State(window, tm) {
		if (!this->tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		auto subtexture = this->tm.get_subtexture(u8"playerShip1_red.png");
		if (!subtexture.first) {
			throw texture_not_found(u8"playerShip1_red.png");
		}
		this->player.setTexture(*subtexture.first, true);
		this->player.setTextureRect(subtexture.second);
		this->player.setOrigin(subtexture.second.width / 2, subtexture.second.height / 2);
		this->player.setRotation(90);
		this->player.setPosition(800.0f, 400.0f);
		for (std::size_t i = 0; i < 8; ++i) {
			if (!this->tm.add_texture(u8"bkgd_" + std::to_string(i) + u8".png", static_cast<unsigned int>(TextureModes::Repeat))) {
				throw file_not_found(u8"bkgd_" + std::to_string(i) + u8".png");
			}
			auto texture = this->tm.get_texture(u8"bkgd_" + std::to_string(i) + u8".png");
			if (!texture) {
				throw texture_not_found(u8"bkgd_" + std::to_string(i) + u8".png");
			}
			this->bg_sprites[i].setTexture(*texture, true);
			this->bg_sprites[i].setTextureRect(sf::Rect<int>(0, 0, 1600, 800));
		}
		//this->bg_sprites[0].setColor(sf::Color::Black);
	}

	MainState::~MainState() {}

	void MainState::integrate(unsigned int controls) {
		static const float speed = 10.0f;
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
		this->player.move(movement);
		for (std::size_t i = 0; i < 8; ++i) {
			auto rect = this->bg_sprites[i].getTextureRect();
			rect.left += 1.0f * (i + 1);
			this->bg_sprites[i].setTextureRect(rect);
		}
		return;
	}

	void MainState::render() {
		for (std::size_t i = 0; i < 8; ++i) {
			this->window.draw(this->bg_sprites[i]);
		}
		this->window.draw(this->player);
		return;
	}
}