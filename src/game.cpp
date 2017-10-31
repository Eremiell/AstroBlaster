#include "inc/game.hpp"
#include <cmath>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include "inc/utility.hpp"

namespace astroblaster {
	Game::Game() : window(sf::VideoMode(1600.0f, 800.0f), "AstroBlaster", sf::Style::Titlebar | sf::Style::Close), s(30.0f) {
		this->window.setKeyRepeatEnabled(false);
		this->s.setFillColor(sf::Color::Green);
		this->s.setOrigin(15.0f, 15.0f);
		this->s.setPosition(800.0f, 400.0f);
	}

	void Game::run() {
		bool running = true;
		double t = 0.0;
		const double dt = 1.0 / 60.0;
		double accumulator = 0.0;
		sf::Clock timer;
		unsigned int controls;
		while (running) {
			accumulator += timer.restart().asSeconds();
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					running = false;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
				running = false;
			}
			controls &= 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				controls |= static_cast<unsigned int>(Controls::Up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				controls |= static_cast<unsigned int>(Controls::Down);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				controls |= static_cast<unsigned int>(Controls::Left);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				controls |= static_cast<unsigned int>(Controls::Right);
			}
			while (accumulator >= dt) {
				this->integrate(controls);
				accumulator -= dt;
				t += dt;
			}
			this->window.clear(sf::Color::Blue);
			this->window.draw(this->s);
			this->window.display();
		}
		this->window.close();
		return;
	}

	void Game::integrate(unsigned int controls) {
		static const float speed = 10.0f;
		sf::Vector2<float> movement(0.0f, 0.0f);
		if ((controls & static_cast<unsigned int>(Controls::Up)) && !(controls & static_cast<unsigned int>(Controls::Down))) {
			movement.y -= 1.0f;
		}
		else if ((controls & static_cast<unsigned int>(Controls::Down)) && !(controls & static_cast<unsigned int>(Controls::Up))) {
			movement.y += 1.0f;
		}
		if ((controls & static_cast<unsigned int>(Controls::Left)) && !(controls & static_cast<unsigned int>(Controls::Right))) {
			movement.x -= 1.0f;
		}
		else if ((controls & static_cast<unsigned int>(Controls::Right)) && !(controls & static_cast<unsigned int>(Controls::Left))) {
			movement.x += 1.0f;
		}
		if ((std::fabs(movement.x) > 0.001f) && (std::fabs(movement.y) > 0.001f)) {
			movement.x *= std::sqrt(speed * speed / 2);
			movement.y *= std::sqrt(speed * speed / 2);
		}
		else {
			movement.x *= speed;
			movement.y *= speed;
		}
		s.move(movement);
		return;
	}
}