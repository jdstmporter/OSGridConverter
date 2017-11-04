/*
 * Matrix.hpp
 *
 *  Created on: 2 Nov 2017
 *      Author: julianporter
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_



#include <vector>
#include <initializer_list>
#include "Vector.hpp"

namespace util {

class Matrix {
public:
	using  vec_t = std::vector<double>;
	using  iterator = vec_t::iterator;
	using  const_iterator = vec_t::const_iterator;
private:
	std::vector<double> v;
	int rows;
	int columns;

public:
	Matrix (const int r,const int c) : v(r*c,0.0), rows(r), columns(c) {};
	Matrix (const int r,const int c, const std::vector<double> &vec) : v(vec), rows(r), columns(c) {};
	Matrix (const int r,const int c, std::vector<double> &&vec) : v(vec), rows(r), columns(c) {};
	Matrix (const int r,const double diag=1.0);

	int nRows() const { return rows; }
	int nColumns() const { return columns; }
	int size() const { return v.size(); }
	iterator begin() { return v.begin(); }
	iterator end() { return v.end(); }
	const_iterator cbegin() const { return v.cbegin(); }
	const_iterator cend() const { return v.cend(); }

	double &operator()(const int r,const int j);
};

bool equalSize(const Matrix &l,const Matrix &r);

bool operator==(const Matrix &l,const Matrix &r);
bool operator!=(const Matrix &l,const Matrix &r);

Matrix operator+(const Matrix &l,const Matrix &r);
Matrix operator-(const Matrix &l,const Matrix &r);
Matrix operator*(const Matrix &m,const double s);
Matrix operator*(const double s,const Matrix &m);
Matrix outer_prod(const Vector &l,const Vector &r);
Vector prod(const Matrix &m,const Vector &v);


} /* namespace util */

#endif /* MATRIX_HPP_ */
