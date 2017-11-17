/*
 * Cartesian.hpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef CARTESIAN_HPP_
#define CARTESIAN_HPP_

#include "Vector.hpp"
#include "Helmert.hpp"
#include "Ellipsoid.hpp"



namespace coordinates {

class Cartesian {
public:
/** Labels for axes */
	enum class Axis : unsigned {
		X = 0,	/*!< X-axis */
		Y = 1,  /*!< Y-axis */
		Z = 2   /*!< Z-axis */
	};
private:
	util::Vector vector;
public:
/** \brief Construct instance from vector
	\param v util::Vector of coordinates (defaults to zero vector) */
	Cartesian(const util::Vector &v = util::Vector(3)) : vector(v) {};
	Cartesian(const double x,const double y,const double z);
	/** Copy constructor */
	Cartesian(const Cartesian &o) : vector(o.vector) {};
	virtual ~Cartesian() = default;
	
	double P() const;
	double RSquared() const;
	double operator[](const Axis &axis) const;

	Cartesian transform(const mapping::Helmert &helmert);
	util::Vector vec() const { return vector; }
};


} /* namespace coordinates */


#endif /* CARTESIAN_HPP_ */
