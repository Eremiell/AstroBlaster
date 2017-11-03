#include "inc/state.hpp"

namespace astroblaster {
	State::State(sf::RenderWindow &window, TextureManager &tm) : window(window), tm(tm) {}

	State::~State() {}
}