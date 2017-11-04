/*
 * Cartesian.hpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef CARTESIAN_HPP_
#define CARTESIAN_HPP_

#include "algebra.hpp"
#include "Helmert.hpp"


namespace coordinates {

class LatitudeLongitude;


class Cartesian {
public:
	enum class Axis : unsigned {
		X = 0,
		Y = 1,
		Z = 2
	};
private:
	mapping::Vector vector;
public:
	Cartesian(const mapping::Vector &v = mapping::Zero(3)) : vector(v) {};
	Cartesian(const double x,const double y,const double z);
	Cartesian(const LatitudeLongitude &l);
	Cartesian(const Cartesian &o) : vector(o.vector) {};
	virtual ~Cartesian() = default;

	double P() const;
	double RSquared() const;
	double operator[](const Axis &axis) const;
	Cartesian transform(const mapping::Helmert &helmert);

	mapping::Vector vec() const { return vector; }
};


} /* namespace coordinates */


#endif /* CARTESIAN_HPP_ */
