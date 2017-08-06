/*
 * LatitudeLongitude.cpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#include "LatitudeLongitude.hpp"
#include "Cartesian.hpp"
#include "Parser.hpp"
#include <stdexcept>
#include <iomanip>



namespace coordinates {

using Axis = Cartesian::Axis;

LatitudeLongitude::LatitudeLongitude(const std::string &str,Tag tag) : datum(mapping::Datum::get(tag)), dTag(tag) {
	Parser p(str);
	if(p.parsedAs()==Parser::Kind::LatLong) {
		auto coordinates=p();
		latitude=coordinates.first;
		longitude=coordinates.second;
	}
	else throw std::runtime_error("Invalid string representation for latitude / longitude type");
}

LatitudeLongitude::LatitudeLongitude(const mapping::Vector &v,Tag tag) : datum(mapping::Datum::get(tag)), dTag(tag) {
	mapping::Ellipsoid e=ellipsoid();

	auto p=hypot(v(0),v(1));
	auto t=(1.0+(e.eccentricity2()*e.minorAxis()/boost::numeric::ublas::inner_prod(v,v)))*e.minorAxis()*v(2)/(e.majorAxis()*p);
	auto s=t/sqrt(1.0+t*t);
	auto c=s/t;

	double phi = std::isnan(c) ? 0 : atan2(v(2)+e.eccentricity2()*e.minorAxis()*pow(s,3),p-e.eccentricity1()*e.majorAxis()*pow(c,3));
	double lambda = atan2(v(1),v(0));

	latitude=degrees(phi);
	longitude=degrees(lambda);
}

LatitudeLongitude  LatitudeLongitude::transform( Tag newTag) const {
	auto newDatum=mapping::Datum::get(newTag);
	if(datum==newDatum) return *this;
	else {
		Cartesian c(*this);
		auto c2=newDatum(datum.invert(c));
		return LatitudeLongitude(c2,newTag);
	}
}


} /* namespace coordinates */

std::ostream & operator<<(std::ostream &o,const coordinates::LatitudeLongitude &ll) {
	char ns=(ll.latitude>=0.0) ? 'N' : 'S';
	char ew=(ll.longitude>=0.0) ? 'E' : 'W';

	o << std::fixed << std::setprecision(5) << fabs(ll.latitude) << ns << "," << fabs(ll.longitude) << ew;
	return o;
}

