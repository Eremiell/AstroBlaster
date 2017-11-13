#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "inc/texture_manager.hpp"

namespace astroblaster {
	class Enemy {
		public:
			Enemy(sf::RenderWindow &window, TextureManager &tm);
			void integrate();
			void render();
		private:
			sf::RenderWindow &window;
			sf::Sprite sprite;
	};
}

#endif