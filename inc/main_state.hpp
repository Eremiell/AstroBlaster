#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <list>
#include <memory>
#include <vector>
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
	class Player;

	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window, TextureManager &tm, std::size_t players = 1);
			virtual ~MainState();
			//virtual void input();
			virtual void integrate(unsigned int controls) override;
			virtual void render() override;
			void emplace_projectile(sf::Vector2<float> position, bool direction = false, std::size_t source = 100u);
			void emplace_enemy(sf::Vector2<float> position, AIType type = AIType::NORMAL, bool up = false);
		private:
			ParallaxBackground background;
			HUD hud;
			std::unique_ptr<LevelGenerator> generator;
			std::list<Player> players;
			std::list<Enemy> enemies;
			std::list<Projectile> projectiles;
			void collide();
	};

	std::vector<std::size_t> accumulate_lives(std::vector<std::size_t> lives, Player p);
	std::vector<std::size_t> accumulate_energy(std::vector<std::size_t> energy, Player p);
	std::vector<std::uint64_t> accumulate_score(std::vector<std::uint64_t> score, Player p);
	std::vector<sf::Vector2<float>> accumulate_position(std::vector<sf::Vector2<float>> position, Player p);
	std::vector<std::string> accumulate_names(std::vector<std::string> names, Player p);
}

#endif