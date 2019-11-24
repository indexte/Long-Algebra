#pragma once
#include "Point.h"
#include "BigNumber.h"
#include <limits>


class ElipticCurve {
private:
	BigNumber A;
	BigNumber B;
	BigNumber N;

	Point getPointWithN(Point point);
public:
	ElipticCurve(BigNumber A, BigNumber B, BigNumber N):A(A),B(B),N(N) {
		//set N in case user haven't done it
		this->A.setN(N.to_string());
		this->B.setN(N.to_string());

		BigNumber discriminant = BigNumber("16",N.to_string()) * (BigNumber("4",N.to_string()) * A*A*A + BigNumber("27",N.to_string()) * B*B);
		if (discriminant == BigNumber("0",N.to_string())) {
			throw new std::invalid_argument("Discriminant cannot be equal 0");
		}
	}

	BigNumber getA();
	BigNumber getB();
	BigNumber getN();

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

BigNumber ElipticCurve::getN() {
	return N;
}

/**
*@brief adds two points a and b
*@return sum of two points a and b.
*@throw invalid_argument if one of the points is not on the curve
*/
Point ElipticCurve::addPoints(Point a, Point b) {
	a = getPointWithN(a);
	b = getPointWithN(b);

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

	BigNumber lambda("0",N.to_string());
	if (a.getX() == b.getX()) {
		//lambda=(3*a^2+A)/(2*y1) mod N
		lambda = (BigNumber("3",N.to_string()) * a.getX()*a.getX() + A)/ (BigNumber("2",N.to_string()) * a.getY());
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

/**
*@return inverse point
*@throw invalid_argument if point is not on the curve
*/
Point ElipticCurve::getInversePoint(Point a) {
	a = getPointWithN(a);

	if (!isPointOnCurve(a)) {
		throw new std::invalid_argument("Some of the points are not on the curve");
	}

	return Point(a.getX(),-a.getY());
}

/**
*@brief checks if point is on curve
*@return true if point is on the curve, otherwise false
*/
bool ElipticCurve::isPointOnCurve(Point a) {
	a = getPointWithN(a);

	BigNumber k = a.getY()*a.getY();
	if (a.getY()*a.getY() != a.getX()*a.getX()*a.getX() + A * a.getX() + B)
		return false;
	if (a.getX() >= N || a.getY()>=N)
		return false;

	return true;
}

/**
*@brief sets N to the coordinates of the point
*@return point with correct N
*This function is created to allow users pass points without setting N to their coordinates.
*/
Point ElipticCurve::getPointWithN(Point point) {
	BigNumber x = point.getX();
	x.setN(N.to_string());
	BigNumber y = point.getY();
	y.setN(N.to_string());
	return Point(x, y);
}