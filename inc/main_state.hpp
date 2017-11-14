#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <list>
#include "inc/player.hpp"
#include "inc/enemy.hpp"
#include "inc/projectile.hpp"
#include "inc/parallax_background.hpp"
#include "inc/hud.hpp"

namespace astroblaster {
	class Enemy;

	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window, TextureManager &tm);
			virtual ~MainState();
			//virtual void input();
			virtual void integrate(unsigned int controls) override;
			virtual void render() override;
			void emplace_projectile(sf::Vector2<float> position, bool direction = false);
		private:
			ParallaxBackground background;
			Player player;
			HUD hud;
			std::list<Enemy> enemies;
			std::list<Projectile> projectiles;
			void collide();
	};
}

#endif