#include "inc/utility.hpp"
#include <sstream>

namespace astroblaster {
	std::string texture_not_found(std::string_view texture) {
		std::stringstream ss;
		ss << u8"Texture " << texture << u8" not found in manager.";
		return ss.str();
	}

	std::string file_not_found(std::string_view file) {
		std::stringstream ss;
		ss << u8"File " << file << u8" not found or not readable.";
		return ss.str();
	}
}