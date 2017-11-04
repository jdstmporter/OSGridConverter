//============================================================================
// Name        : CeoCoordinatesCPP.cpp
// Author      : JP Embedded Solutions Limited
// Version     :
// Copyright   : Copyright  2017 JP Embedded Solutions Limited
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <TestBase.hpp>
#include <Suite.hpp>
#include <Tests.hpp>
#include <iostream>
#include <string>

const int NTests=1000;



int main(int argc,char *argv[]) {


	try {
		int nTests=1000;
		bool verbose=false;

		if(argc>=2) {
			try {
				nTests=std::stol(argv[1]);
			}
			catch(...) {}
		}
		if(argc>=3) {
			try {
				int n=std::stol(argv[2]);
				verbose=(n!=0);
			}
			catch(...) {}
		}

		test::TestSuite suite(nTests,verbose);
		suite.add<test::GridToLatLong>();
		suite.add<test::LatLongToGrid>();
		suite.add<test::GridToLatLongViaText>();

		test::test_t t=suite[(int)TEST_INDEX];
		t->run();

		std::cout << *t;
		return (t->success()) ? 0 : 1;
	}
	catch(...) {
		return 99;
	}
}
