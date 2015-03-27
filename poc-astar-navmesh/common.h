#pragma once

#include <cmath>

const int g_INVALID_NODE_INDEX = -1;

struct Vec2f;
float dist(const Vec2f p1, const Vec2f p2);

// Test if p1 and p2 are on the same side of the line [AB]
bool pointOnSameSideOfLine(Vec2f p1, Vec2f p2, Vec2f a, Vec2f b);
float crossProductZ(Vec2f a, Vec2f b);
float dotProduct(Vec2f a, Vec2f b);

struct Vec2f
{
	float x, y;
	Vec2f() : x(0), y(0) {};
	Vec2f(float _x, float _y) : x(_x), y(_y) {};
	float dist(const Vec2f p2)
	{
		return ::dist(*this, p2);
	};
	Vec2f operator-(Vec2f rhs)
	{
		return Vec2f(x - rhs.x, y - rhs.y);
	};
	bool operator==(Vec2f other)
	{
		return (x == other.x && y == other.y);
	};
};

struct Triangle
{
	Vec2f p1, p2, p3;
	Triangle(Vec2f _p1, Vec2f _p2, Vec2f _p3) : p1(_p1), p2(_p2), p3(_p3) {};
	bool contains(Vec2f p) const
	{
		if (pointOnSameSideOfLine(p, p1, p2, p3)
			&& pointOnSameSideOfLine(p, p2, p1, p3)
			&& pointOnSameSideOfLine(p, p3, p1, p2))
		{
			return true;
		}
		else return false;
	};
};
