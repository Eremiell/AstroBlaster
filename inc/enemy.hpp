#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "inc/texture_manager.hpp"
#include "inc/main_state.hpp"

namespace astroblaster {
	class MainState;

	class Enemy {
		public:
			enum class AI_TYPE : unsigned int {
				NORMAL = 1 << 0,
				MOVING = 1 << 1,
				RAPID = 1 << 2,
				SMART = 1 << 3
			};
			Enemy(sf::RenderWindow &window, TextureManager &tm, MainState &state, AI_TYPE type = AI_TYPE::NORMAL);
			void integrate(sf::Vector2<float> player_position);
			void render();
			sf::Rect<float> get_collision_box() const;
			void collide_with(unsigned int type);
			std::size_t get_energy() const;
			sf::Vector2<float> weapon_position() const;
		private:
			sf::RenderWindow &window;
			MainState &state;
			AI_TYPE type;
			bool up;
			std::size_t counter;
			std::size_t energy;
			sf::Sprite sprite;
			void integrate_normal();
			void integrate_moving();
			void integrate_rapid();
			void integrate_smart(sf::Vector2<float> player_position);
			void deduce_energy(std::size_t damage);
	};
}

#endif