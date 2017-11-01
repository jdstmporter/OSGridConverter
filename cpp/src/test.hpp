/*
 * test.hpp
 *
 *  Created on: 29 Jul 2017
 *      Author: julianporter
 */

#ifndef TEST_HPP_
#define TEST_HPP_

#include <tests/TestBase.hpp>
#include <string>


class GridToLatLong : public test::ConversionTestBase {

public:
	GridToLatLong(std::string name="Grid To LatLong test") : test::ConversionTestBase(name) {};
	virtual ~GridToLatLong() = default;
protected:
	virtual int action();
};

class GridToLatLongViaText : public test::ConversionTestBase {

public:
	GridToLatLongViaText(std::string name="Grid To LatLong (via text) test") : test::ConversionTestBase(name) {};
	virtual ~GridToLatLongViaText() = default;
protected:
	virtual int action();
};
	

	

        
   
     
    
           
    


#endif /* TEST_HPP_ */
