#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <list>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "inc/player.hpp"
#include "inc/enemy.hpp"
#include "inc/projectile.hpp"
#include "inc/parallax_background.hpp"
#include "inc/hud.hpp"
#include "inc/level_generator.hpp"

namespace astroblaster {
	class Enemy;
	class LevelGenerator;

	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window, TextureManager &tm);
			virtual ~MainState();
			//virtual void input();
			virtual void integrate(unsigned int controls) override;
			virtual void render() override;
			void emplace_projectile(sf::Vector2<float> position, bool direction = false);
			void emplace_enemy(sf::Vector2<float> position, AIType type = AIType::NORMAL, bool up = false);
		private:
			ParallaxBackground background;
			Player player;
			HUD hud;
			std::unique_ptr<LevelGenerator> generator;
			std::list<Enemy> enemies;
			std::list<Projectile> projectiles;
			void collide();
	};
}

#endif