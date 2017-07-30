/*
 * Ellipsoid.cpp
 *
 *  Created on: 29 Jul 2017
 *      Author: julianporter
 */

#include "Ellipsoid.hpp"
#include <cmath>

using namespace boost::numeric::ublas;

namespace mapping {

Ellipsoid::Ellipsoid(double a,double b) noexcept : 
	A(a), B(b), f((a-b)/b), e1(2*f-f*f), e2(e1/(1.0-e1)),
	n((a-b)/(a+b)), M(4) {

	M(0)=1.0+n+5.0*A/4.0;
	M(1)=3.0*(n+n*n)+ 21.0*n*n*n/8.0;
	M(2)=15.0*A/8.0;
	M(3)=35.0*n*n*n/24.0;
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

double Ellipsoid::meridional(double phi,double phi0) noexcept {
	auto plus  = phi+phi0;
	auto minus = phi-phi0;	
	vector<double> angles(4);
	angles(0)=plus;
	angles(1)=-sin(minus)*cos(plus);
	angles(2)=sin(2*minus)*cos(2*plus);
	angles(3)=-sin(3*minus)*cos(3*plus);
	return inner_prod(M,angles);
}

std::shared_ptr<Model> Model::the=std::shared_ptr<Model>();

Model::Model() : ellipsoids() {
	ellipsoids[Name::WGS84]        = Ellipsoid(6378137    ,6356752.31425);
	ellipsoids[Name::GRS80]        = Ellipsoid(6378137    ,6356752.31414);
	ellipsoids[Name::Airy1830]     = Ellipsoid(6377563.396,6356256.909);
	ellipsoids[Name::AiryModified] = Ellipsoid(6377340.189,6356034.448);
	ellipsoids[Name::Intl1924]     = Ellipsoid(6378388    ,6356911.946);
	ellipsoids[Name::Bessel1841]   = Ellipsoid(6377397.155,6356078.963);
	ellipsoids[Name::Clarke1880]   = Ellipsoid(6378249.2  ,6356515);
}

Ellipsoid Model::ellipsoid(const Name &key) {
	if(!the) the=std::make_shared<Model>();
	return the->get(key);
}



}



