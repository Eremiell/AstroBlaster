#include "inc/main_state.hpp"
#include <cmath>

namespace astroblaster {
	MainState::MainState(sf::RenderWindow &window) : State(window), s(30.0f) {
		this->s.setFillColor(sf::Color::Green);
		this->s.setOrigin(15.0f, 15.0f);
		this->s.setPosition(800.0f, 400.0f);
	}

	MainState::~MainState() {}

	void MainState::integrate(unsigned int controls) {
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

	void MainState::render() {
		this->window.draw(this->s);
		return;
	}
}