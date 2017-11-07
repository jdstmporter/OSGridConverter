/*
 * Vector.cpp
 *
 *  Created on: 2 Nov 2017
 *      Author: julianporter
 */

#include "Vector.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>

namespace util {

Vector & Vector::operator =(const Vector & o)  {
	v=o.v;
	return *this;
}

Vector & Vector::operator =(Vector && o) {
	std::swap(v,o.v);
	return *this;
}

double Vector::norm() const {
	auto s=std::inner_product(v.cbegin(),v.cend(),v.cbegin(),0.0);
	return sqrt(s);
}

double Vector::normSquared() const {
	double s=std::inner_product(v.cbegin(),v.cend(),v.cbegin(),0.0);
	return s;
}

Vector operator+(const Vector &l,const Vector &r) {
	std::vector<double> v(std::min(l.size(),r.size()));
	std::transform(l.cbegin(),l.cend(),r.cbegin(),v.begin(),std::plus<double>());
	return Vector(std::move(v));
}
Vector operator-(const Vector &l,const Vector &r) {
	std::vector<double> v(std::min(l.size(),r.size()));
	std::transform(l.cbegin(),l.cend(),r.cbegin(),v.begin(),std::minus<double>());
	return Vector(std::move(v));
}
Vector operator-(const Vector &l) {
	std::vector<double> v(l.size());
	std::transform(l.cbegin(),l.cend(),v.begin(),std::negate<double>());
	return Vector(std::move(v));
}

Vector operator*(const Vector &l,const double s) {
	std::vector<double> v(l.size());
	std::transform(l.cbegin(),l.cend(),v.begin(),[s](double x){ return x*s; });
	return Vector(std::move(v));
}
Vector operator*(const double s,const Vector &l) {
	std::vector<double> v(l.size());
	std::transform(l.cbegin(),l.cend(),v.begin(),[s](double x){ return x*s; });
	return Vector(std::move(v));
}

double operator|(const Vector &l,const Vector &r) {
	return std::inner_product(l.cbegin(),l.cend(),r.cbegin(),0.0);
}

bool operator==(const Vector &l,const Vector &r) {
	return std::equal(l.cbegin(),l.cend(),r.cbegin());
}

bool operator!=(const Vector &l,const Vector &r) {
	return !std::equal(l.cbegin(),l.cend(),r.cbegin());
}

void swap(Vector &v1,Vector &v2) {
	v1.v.swap(v2.v);
}


} /* namespace util */
