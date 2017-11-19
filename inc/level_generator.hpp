#pragma once
#ifndef LEVEL_GENERATOR_HPP
#define LEVEL_GENERATOR_HPP

#include <random>
#include <vector>
#include <utility>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include "inc/main_state.hpp"
#include "inc/utility.hpp"

namespace astroblaster {
	class MainState;

	class LevelGenerator {
		public:
			LevelGenerator(MainState &state, double difficulty = 1.0);
			void generate();
		private:
			MainState &state;
			double difficulty;
			std::mt19937_64 mt;
			float dt;
			std::vector<
				std::pair<
					std::vector<
						std::pair<
							sf::Vector2<float>, AIType//, bool
						>
					>,
					float
				>
			> formations;
			std::uniform_int_distribution<std::size_t> dist;
			sf::Clock ticker;
	};
}

#endif