#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "inc/texture_manager.hpp"

namespace astroblaster {
	class Player {
		public:
			Player(sf::RenderWindow &window, TextureManager &tm);
			void integrate(unsigned int controls);
			void render();
			sf::Rect<float> get_collision_box() const;
			void collide_with(unsigned int type);
		private:
			sf::RenderWindow &window;
			sf::Sprite sprite;
	};
}

#endif