#pragma once
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <string_view>
#include <array>

namespace astroblaster {
	const float width = 1600.0f;
	const float height = 800.0f;
	const float speed = 7.0f;

	const std::array<std::string, 4> colours{"red", "green", "blue", "orange"};

	enum class Controls : unsigned int {
		P1Up = 1 << 0,
		P1Down = 1 << 1,
		P1Left = 1 << 2,
		P1Right = 1 << 3,
		P1Shoot = 1 << 4,
		P2Up = 1 << 5,
		P2Down = 1 << 6,
		P2Left = 1 << 7,
		P2Right = 1 << 8,
		P2Shoot = 1 << 9
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