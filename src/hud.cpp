#include "inc/hud.hpp"

namespace astroblaster {
	HUD::HUD(sf::RenderWindow &window, TextureManager &tm) : window(window) {
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
		this->icon.setPosition(40.0f, 40.0f);
		this->life_bar_outline.setFillColor(sf::Color::Transparent);
		this->life_bar_outline.setOutlineColor(sf::Color::White);
		this->life_bar_outline.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->life_bar_outline.setPosition(95.0f, 40.0f);
		this->life_bar_outline.setOutlineThickness(2.0f);
		this->life_bar.setFillColor(sf::Color::Green);
		this->life_bar.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->life_bar.setPosition(95.0f, 40.0f);
		this->player_name.setFont(this->font);
		this->player_name.setCharacterSize(28);
		this->player_name.setString(u8"Player1");
		this->player_name.setPosition(215.0f, 32.0f);
	}

	void HUD::integrate(std::size_t player_energy) {
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
		return;
	}

	void HUD::render() {
		this->window.draw(this->icon);
		this->window.draw(this->life_bar_outline);
		this->window.draw(this->life_bar);
		this->window.draw(this->player_name);
		return;
	}
}