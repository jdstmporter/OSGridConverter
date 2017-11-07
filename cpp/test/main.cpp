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

const mapping::Datum::Name tag=mapping::Datum::Name::OSGB36;

bool isVerbose() {
#ifdef VERBOSE
	return bool(VERBOSE);
#else
	return false;
#endif
}

int NTests() {
#ifdef NTESTS
	return int(NTESTS);
#else
	return 1000;
#endif
}

int TestIndex() {
#ifdef TEST_INDEX
	return int(TEST_INDEX);
#else
	return 0;
#endif
}

int main(int argc,char *argv[]) {


	try {
		bool verbose=isVerbose();
		int nTests=NTests();
		int test=TestIndex();

		test::TestSuite suite(tag,nTests,verbose);
		suite.add<test::GridToLatLong>();
		suite.add<test::LatLongToGrid>();
		suite.add<test::GridToLatLongViaText>();

		test::test_t t=suite[test];
		t->run();

		std::cout << *t;
		return (t->success()) ? 0 : 1;
	}
	catch(...) {
		return 99;
	}
}
