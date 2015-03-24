#include "common.h"


float dist(const Vec2f p1, const Vec2f p2) {
	return hypotf(p2.x - p1.x, p2.y - p1.y);
};