#pragma once
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <string_view>

namespace astroblaster {
	const float width = 1600.0f;
	const float height = 800.0f;
	const float speed = 7.0f;

	enum class Controls : unsigned int {
		Up = 1 << 0,
		Down = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3,
		Space = 1 << 4
	};

	enum class TextureModes : unsigned int {
		Sheet = 1 << 0,
		Repeat = 1 << 1
	};

	enum class CollisionType : unsigned int {
		Enemy = 1 << 0,
		Projectile = 1 << 1
	};

	enum class AIType : unsigned int {
		NORMAL = 1 << 0,
		MOVING = 1 << 1,
		RAPID = 1 << 2,
		SMART = 1 << 3
	};

	std::string texture_not_found(std::string_view texture);

	std::string file_not_found(std::string_view file);
}

#endif