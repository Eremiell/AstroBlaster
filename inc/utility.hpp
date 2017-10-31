#pragma once
#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace astroblaster {
	enum class Controls : unsigned int {
		Up = 1 << 0,
		Down = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3
	};
}

#endif