/*
 * ExactHelmert.cpp
 *
 *  Created on: 1 Mar 2018
 *      Author: julianporter
 */

#include "Helmert.hpp"

namespace mapping {





Helmert::Helmert(const Vector & o,const Vector & a, const double s_) : offset(o), angles(a), scale(s_) {

	Matrix matrix=ZMatrix(3);
	matrix(0,0)= c(0)*c(1);
	matrix(0,1)=-s(0)*c(2)-c(0)*s(1)*s(2);
	matrix(0,2)= s(0)*s(2)-c(0)*s(1)*c(2);
	matrix(1,0)= s(0)*c(1);
	matrix(1,1)= c(0)*c(2)-s(0)*s(1)*s(2);
	matrix(1,2)=-c(0)*s(2)-s(0)*s(1)*c(2);
	matrix(2,0)= s(1);
	matrix(2,1)= c(1)*s(2);
	matrix(2,2)= c(1)*c(2);

	mx=matrix * scale;
	invMx=transpose(matrix) * (1.0/scale);
}

Vector Helmert::transform(Vector x) const {
	return prod(mx,x)+offset;
}

Vector Helmert::inverseTransform(Vector x) const {
	return prod(invMx,x-offset);
}

bool Helmert::eq(const Helmert &o) const {
	return scale==o.scale && offset==o.offset && angles==o.angles;
}





} /* namespace mapping */

