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
#include <iostream>
#include <sstream>
#include <iomanip>

namespace coordinates {


OSGrid::OSGrid(const std::string & slug) {
	Parser p(slug);
	if(p.parse()==Parser::Kind::Grid) {
			auto coordinates=p();
			eastings=long(coordinates.E);
			northings=long(coordinates.N);
		}
		else throw std::runtime_error("Invalid string representation for OS Grid type");
}

OSGrid::OSGrid(const LatitudeLongitude &latlong) {
	auto ll=latlong;
	if(!ll.is(Tag::OSGB36)) {
		ll=ll.transform();
	}
	auto g=mapping::OSGB36(ll.phi(),ll.lambda());
	auto ne=g.fromLatLong();
	northings=long(std::get<1>(ne));
	eastings=long(std::get<0>(ne));
}

bool operator==(const OSGrid &l,const OSGrid &r) {
	return (l.eastings==r.eastings && (l.northings==r.northings));
}

bool operator!=(const OSGrid &l,const OSGrid &r) {
	return (l.eastings!=r.eastings || (l.northings!=r.northings));
}

} /* namespace coordinates */

std::string padIt(const long value,const unsigned n) {
	std::stringstream s;
	s << std::string(n,'0') << value;
	auto str=s.str();
	return str.substr(str.size()-n,n);
}



std::ostream & operator<<(std::ostream &o,const coordinates::OSGrid &g) {
	try {

		auto E=g.E();
		auto N=g.N();
		long e100km=E/100000;
		long n100km=N/100000;
		if(e100km<0 || e100km>6 || n100km<0 || n100km>12) {
			std::cerr << "Out of range" << std::endl;
			throw std::runtime_error("OOR");
		}
		auto nf=19-n100km;
		auto ef=10+e100km;

		long l1=nf-(nf%5)+(ef/5);
		long l2=(5*nf)%25 + (ef%5);
		o << coordinates::Parser::gridAlphabet[l1] << coordinates::Parser::gridAlphabet[l2];
		auto e = E%100000;
		auto n = N%100000;
		o << " " << padIt(e,5) << " " << padIt(n,5);
	}
	catch(...) {
		o << "OOR";
	}
	return o;
}


