#pragma once

#include <cmath>

const int g_INVALID_NODE_INDEX = -1;

struct Vec2f;
float dist(const Vec2f p1, const Vec2f p2);

struct Vec2f {
	float x, y;
	Vec2f() : x(0), y(0) {};
	Vec2f(float _x, float _y) : x(_x), y(_y) {};
	float dist(const Vec2f p2) {
		return ::dist(*this, p2);
	};
};