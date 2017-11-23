#include "inc/main_state.hpp"
#include <iterator>
#include <numeric>
#include "inc/utility.hpp"

namespace astroblaster {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm, std::size_t players) : State(window, tm), background(window, tm), hud(window, tm, (players==1)?(std::vector<std::string>{u8"PL1"}):(std::vector<std::string>{u8"PL1", u8"PL2"})), generator(new LevelGenerator(*this)) {
		for (std::size_t i = 0; i < players; ++i) {
			this->players.emplace_back(this->window, this->tm, *this, u8"PL" + std::to_string(i), i, players > 1);
		}
	}

	MainState::~MainState() {}

	void MainState::integrate(unsigned int controls) {
		for (auto &player : players) {
			player.integrate(controls);
		}
		for (auto &enemy : this->enemies) {
			enemy.integrate(std::accumulate(this->players.begin(), this->players.end(), std::vector<sf::Vector2<float>>(), accumulate_position));
		}
		for (auto &projectile : this->projectiles) {
			projectile.integrate();
		}
		this->collide();
		this->background.integrate();
		this->hud.integrate(std::accumulate(this->players.begin(), this->players.end(), std::vector<std::size_t>(), accumulate_energy), std::accumulate(this->players.begin(), this->players.end(), std::vector<std::size_t>(), accumulate_lives), std::accumulate(this->players.begin(), this->players.end(), std::vector<std::uint64_t>(), accumulate_score));
		this->generator->generate();
		return;
	}

	void MainState::render() {
		this->background.render();
		for (auto &player : players) {
			player.render();
		}
		for (auto &enemy : this->enemies) {
			enemy.render();
		}
		for (auto &projectile : this->projectiles) {
			projectile.render();
		}
		this->hud.render();
		return;
	}

	void MainState::collide() {
		for (auto &player : players) {
			auto player_box = player.get_collision_box();
			for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it) {
				auto enemy_box = it->get_collision_box();
				if (player_box.intersects(enemy_box)) {
					player.collide_with(static_cast<unsigned int>(CollisionType::Enemy));
					player.add_score(it->get_score());
					it = std::prev(this->enemies.erase(it));
					continue;
				}
				for (auto itr = this->projectiles.begin(); itr != this->projectiles.end(); ++itr) {
					auto projectile_box = itr->get_collision_box();
					if (itr->get_direction() && enemy_box.intersects(projectile_box)) {
						it->collide_with(static_cast<unsigned int>(CollisionType::Projectile));
						if (!it->get_energy()) {
							std::next(this->players.begin(), itr->get_source())->add_score(it->get_score());
							it = std::prev(this->enemies.erase(it));
						}
						itr = std::prev(this->projectiles.erase(itr));
						break;
					}
				}
			}
			for (auto it = this->projectiles.begin(); it != this->projectiles.end(); ++it) {
				auto projectile_box = it->get_collision_box();
				if (!it->get_direction() && player_box.intersects(projectile_box)) {
					player.collide_with(static_cast<unsigned int>(CollisionType::Projectile));
					it = std::prev(this->projectiles.erase(it));
				}
			}
		}
		return;
	}

	void MainState::emplace_projectile(sf::Vector2<float> position, bool direction, std::size_t source) {
		this->projectiles.emplace_back(this->window, this->tm, position, direction, source);
		return;
	}

	void MainState::emplace_enemy(sf::Vector2<float> position, AIType type, bool up) {
		this->enemies.emplace_back(this->window, this->tm, *this, position, type, up);
		return;
	}

	std::vector<std::size_t> accumulate_lives(std::vector<std::size_t> lives, Player p) {
		lives.emplace_back(p.get_lives());
		return lives;
	}

	std::vector<std::size_t> accumulate_energy(std::vector<std::size_t> energy, Player p) {
		energy.emplace_back(p.get_energy());
		return energy;
	}

	std::vector<std::uint64_t> accumulate_score(std::vector<std::uint64_t> score, Player p) {
		score.emplace_back(p.get_score());
		return score;
	}

	std::vector<sf::Vector2<float>> accumulate_position(std::vector<sf::Vector2<float>> position, Player p) {
		position.emplace_back(p.weapon_position());
		return position;
	}

	std::vector<std::string> accumulate_names(std::vector<std::string> names, Player p) {
		names.emplace_back(p.get_name());
		return names;
	}
}