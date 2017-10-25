#include "inc/game.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace astroblaster {
	Game::Game() : window(sf::VideoMode(1600.0f, 800.0f), "AstroBlaster", sf::Style::Titlebar | sf::Style::Close) {
		this->window.setKeyRepeatEnabled(false);
	}

	void Game::run() {
		bool running = true;
		double t = 0.0;
		const double dt = 1.0 / 60.0;
		double accumulator = 0.0;
		sf::Clock timer;
		sf::CircleShape s(30.0f);
		s.setFillColor(sf::Color::Green);
		s.setOrigin(15.0f, 15.0f);
		s.setPosition(800.0f, 400.0f);
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
			while (accumulator >= dt) {
				// integrate();
				accumulator -= dt;
				t += dt;
			}
			this->window.clear(sf::Color::Blue);
			this->window.draw(s);
			this->window.display();
		}
		this->window.close();
		return;
	}
}