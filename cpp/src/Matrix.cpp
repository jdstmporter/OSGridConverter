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
#include <stdexcept>

namespace util {



Matrix::Matrix(const int r_,const double diag): r(r_), c(r_),rows(r*c,0.0) {
	for(auto i=0;i<r;i++) rows[(i+1)*r]=diag;
}

Matrix & Matrix::operator =(const Matrix & o) {
	rows=o.rows;
	r=o.r;
	c=o.c;
	return *this;
}

Matrix & Matrix::operator =(Matrix && o) {
	std::swap(rows,o.rows);
	std::swap(r,o.r);
	std::swap(c,o.c);
	return *this;
}

double & Matrix::operator()(const int r_,const int c_) {
	return rows[r_*c + c_];
}


bool equalSize(const Matrix &l,const Matrix &r) {
	return l.nRows()==r.nRows() && l.nColumns()==r.nColumns();
}

Matrix operator+(const Matrix &l,const Matrix &r) {
	if(!equalSize(l,r)) throw std::runtime_error("Matrix addition must be between matrices of equal size");
	std::vector<double> v(l.nRows()*l.nColumns(),0);
	std::transform(l.cbegin(),l.cend(),r.cbegin(),v.begin(),std::plus<double>());
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator-(const Matrix &l,const Matrix &r) {
	if(!equalSize(l,r)) throw std::runtime_error("Matrix subtraction must be between matrices of equal size");
	std::vector<double> v(l.nRows()*l.nColumns(),0);
	std::transform(l.cbegin(),l.cend(),r.cbegin(),v.begin(),std::minus<double>());
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator-(const Matrix &l) {
	std::vector<double> v(l.nRows()*l.nColumns(),0);
	std::transform(l.cbegin(),l.cend(),v.begin(),std::negate<double>());
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator*(const Matrix &l,const double s) {
	std::vector<double> v(l.nRows()*l.nColumns(),0);
	std::transform(l.cbegin(),l.cend(),v.begin(),[s](double x){ return x*s; });
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}
Matrix operator*(const double s,const Matrix &l) {
	std::vector<double> v(l.nRows()*l.nColumns(),0);
	std::transform(l.cbegin(),l.cend(),v.begin(),[s](double x){ return x*s; });
	return Matrix(l.nRows(),l.nColumns(),std::move(v));
}

Vector prod(const Matrix &m,const Vector &v) {
	if(m.nColumns()!=v.size()) throw std::runtime_error("Vector matrix multiplication must have compatible sizes");
	std::vector<double> vv(m.nRows(),0.0);
	for(auto i=0;i<m.nRows();i++) {
		vv[i]=std::inner_product(v.cbegin(),v.cend(),m.cbegin()+i*m.nColumns(),0.0);
	}
	return Vector(std::move(vv));
}

Matrix outer_prod(const Vector &l,const Vector &r) {
	std::vector<double> v(l.size()*r.size(),0.0);
	for(auto i=0;i<l.size();i++) for(auto j=0;j<r.size();j++) v[i*r.size()+j]=l(i)*r(j);
	return Matrix(l.size(),r.size(),std::move(v));
}

void swap(Matrix &v1,Matrix &v2) {
	std::swap(v1.r,v2.r);
	std::swap(v1.c,v2.c);
	v1.rows.swap(v2.rows);
}

} /* namespace util */
