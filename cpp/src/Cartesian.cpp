/*
 * Cartesian.cpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#include "Cartesian.hpp"
#include "LatitudeLongitude.hpp"

#include <cmath>



namespace coordinates {

Cartesian::Cartesian(const double x,const double y,const double z) : vector({x,y,z}) {}


double Cartesian::P() const {
	double d = vector[0]*vector[0]+vector[1]*vector[1];
	return sqrt(d);
}

double Cartesian::RSquared() const {
	return vector.normSquared();
}

double Cartesian::operator[](const Cartesian::Axis &axis) const {
	return vector(static_cast<unsigned>(axis));
}

Cartesian Cartesian::transform(const mapping::Helmert &helmert) {
	auto out=helmert(vector);
	return std::move(Cartesian(out));
}




} /* namespace coordinates */

