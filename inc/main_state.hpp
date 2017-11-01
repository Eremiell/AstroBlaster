#pragma once
#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "inc/state.hpp"
#include <SFML/Graphics/CircleShape.hpp>

namespace astroblaster {
	class MainState : public State {
		public:
			MainState(sf::RenderWindow &window);
			virtual ~MainState();
			//virtual void input();
			virtual void integrate(unsigned int controls) override;
			virtual void render() override;
		private:
			sf::CircleShape s;
	};
}

#endif