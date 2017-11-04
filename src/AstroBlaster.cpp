#include <iostream>
#include <string>
#include <exception>
#include "inc/game.hpp"

int main() {
	try {
		astroblaster::Game game;
		game.run();
	}
	catch (std::string s) {
		std::cerr << s << '\n';
		return 1;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}