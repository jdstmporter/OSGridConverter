/*
 * OSGrid.cpp
 *
 *  Created on: 6 Aug 2017
 *      Author: julianporter
 */

#include "OSGrid.hpp"
#include "Parser.hpp"
#include "LatitudeLongitude.hpp"
#include "../mapping/OSGB36.hpp"
#include <stdexcept>
#include <iomanip>

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

bool operator==(const OSGrid &l,const OSGrid &r) {
	return (l.eastings==r.eastings && (l.northings==r.northings));
}

bool operator!=(const OSGrid &l,const OSGrid &r) {
	return (l.eastings!=r.eastings || (l.northings!=r.northings));
}

} /* namespace coordinates */

std::ostream & operator<<(std::ostream &o,const coordinates::OSGrid &g) {
	try {
		auto c=g.coordinates();
		auto E=std::get<0>(c);
		auto N=std::get<1>(c);
		long e100km=E/10000;
		long n100km=N/10000;
		if(e100km<0 || e100km>6 || n100km<0 || n100km>12) throw std::runtime_error("OOR");
		auto nf=19-n100km;
		auto ef=10+e100km;

		long l1=nf-(nf%5)+(ef/5);
		long l2=(5*nf)%25 + (ef%5);
		o << coordinates::Parser::gridAlphabet[l1] << coordinates::Parser::gridAlphabet[l2];
		auto e = E%100000;
		auto n = N%100000;
		o << " " << std::setw(5) << std::setfill('0')  << std::right << e << " " << n;
	}
	catch(...) {
		o << "OOR";
	}
	return o;
}


