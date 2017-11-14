#include "inc/main_state.hpp"
#include <iterator>
#include "inc/utility.hpp"

namespace astroblaster {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm) : State(window, tm), background(window, tm), player(window, tm), hud(window, tm) {
		this->enemies.emplace_back(Enemy(this->window, this->tm, *this));
	}

	MainState::~MainState() {}

	void MainState::integrate(unsigned int controls) {
		static sf::Clock weapon_cooldown;
		this->player.integrate(controls);
		if (controls & static_cast<unsigned int>(Controls::Space) && weapon_cooldown.getElapsedTime().asSeconds() >= 0.1f) {
			weapon_cooldown.restart();
			this->projectiles.emplace_back(this->window, this->tm, this->player.weapon_position(), true);
		}
		for (auto &enemy : this->enemies) {
			enemy.integrate();
		}
		for (auto &projectile : this->projectiles) {
			projectile.integrate();
		}
		this->collide();
		this->background.integrate();
		this->hud.integrate(this->player.get_energy());
		return;
	}

	void MainState::render() {
		this->background.render();
		this->player.render();
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
		auto player_box = this->player.get_collision_box();
		for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it) {
			auto enemy_box = it->get_collision_box();
			if (player_box.intersects(enemy_box)) {
				this->player.collide_with(static_cast<unsigned int>(CollisionType::Enemy));
				it = std::prev(this->enemies.erase(it));
			}
			for (auto itr = this->projectiles.begin(); itr != this->projectiles.end(); ++itr) {
				auto projectile_box = itr->get_collision_box();
				if (enemy_box.intersects(projectile_box)) {
					it->collide_with(static_cast<unsigned int>(CollisionType::Projectile));
					if (!it->get_energy()) {
						it = std::prev(this->enemies.erase(it));
					}
					itr = std::prev(this->projectiles.erase(itr));
				}
			}
		}
		for (auto it = this->projectiles.begin(); it != this->projectiles.end(); ++it) {
			auto projectile_box = it->get_collision_box();
			if (player_box.intersects(projectile_box)) {
				this->player.collide_with(static_cast<unsigned int>(CollisionType::Projectile));
				it = std::prev(this->projectiles.erase(it));
			}
		}
		return;
	}

	void MainState::emplace_projectile(sf::Vector2<float> position, bool direction) {
		this->projectiles.emplace_back(this->window, this->tm, position, direction);
		return;
	}
}