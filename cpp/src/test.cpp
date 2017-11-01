/*
 * test.cpp
 *
 *  Created on: 29 Jul 2017
 *      Author: julianporter
 */

#include <test.hpp>
#include <iostream>








int GridToLatLong::action() {
	coordinates::OSGrid g=generator.grid(tag);
	auto s=test::gridString(g);
	if(s.size()>0) {
		coordinates::LatitudeLongitude ll(g,tag);
		coordinates::OSGrid gg(ll);
		auto error=test::gridDiff(g,gg);
		push(error,3);
		auto value =  (s==test::gridString(gg));
		if(!value) {
			std::cout << "ERROR: " << s << " " << g << " -> " << ll << " -> " << gg << std::endl;
		}
		return (s==test::gridString(gg)) || (error>3.0) ? 1 : 0;
	}
	return 0;
}


int GridToLatLongViaText::action() {
	coordinates::OSGrid g=generator.grid(tag);
	auto s=test::gridString(g);
	if(s.size()>0) {
		coordinates::LatitudeLongitude ll(s,tag);
		coordinates::OSGrid gg(ll);
		auto error=test::gridDiff(g,gg);
		push(error,3);
		auto value =  (s==test::gridString(gg));
		if(!value) {
			std::cout << "ERROR: " << s << " " << g << " -> " << ll << " -> " << gg << std::endl;
		}
		return (s==test::gridString(gg)) || (error>3.0) ? 1 : 0;
	}
	return 0;
}
