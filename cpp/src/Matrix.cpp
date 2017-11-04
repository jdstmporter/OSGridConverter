/*
 * Matrix.cpp
 *
 *  Created on: 2 Nov 2017
 *      Author: julianporter
 */

#include "Matrix.hpp"
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <stdexcept>

namespace util {

Matrix::Matrix(const int r,const double diag): v(r*r,0.0), rows(r), columns(r) {
	for(auto i=0;i<r;i++) v[(r+1)*i]=diag;
}

double & Matrix::operator()(const int r,const int c) {
	return v[r*rows+c];
}

bool equalSize(const Matrix &l,const Matrix &r) {
	return l.nRows()==r.nRows() && l.nColumns()==r.nColumns();
}

bool operator==(const Matrix &l,const Matrix &r) {
	return equalSize(l,r) && std::equal(l.cbegin(),l.cend(),r.cbegin());
}

bool operator!=(const Matrix &l,const Matrix &r) {
	return !(l==r);
}

Matrix operator+(const Matrix &l,const Matrix &r) {
	if(!equalSize(l,r)) throw std::runtime_error("Matrix addition must be between matrices of equal size");
	std::vector<double> v(l.size(),0.0);
	std::transform(l.cbegin(),l.cend(),r.cbegin(),v.begin(),std::plus<double>());
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator-(const Matrix &l,const Matrix &r) {
	if(!equalSize(l,r)) throw std::runtime_error("Matrix subtraction must be between matrices of equal size");
	std::vector<double> v(l.size(),0.0);
	std::transform(l.cbegin(),l.cend(),r.cbegin(),v.begin(),std::minus<double>());
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator-(const Matrix &l) {
	std::vector<double> v(l.size(),0.0);
		std::transform(l.cbegin(),l.cend(),v.begin(),std::negate<double>());
		return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator*(const Matrix &l,const double s) {
	std::vector<double> v(l.size(),0.0);
	std::transform(l.cbegin(),l.cend(),v.begin(),[s](double x){ return x*s; });
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator*(const double s,const Matrix &l) {
	std::vector<double> v(l.size(),0.0);
	std::transform(l.cbegin(),l.cend(),v.begin(),[s](double x){ return x*s; });
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}

Vector prod(const Matrix &m,const Vector &v) {
	if(m.nColumns()!=v.size()) throw std::runtime_error("Vector matrix multiplication must have compatible sizes");
	std::vector<double> vv(v.size(),0.0);
	for(auto i=0;i<v.size();i++) {
		vv[i]=std::inner_product(v.cbegin(),v.cend(),m.cbegin()+m.nColumns()*i,0.0);
	}
	return Vector(std::move(vv));
}

Matrix outer_prod(const Vector &l,const Vector &r) {
	std::vector<double> v(l.size()*r.size(),0.0);
	auto it=v.begin();
	for(auto i=0;i<l.size();i++) {
		auto lValue=l(i);
		for(auto j=0;j<r.size();j++) {
			*(it++)=lValue*r(j);
		}
	}
	return Matrix(l.size(),r.size(),std::move(v));
}

} /* namespace util */
