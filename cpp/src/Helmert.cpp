/*
 * Helmert.cpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#include "Helmert.hpp"
#include <stdexcept>

using namespace boost::numeric::ublas;

namespace mapping {


std::valarray<unsigned> Helmert::indices(const unsigned index) {
	auto i1=(index+1)%3;
	auto i2=(index+2)%3;
	return std::move(std::valarray<unsigned> {i1, i2});
}

Matrix Helmert::matrix(const Vector & r,const double s) {
	Matrix m = s*ID(3);
	for(auto i=0;i<3;i++) {
		auto jk = Helmert::indices(i);
		auto v=r(i);
		m(jk[0],jk[1])= v;
		m(jk[1],jk[0])=-v;
	}
	return std::move(m);
}

Matrix Helmert::inverseMatrix(const Vector & r,const double s) {
	auto d=1.0/(s*(inner_prod(r,r)+s*s));
	return std::move((Helmert::matrix(-r,s)*s + outer_prod(r,r))*d);
}


Helmert::Helmert(const Vector & T,const Vector & R, const double S) : t(T)  {
	mx=Helmert::matrix(R,S+1.0);
	inv=Helmert::inverseMatrix(R,S+1.0);
}

Helmert & Helmert::operator=(const Helmert &o) {
	t=o.t;
	mx=o.mx;
	inv=o.inv;
	return *this;
}


Helmert Helmert::inverse() {
	auto it  = -prod(inv,t);
	return std::move(Helmert(it,inv,mx));
}

Vector Helmert::operator()(Vector x) {
	return std::move(prod(mx,x)+t);
}



} /* namespace mapping */


  
