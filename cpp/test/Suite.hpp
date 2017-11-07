/*
 * Suite.hpp
 *
 *  Created on: 1 Nov 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_SUITE_HPP_
#define SRC_TESTS_SUITE_HPP_

#include <TestBase.hpp>
#include <vector>
#include <memory>
#include <iostream>

namespace test {

using test_t = std::shared_ptr<test::TestBase>;

class TestSuite {
private:
	mapping::Datum::Name tag;
	std::vector<test_t> tests;
	int nTests;
	bool verbose;

public:
	TestSuite(const mapping::Datum::Name &tag_=mapping::Datum::Name::WGS84,const int nTests_=1000,const bool verbose_=false) :
		tag(tag_), tests(), nTests(nTests_), verbose(verbose_) {}
	virtual ~TestSuite() = default;

	template<class T>
	void add() {
		auto p=std::make_shared<T>(tag,nTests,verbose);
		auto pp=std::static_pointer_cast<TestBase>(p);
		tests.push_back(pp);
	}

	void run();
	test_t operator[](const int n) { return tests[n]; }
	std::ostream & report(std::ostream &o) const;
};




} /* namespace test */

std::ostream & operator<<(std::ostream &o,const test::TestSuite &suite);

#endif /* SRC_TESTS_SUITE_HPP_ */
