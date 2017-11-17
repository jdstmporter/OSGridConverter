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
	friend void swap(Matrix &v1,Matrix &v2);
public:
	using  mx_t = std::vector<double>;
	using  iterator = mx_t::iterator;
	using  const_iterator = mx_t::const_iterator;
private:
	int r;
	int c;
	std::vector<double> rows;



public:
/** \brief Constructs zero matrix of size \p r_ x \p c_
 	\param r_ the number of rows
 	\param c_ the number of columns */
	Matrix(const int r_,const int c_) : r(r_), c(c_) , rows(r*c,0) {};
/** \brief Constructs matrix from values in a std::initializer_list
 \param r_ the number of rows
 \param c_ the number of columns
 \param values the list of values */
	Matrix(const int r_,const int c_, std::initializer_list<double> values) : r(r_), c(c_) , rows(values) {};
/** \brief copies values from std::vector into a new Matrix
 \param r_ the number of rows
 \param c_ the number of columns
 \param v values to copy into the new Matrix */
	Matrix(const int r_,const int c_, const std::vector<double> & v) : r(r_), c(c_), rows(v) {};
/** \brief moves values from std::vector into a new Matrix
 \param r_ the number of rows
 \param c_ the number of columns
 \param v values to move into the new Matrix */
	Matrix(const int r_,const int c_, std::vector<double> && v) : r(r_), c(c_), rows(v) {};
/** Construct diagonal r_ x r_ matrix 
\param r_  number of rows / columns
\param diag diagonal value (defaults to 1.0 */
	Matrix(const int r_,const double diag=1.0);

	Matrix (const Matrix &o) : r(o.r), c(o.c), rows(o.rows)  {};
	Matrix (Matrix &&o) : r(o.r), c(o.c), rows(std::move(o.rows))  {};
	virtual ~Matrix() = default;

	Matrix & operator=(const Matrix &o);
	Matrix & operator=(Matrix &&o);

	static Matrix ID(const int n=3) { return Matrix(n); }
	static Matrix Zero(const int r,const int c) { return Matrix(r,c); }

	const_iterator cbegin() const { return rows.cbegin(); }
	const_iterator cend() const  { return rows.cend(); }
	const_iterator begin()  { return rows.begin(); }
	const_iterator end()   { return rows.end(); }

	/** Number of rows in matrix */
	int nRows() const { return r; }
	/** Number of columns in matrix */
	int nColumns() const { return c; }

/** \brief Subscript (\b read-write)
 * \param r_ index to row of item returned (counting 0 up)
 * \param c_ index to column of item returned (counting 0 up)
 * \return reference to value at index \p (r_,c_) */
	double &operator()(const int r_,const int c_);
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

void swap(Matrix &v1,Matrix &v2);

} /* namespace util */

#endif /* MATRIX_HPP_ */
