#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "inc/texture_manager.hpp"

namespace astroblaster {
	class Player {
		public:
			Player(sf::RenderWindow &window, TextureManager &tm);
			void integrate(unsigned int controls);
			void render();
		private:
			sf::RenderWindow &window;
			sf::Sprite sprite;
	};
}

#endif