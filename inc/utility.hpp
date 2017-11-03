#pragma once
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <string_view>

namespace astroblaster {
	enum class Controls : unsigned int {
		Up = 1 << 0,
		Down = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3
	};

	enum class TextureModes : unsigned int {
		Sheet = 1 << 0,
		Repeat = 1 << 1
	};

	std::string texture_not_found(std::string_view texture);

	std::string file_not_found(std::string_view file);
}

#endif