/*
 * Suite.cpp
 *
 *  Created on: 1 Nov 2017
 *      Author: julianporter
 */

#include <Suite.hpp>
#include <Tests.hpp>
#include <algorithm>

namespace test {

void TestSuite::run() {
	std::for_each(tests.begin(),tests.end(),[](test_t test) { test->run(); });
}


std::ostream & TestSuite::report(std::ostream &o) const {
	int successes = std::count_if(tests.begin(),tests.end(),[](test_t test) {
		return test->success();
	});
	o << "Executed all " << tests.size() << " tests " << successes << " succeeded" << std::endl;
	std::for_each(tests.begin(),tests.end(),[&o](test_t test) { o << *test << std::endl; });
	return o;
}





} /* namespace test */

std::ostream & operator<<(std::ostream &o,const test::TestSuite &suite) {
	return suite.report(o);
}
