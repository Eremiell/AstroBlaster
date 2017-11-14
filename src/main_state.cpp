#include "inc/main_state.hpp"
#include <iterator>
#include "inc/utility.hpp"

namespace astroblaster {
	MainState::MainState(sf::RenderWindow &window, TextureManager &tm) : State(window, tm), background(window, tm), player(window, tm) {
		if (!this->tm.add_texture(u8"sheet.xml", static_cast<unsigned int>(TextureModes::Sheet))) {
			throw file_not_found(u8"sheet.xml");
		}
		this->font.loadFromFile("res/fon/kenvector_future_thin.ttf");
		auto subtexture = this->tm.get_subtexture(u8"playerLife1_red.png");
		if (!subtexture.first) {
			throw texture_not_found(u8"playerLife1_red.png");
		}
		this->icon.setTexture(*subtexture.first, true);
		this->icon.setTextureRect(subtexture.second);
		this->icon.setPosition(40.0f, 40.0f);
		this->life_bar_outline.setFillColor(sf::Color::Transparent);
		this->life_bar_outline.setOutlineColor(sf::Color::White);
		this->life_bar_outline.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->life_bar_outline.setPosition(95.0f, 40.0f);
		this->life_bar_outline.setOutlineThickness(2.0f);
		this->life_bar.setFillColor(sf::Color::Green);
		this->life_bar.setSize(sf::Vector2<float>(100.0f, 20.0f));
		this->life_bar.setPosition(95.0f, 40.0f);
		this->player_name.setFont(this->font);
		this->player_name.setCharacterSize(28);
		this->player_name.setString(u8"Player1");
		this->player_name.setPosition(215.0f, 32.0f);
		this->enemies.emplace_back(Enemy(this->window, this->tm));
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
		this->update_hud();
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
		this->window.draw(this->icon);
		this->window.draw(this->life_bar_outline);
		this->window.draw(this->life_bar);
		this->window.draw(this->player_name);
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
					it = std::prev(this->enemies.erase(it));
					itr = std::prev(this->projectiles.erase(itr));
				}
			}
		}
		return;
	}

	void MainState::update_hud() {
		auto player_energy = this->player.get_energy();
		this->life_bar.setSize(sf::Vector2<float>(static_cast<float>(player_energy), 20.0f));
		if (player_energy <= 30) {
			this->life_bar.setFillColor(sf::Color::Red);
		}
		else if (player_energy <= 60) {
			this->life_bar.setFillColor(sf::Color::Yellow);
		}
		else {
			this->life_bar.setFillColor(sf::Color::Green);
		}
		return;
	}
}