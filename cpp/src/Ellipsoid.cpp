/*
 * Ellipsoid.cpp
 *
 *  Created on: 29 Jul 2017
 *      Author: julianporter
 */

#include "Ellipsoid.hpp"
#include <cmath>
#include <numeric>


namespace mapping {

Ellipsoid::Ellipsoid(double a,double b, double f_) noexcept :
	A(a), B(b), f(f_), e1(2*f-f*f), e2(e1/(1.0-e1)),n((a-b)/(a+b)), M(4) {

	auto nn=n*n;
	auto nnn=n*nn;
	auto aa=nn+nnn;
	M[0]=1.0+n+5.0*aa/4.0;
	M[1]=3.0*(n+nn)+ 21.0*nnn/8.0;
	M[2]=15.0*aa/8.0;
	M[3]=35.0*nnn/24.0;
}

Ellipsoid & Ellipsoid::operator==(const Ellipsoid &other) noexcept {
	A=other.A;
	B=other.B;
	e1=other.e1;
	e2=other.e2;
	n=other.n;
	M=other.M;
	return *this;
}

double Ellipsoid::meridional(const double phi,const double phi0) noexcept {
	auto plus  = phi+phi0;
	auto minus = phi-phi0;
	std::vector<double> angles {
		minus,
		-sin(minus)*cos(plus),
		 sin(2*minus)*cos(2*plus),
		-sin(3*minus)*cos(3*plus)
	};
	return std::inner_product(M.begin(),M.end(),angles.begin(),0.0);
}

Ellipsoid::Parameters Ellipsoid::ellipsoids = Ellipsoid::Parameters();

void Ellipsoid::initialise() {
	ellipsoids[Name::WGS84]        = Axes(6378137.0  ,6356752.31425, 1/298.257223563);
	ellipsoids[Name::GRS80]        = Axes(6378137.0  ,6356752.31414, 1/298.257222101);
	ellipsoids[Name::Airy1830]     = Axes(6377563.396,6356256.909,   1/299.3249646);
	ellipsoids[Name::AiryModified] = Axes(6377340.189,6356034.448,   1/299.3249646);
	ellipsoids[Name::Intl1924]     = Axes(6378388.0  ,6356911.946,   1.0/297.0);
	ellipsoids[Name::Bessel1841]   = Axes(6377397.155,6356078.963,   1/299.152815351);
	ellipsoids[Name::Clarke1880]   = Axes(6378249.2  ,6356515.0,     1/293.465);
}

Ellipsoid Ellipsoid::get(const Name &key) {
	if(ellipsoids.empty()) Ellipsoid::initialise();
	return Ellipsoid(ellipsoids[key]);
}

bool operator==(const mapping::Ellipsoid &l,const mapping::Ellipsoid &r) {
	return (l.A==r.A) && (l.B==r.B);
}

bool operator!=(const mapping::Ellipsoid &l,const mapping::Ellipsoid &r) {
	return (l.A!=r.A) || (l.B!=r.B);
}



}





