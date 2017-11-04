/*
 * Generator.cpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#include <Generator.hpp>
#include <sstream>
#include <iostream>
#include <vector>

namespace test {

unsigned Generator::seed() noexcept {
	return std::chrono::system_clock::now().time_since_epoch().count();
}

double Generator::random(const double lo,const double hi) noexcept {
		return uniform(source)*(hi-lo)+lo;
	}

coordinates::LatitudeLongitude Generator::latLong(const Tag & tag) noexcept {
	auto lat=random(50.0,59.0);
	auto lon=random(-5.0,2.0);
	return coordinates::LatitudeLongitude(lat,lon,tag);
}

coordinates::OSGrid Generator::grid(const Tag & tag) noexcept {
	auto ll=latLong(tag);
	return coordinates::OSGrid(ll);
}

util::Vector Generator::vector() noexcept {
	std::vector<double> v(n,0.0);
	for(auto i=0;i<n;i++) v[i]=random(-100,100);
	return util::Vector(v);
}

void Generator::reset() {
	//uniform.reset();
}

double gridDiff(const coordinates::OSGrid &g1,const coordinates::OSGrid &g2) {
	return std::max(abs(g1.E()-g2.E()),abs(g1.N()-g2.N()));

}
double logGridDiff(const coordinates::OSGrid &g1,const coordinates::OSGrid &g2){
	auto e=gridDiff(g1,g2);
	return (e==0) ? 1000.0 : 6.0-log10(e);
}

double latLongDiff(const coordinates::LatitudeLongitude &l1,const coordinates::LatitudeLongitude &l2) {
	double e=std::max(abs(l1.Longitude()-l2.Longitude()),abs(l1.Latitude()-l2.Latitude()));
	return (e==0) ? 1000.0 : 3.0-log10(e);
}

std::string gridString(const coordinates::OSGrid &g) {
	std::stringstream s;
	s << g;
	return s.str();
}



} /* namespace test */
