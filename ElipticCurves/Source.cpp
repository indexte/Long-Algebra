#include <iostream>
#include "ElipticCurve.h"
#include "Point.h"

using namespace std;

//check out this literature. It will help a lot:
//https://studref.com/403745/informatika/algoritmy_osnove_ellipticheskih_krivyh
//https://people.cs.nctu.edu.tw/~rjchen/ECC2012S/Elliptic%20Curves%20Number%20Theory%20And%20Cryptography%202n.pdf
int main() {
	Point a = Point(13, 7);
	Point b = Point(3, 10);

	//A=1,B=1,N=23
	ElipticCurve curve = ElipticCurve(1, 1, 23);

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
	cout << curve.isInfinitePoint(infinitePoint) << endl;

	system("pause");
}