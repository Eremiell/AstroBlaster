#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <list>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "inc/texture_manager.hpp"
#include "inc/utility.hpp"

namespace astroblaster {
	class HUD {
		public:
			HUD(sf::RenderWindow &window, TextureManager &tm, std::vector<std::string> player_names = {u8"PLR"});
			void integrate(std::vector<std::size_t> player_energy, std::vector<std::size_t> player_lives, std::vector<std::uint64_t> player_score);
			void render();
		private:
			sf::RenderWindow &window;
			std::size_t players;
			std::vector<std::size_t> player_lives;
			std::vector<std::size_t> player_energy;
			std::vector<std::uint64_t> player_score;
			sf::Font font;
			std::list<sf::Sprite> icons;
			sf::RectangleShape energy_bar;
			sf::RectangleShape energy_bar_outline;
			std::list<sf::Text> player_names;
			sf::Text player_score_text;
	};
}

#endif