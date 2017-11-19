#include "inc/level_generator.hpp"
#include <chrono>

namespace astroblaster {
	LevelGenerator::LevelGenerator(MainState &state, double difficulty) : state(state), difficulty(difficulty), mt(std::chrono::high_resolution_clock::now().time_since_epoch().count()), dt(2.0f), dist(0, 7) {
		formations.emplace_back(std::make_pair(std::vector<std::pair<sf::Vector2<float>, AIType>>(), 2.0f));
		formations.emplace_back(
			std::make_pair(
				std::vector<std::pair<sf::Vector2<float>, AIType>>{
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, 100.0f),
						AIType::SMART
					)
				},
				1.0f
			)
		);
		formations.emplace_back(
			std::make_pair(
				std::vector<std::pair<sf::Vector2<float>, AIType>>{
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height - 100.0f),
						AIType::SMART
					)
				},
				2.0f
			)
		);
		formations.emplace_back(
			std::make_pair(
				std::vector<std::pair<sf::Vector2<float>, AIType>>{
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, 100.0f),
						AIType::RAPID
					)
				},
				2.0f
			)
		);
		formations.emplace_back(
			std::make_pair(
				std::vector<std::pair<sf::Vector2<float>, AIType>>{
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height - 100.0f),
						AIType::RAPID
					)
				},
				2.0f
			)
		);
		formations.emplace_back(
			std::make_pair(
				std::vector<std::pair<sf::Vector2<float>, AIType>>{
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, 100.0f),
						AIType::RAPID
					),
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height - 100.0f),
						AIType::RAPID
					)
				},
				2.0f
			)
		);
		formations.emplace_back(
			std::make_pair(
				std::vector<std::pair<sf::Vector2<float>, AIType>>{
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height - 100.0f),
						AIType::MOVING
					),
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height / 2),
						AIType::MOVING
					),
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, 100.0f),
						AIType::MOVING
					)
				},
				2.0f
			)
		);
		formations.emplace_back(
			std::make_pair(
				std::vector<std::pair<sf::Vector2<float>, AIType>>{
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height - 100.0f),
						AIType::NORMAL
					),
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height / 4),
						AIType::NORMAL
					),
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height / 2),
						AIType::NORMAL
					),
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, height * 3 / 4),
						AIType::NORMAL
					),
					std::make_pair(
						sf::Vector2<float>(width + 100.0f, 100.0f),
						AIType::NORMAL
					)
				},
				2.0f
			)
		);
		//formations.emplace_back(std::make_tuple(std::vector<std::tuple<sf::Vector2<float>, AIType, bool>>(std::make_tuple(sf::Vector2<float>(width - 100.0f, height - 100.0f), AIType::SMART, true)), 2.0f));
		//std::tuple{{std::tuple<sf::Vector2<float>, AIType, bool>{sf::Vector2<float>(width - 100.0f, height - 100.0f), AIType::SMART, true}}, 2.0f}
	}

	void LevelGenerator::generate() {
		if (this->ticker.getElapsedTime().asSeconds() > this->dt) {
			this->ticker.restart();
			std::size_t wave = this->dist(this->mt);
			this->dt = this->formations.at(wave).second;
			for (auto &enemy : this->formations.at(wave).first) {
				this->state.emplace_enemy(enemy.first, enemy.second);//, std::get<2>(enemy));
			}
		}
		return;
	}
}