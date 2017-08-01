/*
 * LatitudeLongitude.hpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef LATITUDELONGITUDE_HPP_
#define LATITUDELONGITUDE_HPP_

#include "Ellipsoid.hpp"
#include "Datum.hpp"

namespace mapping {

class Datum;

namespace coordinates {

class LatitudeLongitude {
private:
	Datum datum;
	double latitude;
	double longitude;
public:
	LatitudeLongitude();
	virtual ~LatitudeLongitude() = default;
	
	double Latitude() { return latitude; }
	double Longitude(){ return longitude; }
	
	double phi() const { return latitude*PI/180.0; }
	double lambda() const { return longitude*PI/180.0; }
	
	Ellipsoid ellipsoid() const { return datum.ellipsoid();  }
};

} /* namespace coordinates */
} /* namespace mapping */

#endif /* LATITUDELONGITUDE_HPP_ */
