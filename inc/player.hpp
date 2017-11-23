#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "inc/texture_manager.hpp"
#include "inc/main_state.hpp"

namespace astroblaster {
	class MainState;
	
	class Player {
		public:
			Player(sf::RenderWindow &window, TextureManager &tm, MainState &state, std::string name = u8"PLR", std::size_t number = 0u, bool multiplayer = false);
			void integrate(unsigned int controls);
			void render();
			sf::Rect<float> get_collision_box() const;
			void collide_with(unsigned int type);
			std::size_t get_energy() const;
			std::size_t get_lives() const;
			std::uint64_t get_score() const;
			std::string get_name() const;
			void add_score(std::size_t score);
			sf::Vector2<float> weapon_position() const;
		private:
			sf::Clock weapon_cooldown;
			sf::RenderWindow &window;
			MainState &state;
			std::string name;
			std::size_t energy;
			std::size_t lives;
			std::uint64_t score;
			std::size_t number;
			bool multiplayer;
			sf::Sprite sprite;
			void collide_against_bounds();
			void deduce_energy(std::size_t damage);
	};
}

#endif