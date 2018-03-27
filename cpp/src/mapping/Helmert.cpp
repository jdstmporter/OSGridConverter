/*
 * ExactHelmert.cpp
 *
 *  Created on: 1 Mar 2018
 *      Author: julianporter
 */

#include "Helmert.hpp"

#define EXACT 1

namespace mapping {

const double Helmert::AngleScale=PI/(3600.0*180.0);
const double Helmert::ScaleScale=1.0e-6;

Helmert::Helmert(const Vector & o,const Vector & a, const double s_) : offset(o), angles(Helmert::AngleScale*a), scale(s_*Helmert::ScaleScale) {
	double p=angles[0], q=angles[1], r=angles[2];

	Matrix matrix(3,3);

#ifdef EXACT
	double c0=cos(p),c1=cos(q),c2=cos(r);
	double s0=sin(p),s1=sin(q),s2=sin(r);

	matrix(0,0)= c0*c1;
	matrix(0,1)=-s0*c2-c0*s1*s2;
	matrix(0,2)= s0*s2-c0*s1*c2;
	matrix(1,0)= s0*c1;
	matrix(1,1)= c0*c2-s0*s1*s2;
	matrix(1,2)=-c0*s2-s0*s1*c2;
	matrix(2,0)= s1;
	matrix(2,1)= c1*s2;
	matrix(2,2)= c1*c2;

	mx=(1.0+scale)*matrix;
	invMx=transpose(matrix)/(1.0+scale);
#else
	matrix(0,0)=1;
	matrix(0,1)=-p;
	matrix(0,2)=-q;
	matrix(1,0)=p;
	matrix(1,1)=1;
	matrix(1,2)=-r;
	matrix(2,0)=q;
	matrix(2,1)=r;
	matrix(2,2)=1;

	mx=matrix + scale*ID(3);
	invMx=transpose(matrix) - scale*ID(3);
#endif



	std::cerr << "Matrix" << std::endl;
	for(auto row=0;row<3;row++) {
		for(auto column=0;column<3;column++) std::cerr << mx(row,column) << " ";
		std::cerr<< std::endl;
	}
	std::cerr << "Inverse" << std::endl;
		for(auto row=0;row<3;row++) {
			for(auto column=0;column<3;column++) std::cerr << invMx(row,column) << " ";
			std::cerr<< std::endl;
		}
}

Vector Helmert::transform(Vector x) const {
	auto m=prod(mx,x);
	auto out=m+offset;
	std::cerr << "Forward Product is " << m << " offset is " << offset << " result is " << out << std::endl;
	return out;
}

Vector Helmert::inverseTransform(Vector x) const {
	auto m=prod(invMx,x);
	auto o=-prod(invMx,offset);
	auto out=m+offset;
	std::cerr << "Inverse Product is " << m << " offset is " << o << " result is " << out << std::endl;
	return out;
}

bool Helmert::eq(const Helmert &o) const {
	return scale==o.scale && offset==o.offset && angles==o.angles;
}





} /* namespace mapping */


