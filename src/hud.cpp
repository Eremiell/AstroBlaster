#include "inc/hud.hpp"
#include <iterator>

namespace astroblaster {
	HUD::HUD(sf::RenderWindow &window, TextureManager &tm, std::vector<std::string> player_names) : window(window), players(player_names.size()) {
		if (!tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		if (!this->font.loadFromFile("res/fon/kenvector_future_thin.ttf")) {
			throw file_not_found(u8"kenvector_future_thin.ttf");
		}
		for (std::size_t i = 0; i < this->players; ++i) {
			auto subtexture = tm.get_subtexture(u8"playerLife1_" + colours.at(i) + ".png");
			if (!subtexture.first) {
				throw texture_not_found(u8"playerLife1_" + colours.at(i) + ".png");
			}
			auto &icon = this->icons.emplace_back();
			icon.setTexture(*subtexture.first, true);
			icon.setTextureRect(subtexture.second);
			icon.setPosition(160.0f, 20.0f);
			this->player_lives.emplace_back(3u);
			this->player_energy.emplace_back(100u);
			this->player_score.emplace_back(0ull);
			auto &name = this->player_names.emplace_back();
			name.setFont(this->font);
			name.setCharacterSize(28);
			name.setString(player_names.at(i));
			name.setPosition(40.0f, 12.0f + i * 30.0f);
		}
		this->energy_bar_outline.setFillColor(sf::Color::Transparent);
		this->energy_bar_outline.setOutlineColor(sf::Color::White);
		this->energy_bar_outline.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->energy_bar_outline.setPosition(240.0f, 20.0f);
		this->energy_bar_outline.setOutlineThickness(2.0f);
		this->energy_bar.setFillColor(sf::Color::Green);
		this->energy_bar.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->energy_bar.setPosition(240.0f, 20.0f);
		this->player_score_text.setFont(this->font);
		this->player_score_text.setCharacterSize(28);
		this->player_score_text.setString(u8"0");
		this->player_score_text.setPosition(360.0f, 12.0f);
	}

	void HUD::integrate(std::vector<std::size_t> player_energy, std::vector<std::size_t> player_lives, std::vector<std::uint64_t> player_score) {
		this->player_energy = player_energy;
		this->player_lives = player_lives;
		this->player_score = player_score;
		return;
	}

	void HUD::render() {
		for (std::size_t i = 0; i < this->players; ++i) {
			this->energy_bar.setSize(sf::Vector2<float>(static_cast<float>(this->player_energy.at(i)), 20.0f));
			this->energy_bar.setPosition(240.0f, 20.0f + i * 30.0f);
			this->energy_bar_outline.setPosition(240.0f, 20.0f + i * 30.0f);
			if (this->player_energy.at(i) <= 30) {
				this->energy_bar.setFillColor(sf::Color::Red);
			}
			else if (this->player_energy.at(i) <= 60) {
				this->energy_bar.setFillColor(sf::Color::Yellow);
			}
			else {
				this->energy_bar.setFillColor(sf::Color::Green);
			}
			this->player_score_text.setString(std::to_string(this->player_score.at(i)));
			this->player_score_text.setPosition(360.0f, 12.0f + i * 30.0f);
			for (std::size_t j = 1; j <= 3; ++j) {
				std::next(this->icons.begin(), i)->setPosition(110.0f + (j - 1) * 40.f, 20.0f);
				if (j > this->player_lives.at(i)) {
					std::next(this->icons.begin(), i)->setColor(sf::Color(0x77, 0x77, 0x77));
				}
				else {
					std::next(this->icons.begin(), i)->setColor(sf::Color(0xff, 0xff, 0xff, 0xff));
				}
				this->window.draw(*std::next(this->icons.begin(), i));
			}
			this->window.draw(this->energy_bar_outline);
			this->window.draw(this->energy_bar);
			this->window.draw(*std::next(this->player_names.begin(), i));
			this->window.draw(this->player_score_text);
		}
		return;
	}
}