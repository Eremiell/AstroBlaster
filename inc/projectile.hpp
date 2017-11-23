#pragma once
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "inc/texture_manager.hpp"

namespace astroblaster {
	class Projectile {
		public:
			Projectile(sf::RenderWindow &window, TextureManager &tm, sf::Vector2<float> position, bool direction = true, std::size_t source = 100u);
			void integrate();
			void render();
			bool get_direction() const;
			std::size_t get_source() const;
			sf::Rect<float> get_collision_box();
		private:
			sf::RenderWindow &window;
			bool direction;
			std::size_t source;
			sf::Sprite sprite;
	};
}

#endif