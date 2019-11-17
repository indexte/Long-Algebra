#pragma once
#include "Point.h"
#include "LongOperations.h"
#include <limits>


class ElipticCurve {
private:
	BigNumber A;
	BigNumber B;
	BigNumber N;
public:
	ElipticCurve(BigNumber A, BigNumber B, BigNumber N):A(A),B(B),N(N) {
		BigNumber discriminant = BigNumber("16",N.getN()) * (BigNumber("4",N.getN()) * A*A*A + BigNumber("27",N.getN()) * B*B);
		if (discriminant == BigNumber("0",N.getN())) {
			throw new std::invalid_argument("Discriminant cannot be equal 0");
		}
	}

	BigNumber getA();
	BigNumber getB();

	Point addPoints(Point a, Point b);
	Point getInversePoint(Point a);
	bool isPointOnCurve(Point a);

};

BigNumber ElipticCurve::getB() {
	return B;
}

BigNumber ElipticCurve::getA() {
	return A;
}

//what if we have negative? 
Point ElipticCurve::addPoints(Point a, Point b) {
	if (a.isInfinitePoint())
		return b;

	if (b.isInfinitePoint())
		return a;

	if (!isPointOnCurve(a) || !isPointOnCurve(b)) {
		throw new std::invalid_argument("Some of the points are not on the curve");
	}

	//A+(-A)=O
	if (a == getInversePoint(b)) {
		return Point::getInfinitePoint();
	}

	BigNumber lambda("0",N.getN());
	if (a.getX() == b.getX()) {
		//lambda=(3*a^2+A)/(2*y1) mod N
		lambda = (BigNumber("3",N.getN()) * a.getX()*a.getX() + A)/ (BigNumber("2",N.getN()) * a.getY());
	}
	else {
		//lambda=(y2-y1)/(x2-x1) mod N
		lambda = (b.getY() - a.getY())/ (b.getX() - a.getX());
	}

	//x=lambda*lambda-x1-x2 mod N
	BigNumber x = lambda*lambda - a.getX() - b.getX();
	//y=lambda*(x1-x)-y1
	BigNumber y = lambda * (a.getX() - x) - a.getY();

	return Point(x, y);
}

Point ElipticCurve::getInversePoint(Point a) {
	if (!isPointOnCurve(a)) {
		throw new std::invalid_argument("Some of the points are not on the curve");
	}

	return Point(a.getX(),-a.getY());
}

bool ElipticCurve::isPointOnCurve(Point a) {
	BigNumber k = a.getY()*a.getY();
	if (a.getY()*a.getY() != a.getX()*a.getX()*a.getX() + A * a.getX() + B)
		return false;
	if (BigNumber("0",N.getN())> a.getX() || a.getX() > N)
		return false;

	return true;
}
