#include <iostream>
#include "LongOperations.h"
using namespace std;

int main() {

	string N = "1000000000";
	BigNumber n1("123456789", N);
	n1.printBigNumber();

	BigNumber n2("987654321", N);
	n2.printBigNumber();
	
	BigNumber n3 = n1 - n2;
	n3.printBigNumber();

	n3.setBigNumber(n2 + n1);
	n3.printBigNumber();
	
	cin.get();
	return 0;
}