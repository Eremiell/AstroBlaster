#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace astroblaster {
	class Game {
		public:
			Game();
			void run();
		private:
			sf::RenderWindow window;
			sf::CircleShape s;
			void integrate(unsigned int controls);
	};
}

#endif