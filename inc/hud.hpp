#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <string>
#include <cstdint>
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
			HUD(sf::RenderWindow &window, TextureManager &tm, std::string player_name = u8"PLR");
			void integrate(std::size_t player_energy, std::size_t player_lifes, std::uint64_t player_score);
			void render();
		private:
			sf::RenderWindow &window;
			std::size_t player_lives;
			sf::Font font;
			sf::Sprite icon;
			sf::RectangleShape life_bar;
			sf::RectangleShape life_bar_outline;
			sf::Text player_name;
			sf::Text player_score;
	};
}

#endif