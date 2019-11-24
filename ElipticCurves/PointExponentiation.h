#pragma once
#include "ElipticCurve.h"
#include "Point.h"
#include "../1/BigNumber.h"

Point exponentiation (ElipticCurve& curve, Point a, BigNumber& k) { //Point A in degree k

    if (!(k >= BigNumber("0", k.getN()))) {
        throw std::invalid_argument("Degree cannot be 0 or lower");
    }

    //k = k % (A point order);
    if (k == BigNumber("0")) {return Point::getInfinitePoint();}

    Point b = Point::getInfinitePoint();

    while (k != BigNumber("0", k.getN())) {
        if (k % BigNumber("2",k.getN()) == BigNumber("0", k.getN())) {
            k = k / BigNumber("2",k.getN());
            a = curve.addPoints(a,a);
        } else {
            k = k - BigNumber("1",k.getN());
            b = curve.addPoints(b,a);
        }
    }

    return b;
}