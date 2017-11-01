#pragma once
#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "inc/utility.hpp"

namespace astroblaster {
	class State {
		public:
			State(sf::RenderWindow &window);
			virtual ~State();
			//void input();
			virtual void integrate(unsigned int controls) = 0;
			virtual void render() = 0;
		protected:
			sf::RenderWindow &window;
	};
}

#endif