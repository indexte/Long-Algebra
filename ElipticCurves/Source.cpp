#include <iostream>
#include "ElipticCurve.h"
#include "../1/BigNumber.h"
#include "Point.h"
#include "PointExponentiation.h"

using namespace std;

//check out this literature. It will help a lot:
//https://studref.com/403745/informatika/algoritmy_osnove_ellipticheskih_krivyh
//https://people.cs.nctu.edu.tw/~rjchen/ECC2012S/Elliptic%20Curves%20Number%20Theory%20And%20Cryptography%202n.pdf
int main() {
	Point a = Point(BigNumber("13"), BigNumber("7"));
	Point b = Point(BigNumber("3"), BigNumber("10"));

	//A=1,B=1,N=23
	ElipticCurve curve = ElipticCurve(BigNumber("1"), BigNumber("1"), BigNumber("23"));

	Point sumAB = curve.addPoints(a, b);

	cout << "Sum two points (13,7) and (3,10)" << endl;
	cout << sumAB.getX() << " " << sumAB.getY() << endl;

	Point minusA = curve.getInversePoint(a);
	cout << "Get -a" << endl;
	cout << minusA.getX() << " " << minusA.getY() << endl;

	Point infinitePoint = curve.addPoints(a, minusA);
	cout << "Infinite point" << endl;
	cout << infinitePoint.getX() << " " << infinitePoint.getY()<<endl;

	cout << "Check if point is infinite" << endl;
	cout << infinitePoint.isInfinitePoint() << endl;

    //-----------------------------------------------
    BigNumber degree = BigNumber("2", curve.getN().to_string());
    Point aInDegree = exponentiation(curve, a, degree);
    cout << "Point (13,7) in degree 2: "<< endl;
    cout << aInDegree.getX() << " " << aInDegree.getY() << endl;

    degree = BigNumber("5", curve.getN().to_string());
    aInDegree = exponentiation(curve, a, degree);
    cout << "Point (13,7) in degree 5: "<< endl;
    cout << aInDegree.getX() << " " << aInDegree.getY() << endl;

    degree = BigNumber("7", curve.getN().to_string());
    aInDegree = exponentiation(curve, a, degree);
    cout << "Point (13,7) in degree 7: "<< endl;
    cout << aInDegree.getX() << " " << aInDegree.getY() << endl;

    return 0;
}
