/*
 * ALgebraTests.hpp
 *
 *  Created on: 3 Nov 2017
 *      Author: julianporter
 */

#ifndef TEST_ALGEBRATESTS_HPP_
#define TEST_ALGEBRATESTS_HPP_

#include <TestBase.hpp>

namespace test {

class VectorEquality : public TestBase {
public:
	VectorEquality(const int nTests,const bool verbose) :
		TestBase("Vector Equality",nTests,verbose) {};
	virtual ~VectorEquality() = default;
protected:
	virtual int action();


};

class VectorCopy : public TestBase {
public:
	VectorCopy(const int nTests,const bool verbose) :
		TestBase("Vector Copy",nTests,verbose) {};
	virtual ~VectorCopy() = default;
protected:
	virtual int action();


};

} /* namespace test */

#endif /* TEST_ALGEBRATESTS_HPP_ */
