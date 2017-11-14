#pragma once
#ifndef HUD_HPP
#define HUD_HPP

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
			HUD(sf::RenderWindow &window, TextureManager &tm);
			void integrate(std::size_t player_energy);
			void render();
		private:
			sf::RenderWindow &window;
			sf::Font font;
			sf::Sprite icon;
			sf::RectangleShape life_bar;
			sf::RectangleShape life_bar_outline;
			sf::Text player_name;
	};
}

#endif