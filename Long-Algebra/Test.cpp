#include <iostream>
#include <string>
#include <vector>
#include "BigNumber/BigNumber.h"
#include "EllipticCurves/ElipticCurve.h"

int main() {
	BigNumber a ("16", "17");
	(a+a).printBigNumber();
	system("PAUSE");
	return 0;
}