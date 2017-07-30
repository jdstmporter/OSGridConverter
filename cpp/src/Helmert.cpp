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

Matrix HelmertMatrix::rsMatrix(const Vector & r,const double s) {
	if(r.size()!=3) throw std::length_error("vector must have length 3 in Helmert Matrix");
	Matrix m = s*ID(3);
	for(unsigned i=0;i<3;i++) {
		auto j=(i+1)%3;
		auto k=(i+2)%3;
		auto v=r(i);
		m(j,k)=v;
		m(k,j)=-v;
	}
	return m;
}

double HelmertMatrix::determinant() { return s*(inner_prod(r,r)+s*s); }

HelmertMatrix HelmertMatrix::inverse() {
	Matrix ix=HelmertMatrix::rsMatrix(-r,s)*s + outer_prod(r,r);
	double d=1.0/determinant();
	return HelmertMatrix(ix*d);
}

HelmertMatrix & HelmertMatrix::operator=(const HelmertMatrix &other) {
	r=other.r;
	s=other.s;
	mx=other.mx;
	return *this;
}

Vector operator*(const HelmertMatrix &h,const Vector &v) {
	prod(h.mx,v);
}



Helmert::Helmert() {
	// TODO Auto-generated constructor stub

}

Helmert::~Helmert() {
	// TODO Auto-generated destructor stub
}

} /* namespace mapping */


  