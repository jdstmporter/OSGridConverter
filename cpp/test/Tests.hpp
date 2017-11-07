/*
 * Tests.hpp
 *
 *  Created on: 1 Nov 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_TESTS_HPP_
#define SRC_TESTS_TESTS_HPP_

#include <TestBase.hpp>
#include <string>

namespace test {




class GridToLatLong : public TestBase {

public:
	GridToLatLong(const mapping::Datum::Name &tag,const int nTests,const bool verbose) :
		TestBase("Grid To LatLong test",tag,nTests,verbose) {};
	virtual ~GridToLatLong() = default;
protected:
	virtual int action();
};

class GridToLatLongViaText : public TestBase {

public:
	GridToLatLongViaText(const mapping::Datum::Name &tag,const int nTests,const bool verbose) :
		TestBase("Grid To LatLong (via text) test",tag,nTests,verbose) {};
	virtual ~GridToLatLongViaText() = default;
protected:
	virtual int action();
};

class LatLongToGrid : public TestBase {

public:
	LatLongToGrid(const mapping::Datum::Name &tag,const int nTests,const bool verbose) :
		TestBase("LatLong to Grid test",tag,nTests,verbose) {};
	virtual ~LatLongToGrid() = default;
protected:
	virtual int action();
};



} /* namespace tests */

#endif /* SRC_TESTS_TESTS_HPP_ */
