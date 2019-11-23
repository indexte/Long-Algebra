#include <iostream>
#include "ElipticCurve.h"
#include "BigNumber.h"
#include "Point.h"

using namespace std;

//check out this literature. It will help a lot:
//https://studref.com/403745/informatika/algoritmy_osnove_ellipticheskih_krivyh
//https://people.cs.nctu.edu.tw/~rjchen/ECC2012S/Elliptic%20Curves%20Number%20Theory%20And%20Cryptography%202n.pdf
int main() {
	Point a = Point(BigNumber("13","23"), BigNumber("7","23"));
	Point b = Point(BigNumber("3", "23"), BigNumber("10", "23"));

	//A=1,B=1,N=23
	ElipticCurve curve = ElipticCurve(BigNumber("1","23"), BigNumber("1","23"), BigNumber("23"));

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

	system("pause");
}
