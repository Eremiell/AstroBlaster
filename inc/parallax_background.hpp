#pragma once
#ifndef PARALLAX_BACKGROUND_HPP
#define PARALLAX_BACKGROUND_HPP

#include <array>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "inc/texture_manager.hpp"
#include "inc/utility.hpp"

namespace astroblaster {
	class ParallaxBackground {
		public:
			ParallaxBackground(sf::RenderWindow &window, TextureManager &tm);
			void integrate();
			void render();
		private:
			sf::RenderWindow &window;
			std::array<sf::Sprite, 8> bg_sprites;
	};
}

#endif