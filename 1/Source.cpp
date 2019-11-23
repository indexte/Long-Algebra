#include <iostream>
#include "BigNumber.h"

int main()
{
	BigNumber n1("15", "23");
	n1.printBigNumber();
	BigNumber n2("7", "23");
	n2.printBigNumber();
	std::cout << std::endl;
	BigNumber n3 = n1 / n2;
	n3.printBigNumber();
}