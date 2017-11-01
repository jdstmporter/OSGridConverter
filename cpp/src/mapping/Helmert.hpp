/*
 * Helmert.hpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#ifndef HELMERT_HPP_
#define HELMERT_HPP_


#include <valarray>
#include "algebra.hpp"


namespace mapping {

bool operator==(const Vector &l,const Vector &r);
bool operator!=(const Vector &l,const Vector &r);

bool operator==(const Matrix &l,const Matrix &r);
bool operator!=(const Matrix &l,const Matrix &r);

class Helmert {
	friend bool operator==(const Helmert &l,const Helmert &r);
	friend bool operator!=(const Helmert &l,const Helmert &r);
private:
	Vector t;
	Matrix mx;
	Matrix inv;

	double determinant();
	static Matrix matrix(const Vector &r, const double s);
	static Matrix inverseMatrix(const Vector &r, const double s);
	static std::valarray<unsigned> indices(const unsigned index);

public:
	Helmert() : t(Zero(3)), mx(ID(3)), inv(ID(3)) {};
	Helmert(const Vector & T, const Matrix & MX, const Matrix &INV) : t(T),  mx(MX), inv(INV) {};
	Helmert(const Vector & T,const Vector & R, const double S);
	Helmert(const Helmert &o) : t(o.t), mx(o.mx), inv(o.inv) {};
	virtual ~Helmert() = default;

	Helmert & operator=(const Helmert &o);
	Helmert inverse() const;
	Vector operator()(Vector x) const;
};

bool operator==(const Helmert &l,const Helmert &r);
bool operator!=(const Helmert &l,const Helmert &r);

} /* namespace mapping */



#endif /* HELMERT_HPP_ */
