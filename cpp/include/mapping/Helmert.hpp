/*
 * Helmert.hpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#ifndef HELMERT_HPP_
#define HELMERT_HPP_




#include <stdexcept>
#include "algebra.hpp"


namespace mapping {





class Helmert {


private:
	Matrix mx;
	Matrix invMx;
	Vector offset;
	Vector angles;
	double scale;

	double s(const int n) { return sin(angles(n)); };
	double c(const int n) { return cos(angles(n)); };

public:


	Helmert() : mx(ID(3)), invMx(ID(3)), offset(Zero(3)), angles(Zero(3)), scale(1.0) {};
	Helmert(const Vector &o,const Vector &a,const double s_);
	Helmert(const Helmert &o) = default;
	virtual ~Helmert() = default;

	Helmert & operator=(const Helmert &o) = default;

	Vector transform(Vector x) const;
	Vector inverseTransform(Vector x) const;

	bool eq(const Helmert &o) const;


};


} /* namespace mapping */




#endif /* HELMERT_HPP_ */
