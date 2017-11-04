/*
 * ALgebraTests.cpp
 *
 *  Created on: 3 Nov 2017
 *      Author: julianporter
 */

#include "AlgebraTests.hpp"

namespace test {

bool equal(const util::Vector & v1,const util::Vector &v2) {
	if(v1.size()!=v2.size()) return false;
	bool good=true;
	for(auto i=0;i<v1.size();i++) good&=(v1(i)==v2(i));
	return good;
}

int VectorEquality::action() {
	auto v1=generator.vector();
	auto v2=generator.vector();

	bool predicted=(v1==v2);
	bool actual=equal(v1,v2);
	return (predicted==actual) ? 1 : 0;
}

int VectorCopy::action() {
	auto v=generator.vector();
	std::vector<double> copy(v.size(),0.0);
	for(auto i=0;i<v.size();i++) copy[i]=v(i);
	auto w=std::move(v);
	util::Vector z(copy);
	return equal(w,z) ? 1 : 0;
}

} /* namespace test */
