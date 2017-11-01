//============================================================================
// Name        : CeoCoordinatesCPP.cpp
// Author      : JP Embedded Solutions Limited
// Version     :
// Copyright   : Copyright  2017 JP Embedded Solutions Limited
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include "test.hpp"

using namespace std;

CppUnit::Test *makeSuite() {
	auto suite = new CppUnit::TestSuite( "Mapping Test Suite" );
	suite->addTest( new CppUnit::TestCaller<GridToLatLong>("Grid to LatLong",&GridToLatLong::testAction ) );
//	suite->addTest( new CppUnit::TestCaller<LatLongToGrid>("LatLong to Grid",&LatLongToGrid::testAction ) );
	return suite;
}

int main() {
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( makeSuite() );
	runner.run();
	return 0;
}
