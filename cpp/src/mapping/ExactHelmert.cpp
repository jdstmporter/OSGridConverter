/*
 * ExactHelmert.cpp
 *
 *  Created on: 1 Mar 2018
 *      Author: julianporter
 */

#include "ExactHelmert.hpp"

namespace mapping {
namespace helmert {

std::valarray<unsigned> indices(const unsigned index) {
	auto i1=(index+1)%3;
	auto i2=(index+2)%3;
	return std::move(std::valarray<unsigned> {i1, i2});
}

enum Axis : unsigned {
	X = 0, Y = 1, Z = 2
};

struct Trigonometry {
	double c;
	double s;

	Trigonometry() : c(1), s(0) {};
	Trigonometry(const double angle) : c(cos(angle)), s(sin(angle)) {};
	Trigonometry(const Trigonometry &o) = default;
};

Matrix rotate(const unsigned axis,const double angle) {
	Trigonometry t(angle);
	auto jk=indices(axis);
	Matrix m=ID(3);
	m(jk[0],jk[0]) = t.c;
	m(jk[1],jk[1]) = t.c;
	m(jk[1],jk[0]) =-t.s;
	m(jk[0],jk[1]) = t.s;
	return std::move(m);
}

Matrix euler(const Vector &angles) {
	auto m0=rotate(angles(0),0);
	auto m1=rotate(angles(1),1);
	auto m2=rotate(angles(2),2);
	return std::move(m0*m1*m2);
}

Matrix ExactHelmert::matrix(const Vector &a,const double sc) const {
	Matrix m=ZMatrix(3,3);
	std::valarray<double> c(3);
	std::valarray<double> s(3);
	std::transform(std::begin(a),std::end(a),std::begin(c),[](double x) { return cos(x); });
	std::transform(std::begin(a),std::end(a),std::begin(s),[](double x) { return sin(x); });
	m(0,0)=c[1]*c[2];
	m(1,0)=-(m(0,1)=c[0]*s[2]+c[2]*s[0]*s[1]);
	m(2,0)=-(m(0,2)=s[0]*s[2]-c[0]*c[2]*s[1]);
	m(1,1)=c[0]*c[2]-s[0]*s[1]*s[2];
	m(2,1)=-(m(1,2)=c[2]*s[0]+c[0]*s[1]*s[2]);
	m(2,2)=c[0]*c[1];
	m*=sc;
	return m;
}


Vector ExactHelmert::invertedAngles() const {
	Vector b(3);
	b(0)=-angles(2);
	b(1)=-angles(1);
	b(2)=-angles(0);
	return std::move(b);
}





} /* namespace helmert */
} /* namespace mapping */
