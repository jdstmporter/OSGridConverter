/*
 * TestBase.cpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#include <TestBase.hpp>
#include <sstream>
#include <algorithm>

namespace test {

int TestBase::push(double error,double threshold) {
	errors.push_back(error);
	return (error>threshold) ? 1 : 0;
}

void TestBase::run() {
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

}

std::string TestBase::report() const {
	std::stringstream s;
	s << "Test " << name << ": ";
	if (success()) s << "PASSED";
	else s << "FAILED";
	s << " " << good << " / " << nTests << " ";
	if(verbose) {
		if(errors.empty()) s << ", "<< crashes << " crashed";
		else {
			auto e=std::min_element(errors.begin(),errors.end());
			s << " with minimum log10 error = " << *e << ", " << crashes << " crashed";
		}
	}
	return s.str();
}




} /* namespace test */

std::ostream & operator<<(std::ostream & o,const test::TestBase &t) {
	 o << t.report();
	 return o;
}
