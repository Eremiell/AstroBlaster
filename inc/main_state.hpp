#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <array>
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "inc/player.hpp"
#include "inc/enemy.hpp"
#include "inc/projectile.hpp"

namespace astroblaster {
	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window, TextureManager &tm);
			virtual ~MainState();
			//virtual void input();
			virtual void integrate(unsigned int controls) override;
			virtual void render() override;
		private:
			Player player;
			std::array<sf::Sprite, 8> bg_sprites;
			sf::Font font;
			sf::Sprite icon;
			sf::RectangleShape life_bar;
			sf::RectangleShape life_bar_outline;
			sf::Text player_name;
			std::list<Enemy> enemies;
			std::list<Projectile> projectiles;
			void collide();
			void update_hud();
	};
}

#endif