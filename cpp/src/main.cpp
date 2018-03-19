//============================================================================
// Name        : CeoCoordinatesCPP.cpp
// Author      : JP Embedded Solutions Limited
// Version     :
// Copyright   : Copyright  2017 JP Embedded Solutions Limited
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "tests/Suite.hpp"



int main() {

	try {
		test::ConverterTestSuite suite;
		suite.run();
	}
	catch(std::exception &e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}
