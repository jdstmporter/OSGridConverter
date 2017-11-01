/*
 * TestBase.hpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_TESTBASE_HPP_
#define SRC_TESTS_TESTBASE_HPP_

#include <cppunit/TestCase.h>
#include <list>
#include <string>
#include <mapping.hpp>
#include "Generator.hpp"

namespace test {

class ConversionTestBase : public CppUnit::TestCase {
private:
	int nTests;
	std::list<double> errors;
	int good;
	int count;
	int crashes;
	
protected:
	Generator generator;
	mapping::Datum::Name tag;
	int push(double error,double threshold=10.0);
	virtual int action() { return 1; };
	
	
public:
	ConversionTestBase(std::string name) : CppUnit::TestCase(name), generator(), tag(mapping::Datum::Name::WGS84), nTests(1000),errors(), good(0), count(0),crashes(0) {};
	virtual ~ConversionTestBase() = default;
	
	virtual void setUp() {};
	virtual void tearDown() {};
	void testAction();

};

} /* namespace test */

#endif /* SRC_TESTS_TESTBASE_HPP_ */
