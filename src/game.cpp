#include "inc/game.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include "inc/utility.hpp"
#include "inc/main_state.hpp"

namespace astroblaster {
	Game::Game(std::size_t players) : window(sf::VideoMode(width, height), "AstroBlaster", sf::Style::Titlebar | sf::Style::Close), tm(), state(new MainState(this->window, this->tm, players)) {
		this->window.setKeyRepeatEnabled(false);
	}

	void Game::run() {
		bool running = true;
		double t = 0.0;
		const double dt = 1.0 / 60.0;
		double accumulator = 0.0;
		sf::Clock timer;
		unsigned int controls = 0u;
		while (running) {
			accumulator += timer.restart().asSeconds();
			controls &= 0u;
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					running = false;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
				running = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				controls |= static_cast<unsigned int>(Controls::P1Up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				controls |= static_cast<unsigned int>(Controls::P1Down);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				controls |= static_cast<unsigned int>(Controls::P1Left);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				controls |= static_cast<unsigned int>(Controls::P1Right);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				controls |= static_cast<unsigned int>(Controls::P1Shoot);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				controls |= static_cast<unsigned int>(Controls::P2Up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				controls |= static_cast<unsigned int>(Controls::P2Down);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				controls |= static_cast<unsigned int>(Controls::P2Left);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				controls |= static_cast<unsigned int>(Controls::P2Right);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				controls |= static_cast<unsigned int>(Controls::P2Shoot);
			}
			while (accumulator >= dt) {
				this->state->integrate(controls);
				accumulator -= dt;
				t += dt;
			}
			this->window.clear(sf::Color::Blue);
			this->state->render();
			this->window.display();
		}
		this->window.close();
		return;
	}
}