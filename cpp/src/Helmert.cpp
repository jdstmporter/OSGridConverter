/*
 * Helmert.cpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#include "Helmert.hpp"
#include <stdexcept>
#include <algorithm>



namespace mapping {




std::valarray<unsigned> Helmert::indices(const unsigned index) {
	auto i1=(index+1)%3;
	auto i2=(index+2)%3;
	return std::valarray<unsigned> {i1, i2};
}

util::Matrix Helmert::matrix(const util::Vector & r,const double s) {
	util::Matrix m(3,s);
	for(int i=0;i<3;i++) {
		auto jk = Helmert::indices(i);
		auto v=r(i);
		m(jk[0],jk[1])= v;
		m(jk[1],jk[0])=-v;
	}
	return m;
}

util::Matrix Helmert::inverseMatrix(const util::Vector & r,const double s) {
	auto d=1.0/(s*((r|r)+s*s));
	return (Helmert::matrix(-r,s)*s + outer_prod(r,r))*d;
}


Helmert::Helmert(const util::Vector & T,const util::Vector & R, const double S) : t(T),
		mx(Helmert::matrix(R,S+1.0)), inv(Helmert::inverseMatrix(R,S+1.0))  {}

Helmert & Helmert::operator=(const Helmert &o) {
	t=o.t;
	mx=o.mx;
	inv=o.inv;
	return *this;
}


Helmert Helmert::inverse() const {
	auto it  = -util::prod(inv,t);
	return Helmert(it,inv,mx);
}

util::Vector Helmert::operator()(const util::Vector &x) const {
	return util::prod(mx,x)+t;
}
//util::Vector Helmert::operator()(util::Vector &&x) const {
//	return util::prod(mx,x)+t;
//}





bool operator==(const Helmert &l,const Helmert &r) {
	return (l.t==r.t) && (l.mx==r.mx);
}
bool operator!=(const Helmert &l,const Helmert &r){
	return (l.t!=r.t) || (l.mx!=r.mx);
}

} /* namespace mapping */


  
