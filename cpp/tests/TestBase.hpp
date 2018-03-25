/*
 * TestBase.hpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_TESTBASE_HPP_
#define SRC_TESTS_TESTBASE_HPP_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <list>
#include <string>
#include <type_traits>
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
	bool verbose;
	Generator generator;
	mapping::DatumName tag;
	int push(double error,double threshold=10.0);
	virtual int action() { return 1; };
	
	
public:
	ConversionTestBase(std::string name,bool verbose_ = false) : CppUnit::TestCase(name),  nTests(1000),errors(), good(0), count(0),crashes(0), verbose(verbose_), generator(), tag(mapping::DatumName::OSGB36) {};
	virtual ~ConversionTestBase() = default;
	
	virtual void setUp() {};
	virtual void tearDown() {};
	void testAction();

};



} /* namespace test */

#endif /* SRC_TESTS_TESTBASE_HPP_ */
