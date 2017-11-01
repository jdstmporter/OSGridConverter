/*
 * TestBase.cpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#include <tests/TestBase.hpp>
#include <iostream>

namespace test {

int ConversionTestBase::push(double error,double threshold) {
	errors.push_back(error);
	return (error>threshold) ? 1 : 0;
}

void ConversionTestBase::testAction() {
	for(auto i=0;i<nTests;i++) {
		try {
			good+=action();
			count++;
		}
		catch(std::exception &e) {
			std::cerr << "Exception on test " << i << " : " << e.what() << std::endl;
			crashes++;
		}
	}
	if(errors.empty()) {
		std::cout << nTests << " tests : count = " << count << " good = " << good << " crashes = " << crashes << std::endl;
	}
	else {
		auto e=std::min_element(errors.begin(),errors.end());
		std::cout << nTests << " tests : count = " << count << " good = " << good <<
				" minimum log10 error = " << *e << " crashes = " << crashes << std::endl;
	}
	CPPUNIT_ASSERT( good == count );
}

} /* namespace test */
