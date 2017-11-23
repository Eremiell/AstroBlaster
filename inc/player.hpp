#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>
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
			std::size_t get_energy() const;
			std::size_t get_lives() const;
			std::uint64_t get_score() const;
			void add_score(std::size_t score);
			sf::Vector2<float> weapon_position() const;
		private:
			sf::RenderWindow &window;
			std::size_t energy;
			std::size_t lives;
			std::uint64_t score;
			sf::Sprite sprite;
			void collide_against_bounds();
			void deduce_energy(std::size_t damage);
	};
}

#endif