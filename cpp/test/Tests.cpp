/*
 * Tests.cpp
 *
 *  Created on: 1 Nov 2017
 *      Author: julianporter
 */

#include <geoconv.hpp>
#include <Tests.hpp>
#include <iostream>

namespace test {

int GridToLatLong::action() {

	coordinates::OSGrid g=generator.grid(tag);
	auto s=gridString(g);
	if(s.size()>0) {
		coordinates::LatitudeLongitude ll(g,tag);
		coordinates::OSGrid gg(ll);
		auto error=logGridDiff(g,gg);
		push(error,3);
		if(verbose) {
			std::cout << s << grid(g) << " -> " << ll << " -> "
					  << gg << " " << grid(gg)  << " Error " <<
					  gridDiff(g,gg) << " log Error " << error << std::endl;
		}
		return (s==gridString(gg)) || (error>3.0) ? 1 : 0;
	}
	return 0;
}


int GridToLatLongViaText::action() {
	coordinates::OSGrid g=generator.grid(tag);
	auto s=gridString(g);
	if(s.size()>0) {
		coordinates::LatitudeLongitude ll(s,tag);
		coordinates::OSGrid gg(ll);
		auto error=logGridDiff(g,gg);
		push(error,3);
		if(verbose) {
					std::cout << s << grid(g) << " -> " << ll << " -> "
							  << gg << " " << grid(gg)  << " Error " <<
							  gridDiff(g,gg) << " log Error " << error << std::endl;
				}
		return (s==gridString(gg)) || (error>3.0) ? 1 : 0;
	}
	return 0;
}

int LatLongToGrid::action() {
	coordinates::LatitudeLongitude l=generator.latLong(tag);
	coordinates::OSGrid g(l);
	coordinates::LatitudeLongitude ll(g,tag);
	auto error=latLongDiff(l, ll);
	return push(error,3);
}

} /* namespace tests */
