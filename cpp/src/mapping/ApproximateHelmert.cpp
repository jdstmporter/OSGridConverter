/*
 * ApproximateHelmert.cpp
 *
 *  Created on: 1 Mar 2018
 *      Author: julianporter
 */

#include "ApproximateHelmert.hpp"

namespace mapping {
namespace helmert {

std::valarray<unsigned> ApproximateHelmert::indices(const unsigned index) {
	auto i1=(index+1)%3;
	auto i2=(index+2)%3;
	return std::move(std::valarray<unsigned> {i1, i2});
}

Matrix ApproximateHelmert::matrix(const Vector & r,const double s) const {
	Matrix m = s*ID(3);
	for(auto i=0;i<3;i++) {
		auto jk = ApproximateHelmert::indices(i);
		auto v=r(i);
		m(jk[0],jk[1])+= v;
		m(jk[1],jk[0])+=-v;
	}
	return std::move(m);
}



Vector ApproximateHelmert::invertedAngles() const {
	auto b=-angles;
	return std::move(b);
}




} /* namespace helmert */
} /* namespace mapping */
