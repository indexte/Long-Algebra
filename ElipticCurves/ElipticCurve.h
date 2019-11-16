#pragma once
#include "Point.h"
#include <limits>


class ElipticCurve {
private:
	long long A;
	long long B;
	long long N;

	long long calculateDivision(long long top, long long bottom);

	long long modN(long long number);
	long long getInverseNumber(long long a);

public:
	ElipticCurve(long long A, long long B,long long N):A(A),B(B),N(N) {
		long long discriminant = -16 * (4 * A*A*A + 27 * B*B);
		if (discriminant == 0) {
			throw new std::invalid_argument("Discriminant cannot be equal 0");
		}
	}

	long long getA();
	long long getB();

	Point addPoints(Point a, Point b);
	Point getInversePoint(Point a);
	bool isPointOnCurve(Point a);

	bool isInfinitePoint(Point a);
	Point getInfinitePoint();

};

long long ElipticCurve::getInverseNumber(long long a) {
	long long first = 0;
	long long second = 1;
	long long third = 0;
	long long x = N;
	long long y = a;
	while (x != 0 && y != 0) {
		if (x < y)
			std::swap(x, y);
		if (y == 1)
			break;
		int div = x / y;
		third = first - div * second;
		first = second;
		second = third;
		x %= y;
	}

	return modN(third);
}

long long ElipticCurve::calculateDivision(long long top, long long bottom) {
	bottom = getInverseNumber(bottom);
	return modN(top*bottom);
}

long long ElipticCurve::getB() {
	return B;
}

long long ElipticCurve::getA() {
	return A;
}

//what if we have negative? 
Point ElipticCurve::addPoints(Point a, Point b) {
	if (a == getInfinitePoint())
		return b;

	if (b == getInfinitePoint())
		return a;

	if (!isPointOnCurve(a) || !isPointOnCurve(b)) {
		throw new std::invalid_argument("Some of the points are not on the curve");
	}

	//A+(-A)=O
	if (a == getInversePoint(b)) {
		return getInfinitePoint();
	}

	long long lambda;
	if (a.getX() == b.getX()) {
		//lambda=(3*a^2+A)/(2*y1) mod N
		lambda = modN(calculateDivision(modN(3 * a.getX()*a.getX() + A), modN(2 * a.getY())));
	}
	else {
		//lambda=(y2-y1)/(x2-x1) mod N
		lambda = modN(calculateDivision(modN(b.getY() - a.getY()), modN(b.getX() - a.getX())));
	}

	//x=lambda*lambda-x1-x2 mod N
	long long x = modN(lambda*lambda - a.getX() - b.getX());
	//y=lambda*(x1-x)-y1
	long long y = modN(lambda * (a.getX() - x) - a.getY());

	return Point(x, y);
}

Point ElipticCurve::getInversePoint(Point a) {
	if (!isPointOnCurve(a)) {
		throw new std::invalid_argument("Some of the points are not on the curve");
	}

	return Point(a.getX(), modN(-a.getY()));
}

bool ElipticCurve::isPointOnCurve(Point a) {
	if (modN((a.getY()*a.getY())) != (modN(a.getX()*a.getX()*a.getX() + A * a.getX() + B)))
		return false;
	if (a.getX() < 0 || a.getX() > N)
		return false;

	return true;
}

long long ElipticCurve::modN(long long number) {
	number %= N;
	if (number < 0)
		number = number + N;
	return number;
}

bool ElipticCurve::isInfinitePoint(Point a) {
	return a == getInfinitePoint();
}

Point ElipticCurve::getInfinitePoint() {
	return Point(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::max());
}
