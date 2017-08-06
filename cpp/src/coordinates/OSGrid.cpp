/*
 * OSGrid.cpp
 *
 *  Created on: 6 Aug 2017
 *      Author: julianporter
 */

#include "OSGrid.hpp"
#include "Parser.hpp"
#include "LatitudeLongitude.hpp"
#include "OSGB36.hpp"
#include <stdexcept>

namespace coordinates {


OSGrid::OSGrid(const std::string & slug) {
	Parser p(slug);
	if(p.parsedAs()==Parser::Kind::Grid) {
			auto coordinates=p();
			eastings=long(coordinates.first);
			northings=long(coordinates.second);
		}
		else throw std::runtime_error("Invalid string representation for OS Grid type");
}

OSGrid::OSGrid(const LatitudeLongitude &latlong) {
	LatitudeLongitude ll = latlong.is(Tag::OSGB36) ? latlong : latlong.transform();
	auto g=mapping::OSGB36({ll.phi(),ll.lambda()});
	auto ne=g.fromLatLong();
	northings=long(std::get<0>(ne));
	eastings=long(std::get<1>(ne));
}


} /* namespace coordinates */

bool operator==(const coordinates::OSGrid &l,const coordinates::OSGrid &r) {
	return (l.eastings==r.eastings && (l.northings==r.northings));
}

bool operator!=(const coordinates::OSGrid &l,const coordinates::OSGrid &r) {
	return (l.eastings!=r.eastings || (l.northings!=r.northings));
}

std::ostream & operator<<(std::ostream &o,const coordinates::OSGrid &grid) {
	o << coordinates::Parser::toString(grid);
	return o;
}
