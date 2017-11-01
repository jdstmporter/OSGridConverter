/*
 * LatitudeLongitude.hpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef LATITUDELONGITUDE_HPP_
#define LATITUDELONGITUDE_HPP_

#include <mapping/Ellipsoid.hpp>
#include <mapping/Datum.hpp>
#include <string>
#include <iostream>





namespace coordinates {

class Cartesian;

using Tag = mapping::Datum::Name;

class OSGrid;

class LatitudeLongitude {
	friend std::ostream & operator<<(std::ostream &o,const LatitudeLongitude &ll);
private:

	double latitude;
	double longitude;
	mapping::Datum datum;
	Tag dTag;
public:
	LatitudeLongitude(const mapping::Vector &v,Tag tag = Tag::WGS84);
	LatitudeLongitude(const Cartesian &cartesian,Tag tag = Tag::WGS84);
	LatitudeLongitude(const std::string &str,Tag tag = Tag::WGS84);
	LatitudeLongitude(const OSGrid &grid,Tag tag = Tag::WGS84);
	LatitudeLongitude(const double lat,const double lon,Tag tag = Tag::WGS84) : latitude(lat), longitude(lon), datum(mapping::Datum::get(tag)), dTag(tag)  {};
	LatitudeLongitude(const std::pair<double,double> & p,Tag tag = Tag::WGS84) : LatitudeLongitude(p.first, p.second,tag) {};
	virtual ~LatitudeLongitude() = default;
	
	double Latitude() const { return latitude; }
	double Longitude() const { return longitude; }
	
	double phi() const { return radians(latitude); }
	double lambda() const { return radians(longitude); }
	
	mapping::Ellipsoid ellipsoid() const { return datum.ellipsoid();  }
	LatitudeLongitude transform(Tag newTag=Tag::OSGB36) const;

	bool is(const Tag &tag) const { return tag==dTag; }

};

std::ostream & operator<<(std::ostream &o,const coordinates::LatitudeLongitude &ll);

} /* namespace coordinates */




#endif /* LATITUDELONGITUDE_HPP_ */
