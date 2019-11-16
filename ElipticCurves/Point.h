#pragma once

class Point {
private:
	long long x;
	long long y;
public:

	Point(long long x, long long y) :x(x), y(y) {

	}

	long long getX() {
		return x;
	}

	long long getY() {
		return y;
	}

	bool operator==(const Point& point) {
		return x == point.x && y == point.y;
	}
};
