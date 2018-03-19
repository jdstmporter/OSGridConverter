/*
 * Suite.cpp
 *
 *  Created on: 1 Nov 2017
 *      Author: julianporter
 */

#include "Suite.hpp"
#include "Tests.hpp"
#include <cppunit/Test.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

namespace test {

ConverterTestSuite::ConverterTestSuite() {
	suite = new CppUnit::TestSuite( "Mapping Test Suite" );
	suite->addTest( new CppUnit::TestCaller<GridToLatLong>("Grid to LatLong",&GridToLatLong::testAction ) );
	suite->addTest( new CppUnit::TestCaller<GridToLatLongViaText>("Grid to LatLong via text",&GridToLatLongViaText::testAction ) );
	suite->addTest( new CppUnit::TestCaller<LatLongToGrid>("LatLong to Grid",&LatLongToGrid::testAction ) );
}



void ConverterTestSuite::run() {
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);
	runner.run();
}


} /* namespace test */
