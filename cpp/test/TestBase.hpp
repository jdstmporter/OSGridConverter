/*
 * TestBase.hpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_TESTBASE_HPP_
#define SRC_TESTS_TESTBASE_HPP_


#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <geoconv.hpp>
#include <Generator.hpp>

namespace test {

class TestBase {
private:
	std::string name;
	int nTests;

	std::list<double> errors;
	int good;
	int count;
	int crashes;
	
protected:
	bool verbose;
	Generator generator;
	mapping::Datum::Name tag;
	int push(double error,double threshold=10.0);
	virtual int action() { return 1; };
	




public:
	TestBase(const std::string &name_,const int n, const bool v) :
		name(name_), nTests(n), errors(), good(0), count(0),crashes(0),
		verbose(v), generator(), tag(mapping::Datum::Name::OSGB36) {};
	virtual ~TestBase() = default;
	
	virtual void setUp() {};
	virtual void tearDown() {};
	void run();
	bool success() const { return (good == count); };
	std::string report() const;
};




} /* namespace test */

std::ostream & operator<<(std::ostream & o,const test::TestBase &t);

#endif /* SRC_TESTS_TESTBASE_HPP_ */
