#include <iostream>
#include <string>
#include <exception>
#include "inc/game.hpp"

int main(int argc, char **argv) {
	std::size_t players = 1;
	if (argc > 1 && std::string(argv[1]) == "--multiplayer") {
		players = 2;
	}
	try {
		astroblaster::Game game(players);
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