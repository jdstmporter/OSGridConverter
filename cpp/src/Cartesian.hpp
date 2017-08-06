/*
 * Cartesian.hpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef CARTESIAN_HPP_
#define CARTESIAN_HPP_

#include "mapping/algebra.hpp"


namespace coordinates {

class LatitudeLongitude;

class Cartesian {
private:
	mapping::Vector vector;
public:
	Cartesian(const mapping::Vector &v = mapping::Zero(3)) : vector(v) {};
	Cartesian(const double x,const double y,const double z);
	Cartesian(const LatitudeLongitude &l);
	Cartesian(const Cartesian &o) : vector(o.vector) {};
	virtual ~Cartesian() = default;
};

} /* namespace coordinates */


#endif /* CARTESIAN_HPP_ */
