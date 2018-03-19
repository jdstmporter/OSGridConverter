/*
 * Tests.hpp
 *
 *  Created on: 1 Nov 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_TESTS_HPP_
#define SRC_TESTS_TESTS_HPP_

#include "TestBase.hpp"
#include <string>

namespace test {




class GridToLatLong : public ConversionTestBase {

public:
	GridToLatLong(std::string name="Grid To LatLong test") : ConversionTestBase(name) {};
	virtual ~GridToLatLong() = default;
protected:
	virtual int action();
};

class GridToLatLongViaText : public ConversionTestBase {

public:
	GridToLatLongViaText(std::string name="Grid To LatLong (via text) test") : ConversionTestBase(name) {};
	virtual ~GridToLatLongViaText() = default;
protected:
	virtual int action();
};

class LatLongToGrid : public ConversionTestBase {

public:
	LatLongToGrid(std::string name="LatLong to Grid test") : ConversionTestBase(name) {};
	virtual ~LatLongToGrid() = default;
protected:
	virtual int action();
};

} /* namespace tests */

#endif /* SRC_TESTS_TESTS_HPP_ */
