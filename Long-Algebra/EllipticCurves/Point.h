#pragma once
#include "../BigNumber/BigNumber.h"

class Point {
private:
	BigNumber x;
	BigNumber y;
	bool isInfinite;
public:

	static Point getInfinitePoint() {
		Point point = Point(BigNumber("0"), BigNumber("0"));
		point.isInfinite = true;
		return point;
	}

	Point(BigNumber x, BigNumber y) :x(x), y(y), isInfinite(false) {

	}

	Point(string x, string y) :x(BigNumber(x)), y(BigNumber(y)), isInfinite(false)
	{

	}

	BigNumber getX() {
		return x;
	}

	BigNumber getY() {
		return y;
	}

	bool isInfinitePoint() {
		return isInfinite;
	}

	bool operator==(const Point& point) {
		return x == point.x && y == point.y;
	}
};
