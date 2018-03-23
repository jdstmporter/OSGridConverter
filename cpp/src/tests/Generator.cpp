/*
 * Generator.cpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#include <tests/Generator.hpp>
#include <sstream>
#include <iostream>
#include <cmath>

namespace test {

unsigned Generator::seed() {
	return std::chrono::system_clock::now().time_since_epoch().count();
}

double Generator::random(const double lo,const double hi) {
		return uniform(source)*(hi-lo)+lo;
	}

coordinates::LatitudeLongitude Generator::latLong(const mapping::Datum::Name & tag) {
	auto lat=random(50.0,59.0);
	auto lon=random(-5.0,2.0);
	return coordinates::LatitudeLongitude(lat,lon,tag);
}

coordinates::OSGrid Generator::grid(const mapping::Datum::Name & tag) {
	auto ll=latLong(tag);
	return coordinates::OSGrid(ll);
}

void Generator::reset() {
	//uniform.reset();
}

inline double safeLog10(long x) {
	return (x==0) ? -10.0 : log10((double)x);
}

double gridDiff(const coordinates::OSGrid &g1,const coordinates::OSGrid &g2) {
	auto dE=abs(g1.E()-g2.E());
	auto dN=abs(g1.N()-g2.N());
	auto d=hypot((double)dE,(double)dN);
	return (d==0) ? 1000.0 : 6-log10(d);
}

static const double EarthRadius = 6.371e6;

double latLongDiff(const coordinates::LatitudeLongitude &l1,const coordinates::LatitudeLongitude &l2) {
	auto dE=fabs(l1.phi()-l2.phi());
	auto dN=fabs(l1.lambda()-l2.lambda());
	auto d=hypot(dE,dN)*EarthRadius;
	return (d==0) ? 1000.0 : 6-log10(d);
}

std::string gridString(const coordinates::OSGrid &g) {
	std::stringstream s;
	s << g;
	return s.str();
}



} /* namespace test */
