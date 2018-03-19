/*
 * Suite.hpp
 *
 *  Created on: 1 Nov 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_SUITE_HPP_
#define SRC_TESTS_SUITE_HPP_

#include <iostream>
#include <cppunit/TestSuite.h>

namespace test {

class ConverterTestSuite {
private:
	CppUnit::TestSuite * suite;

public:
	ConverterTestSuite();
	virtual ~ConverterTestSuite() = default;

	void run();
};


} /* namespace test */

#endif /* SRC_TESTS_SUITE_HPP_ */
