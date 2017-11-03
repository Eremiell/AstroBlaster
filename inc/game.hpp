#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "inc/state.hpp"
#include "inc/texture_manager.hpp"

namespace astroblaster {
	class Game {
		public:
			Game();
			void run();
		private:
			sf::RenderWindow window;
			TextureManager tm;
			std::unique_ptr<State> state;
	};
}

#endif