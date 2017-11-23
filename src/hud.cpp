#include "inc/hud.hpp"

namespace astroblaster {
	HUD::HUD(sf::RenderWindow &window, TextureManager &tm, std::string player_name) : window(window), player_lives(3) {
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		if (!this->font.loadFromFile("res/fon/kenvector_future_thin.ttf")) {
			throw file_not_found(u8"kenvector_future_thin.ttf");
		}
		auto subtexture = tm.get_subtexture(u8"playerLife1_red.png");
		if (!subtexture.first) {
			throw texture_not_found(u8"playerLife1_red.png");
		}
		this->icon.setTexture(*subtexture.first, true);
		this->icon.setTextureRect(subtexture.second);
		this->icon.setPosition(40.0f, 20.0f);
		this->icon.setPosition(160.0f, 20.0f);
		this->life_bar_outline.setFillColor(sf::Color::Transparent);
		this->life_bar_outline.setOutlineColor(sf::Color::White);
		this->life_bar_outline.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->life_bar_outline.setPosition(95.0f, 20.0f);
		this->life_bar_outline.setPosition(240.0f, 20.0f);
		this->life_bar_outline.setOutlineThickness(2.0f);
		this->life_bar.setFillColor(sf::Color::Green);
		this->life_bar.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->life_bar.setPosition(95.0f, 20.0f);
		this->life_bar.setPosition(240.0f, 20.0f);
		this->player_name.setFont(this->font);
		this->player_name.setCharacterSize(28);
		this->player_name.setString(player_name);
		this->player_name.setPosition(215.0f, 12.0f);
		this->player_name.setPosition(40.0f, 12.0f);
		this->player_score.setFont(this->font);
		this->player_score.setCharacterSize(28);
		this->player_score.setString(u8"10250");
		this->player_score.setPosition(360.0f, 12.0f);
	}

	void HUD::integrate(std::size_t player_energy, std::size_t player_lives, std::uint64_t player_score) {
		this->life_bar.setSize(sf::Vector2<float>(static_cast<float>(player_energy), 20.0f));
		if (player_energy <= 30) {
			this->life_bar.setFillColor(sf::Color::Red);
		}
		else if (player_energy <= 60) {
			this->life_bar.setFillColor(sf::Color::Yellow);
		}
		else {
			this->life_bar.setFillColor(sf::Color::Green);
		}
		this->player_lives = player_lives;
		this->player_score.setString(std::to_string(player_score));
		return;
	}

	void HUD::render() {
		for (std::size_t i = 1; i <= 3; ++i) {
			this->icon.setPosition(110.0f + (i - 1) * 40.f, 20.0f);
			if (i > this->player_lives) {
				this->icon.setColor(sf::Color(0x77, 0x77, 0x77));
			}
			else {
				this->icon.setColor(sf::Color(0xff, 0xff, 0xff, 0xff));
			}
			this->window.draw(this->icon);
		}
		this->window.draw(this->life_bar_outline);
		this->window.draw(this->life_bar);
		this->window.draw(this->player_name);
		this->window.draw(this->player_score);
		return;
	}
}