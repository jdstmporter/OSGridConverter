/*
 * LatitudeLongitude.hpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef LATITUDELONGITUDE_HPP_
#define LATITUDELONGITUDE_HPP_

#include "mapping/Ellipsoid.hpp"
#include "mapping/Datum.hpp"
#include <string>





namespace coordinates {

class Cartesian;

class LatitudeLongitude {
private:
	mapping::Datum datum;
	double latitude;
	double longitude;
public:
	LatitudeLongitude(const Cartesian &cartesian,mapping::Datum::Name tag = mapping::Datum::Name::WGS84);
	LatitudeLongitude(const std::string &str,mapping::Datum::Name tag = mapping::Datum::Name::WGS84);
	LatitudeLongitude(const double lat,const double lon,mapping::Datum::Name tag = mapping::Datum::Name::WGS84);
	virtual ~LatitudeLongitude() = default;
	
	double Latitude() { return latitude; }
	double Longitude(){ return longitude; }
	
	double phi() const { return radians(latitude); }
	double lambda() const { return radians(longitude); }
	
	mapping::Ellipsoid ellipsoid() const { return datum.ellipsoid();  }
};

} /* namespace coordinates */


#endif /* LATITUDELONGITUDE_HPP_ */
