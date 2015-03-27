#include "common.h"


float dist(const Vec2f p1, const Vec2f p2) {
	return hypotf(p2.x - p1.x, p2.y - p1.y);
};

bool pointOnSameSideOfLine(Vec2f p1, Vec2f p2, Vec2f a, Vec2f b)
{
	float cp1z = crossProductZ(b - a, p1 - a);
	float cp2z = crossProductZ(b - a, p2 - a);
	if (/*dotProduct(cp1, cp2)*/ cp1z * cp2z >= 0) return true;
	else return false;
}

// return z coordinates as if a and b were 3D vectors with 0 in Z
float crossProductZ(Vec2f a, Vec2f b)
{
	return (a.x*b.y) - (a.y*b.x);
}

float dotProduct(Vec2f a, Vec2f b)
{
	return (a.x*b.x) + (a.y*b.y);
}