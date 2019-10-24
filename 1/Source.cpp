#include <iostream>
#include "LongOperations.h"
using namespace std;

int main() {

	int N = 20;
	BigNumber n1("-2033", N);
	n1.printBigNumber();

	BigNumber n2("-20", N);
	n2.printBigNumber();
	
	BigNumber n3 = n2 - n1;
	n3.printBigNumber();

	n3.setBigNumber(n2 + n1);
	n3.printBigNumber();
	
	cin.get();
	return 0;
}