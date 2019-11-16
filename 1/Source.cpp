#include <iostream>
#include "LongOperations.h"
int main()
{
	BigNumber n1("10", "15");
	n1.printBigNumber();
	BigNumber n2("7", "15");
	n2.printBigNumber();
	std::cout << std::endl;
	BigNumber n3 = n1 / n2;
	n3.printBigNumber();

}