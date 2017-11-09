#include "inc/main_state.hpp"
#include <inc/utility.hpp>

namespace astroblaster {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm) : State(window, tm), player(window, tm) {
		if (!this->tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
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
		this->font.loadFromFile("res/fon/kenvector_future_thin.ttf");
		auto subtexture = this->tm.get_subtexture(u8"playerLife1_red.png");
		if (!subtexture.first) {
			throw texture_not_found(u8"playerLife1_red.png");
		}
		this->icon.setTexture(*subtexture.first, true);
		this->icon.setTextureRect(subtexture.second);
		this->icon.setPosition(40.0f, 40.0f);
		this->life_bar_outline.setFillColor(sf::Color::Transparent);
		this->life_bar_outline.setOutlineColor(sf::Color::White);
		this->life_bar_outline.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->life_bar_outline.setPosition(95.0f, 40.0f);
		this->life_bar_outline.setOutlineThickness(2.0f);
		this->life_bar.setFillColor(sf::Color::Red);
		this->life_bar.setSize(sf::Vector2<float>(20.0f, 20.0f));
		this->life_bar.setPosition(95.0f, 40.0f);
		this->player_name.setFont(this->font);
		this->player_name.setCharacterSize(28);
		this->player_name.setString(u8"Player1");
		this->player_name.setPosition(215.0f, 32.0f);
	}

	MainState::~MainState() {}

	void MainState::integrate(unsigned int controls) {
		this->player.integrate(controls);
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
		this->player.render();
		this->window.draw(this->icon);
		this->window.draw(this->life_bar_outline);
		this->window.draw(this->life_bar);
		this->window.draw(this->player_name);
		return;
	}
}