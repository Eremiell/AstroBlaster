#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "inc/texture_manager.hpp"
#include "inc/main_state.hpp"
#include "inc/utility.hpp"

namespace astroblaster {
	class MainState;

	class Enemy {
		public:
			Enemy(sf::RenderWindow &window, TextureManager &tm, MainState &state, sf::Vector2<float> position, AIType type = AIType::NORMAL, bool up = false);
			void integrate(std::vector<sf::Vector2<float>> player_positions);
			void render();
			sf::Rect<float> get_collision_box() const;
			void collide_with(unsigned int type);
			std::size_t get_energy() const;
			std::size_t get_score() const;
			sf::Vector2<float> weapon_position() const;
		private:
			sf::RenderWindow &window;
			MainState &state;
			AIType type;
			bool up;
			unsigned int counter;
			std::size_t energy;
			std::size_t score;
			sf::Clock weapon_clock;
			sf::Sprite sprite;
			void integrate_normal();
			void integrate_moving();
			void integrate_rapid();
			void integrate_smart(std::vector<sf::Vector2<float>> player_positions);
			void deduce_energy(std::size_t damage);
			void fire();
	};
}

#endif