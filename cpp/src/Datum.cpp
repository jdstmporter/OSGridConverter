/*
 * Datum.cpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#include "Datum.hpp"
#include "Vector.hpp"
#include <algorithm>


namespace mapping {


Datum::Datum(const Ellipsoid::Name & model,const util::Vector &t,const util::Vector &r,const double s) :
	e(Ellipsoid::get(model)), helmert(Helmert(t,r,s)) {};
Datum::Datum(const Ellipsoid::Name & model,const Helmert &h) :
	e(Ellipsoid::get(model)), helmert(h) {};



Datum Datum::get(const Name &key) {
	switch(key) {
	case Name::WGS84:
		return Datum(Ellipsoid::Name::WGS84,util::Vector({0.0,0.0,0.0}),util::Vector({0.0,0.0,0.0}),0.0);
	case Name::NTF:
		return Datum(Ellipsoid::Name::Clarke1880,util::Vector({168.0,60.0,-320.0}),util::Vector({0.0,0.0,0.0}),0.0);
	case Name::NAD83:
		return Datum(Ellipsoid::Name::GRS80,util::Vector({1.004,-1.910,-0.515}),util::Vector({0.0267,0.00034,0.011}),-0.0015);
	case Name::OSGB36:
		return Datum(Ellipsoid::Name::Airy1830,util::Vector({-446.448,125.157,-542.060}),util::Vector({-0.1502,-0.2470,-0.8421}),20.4894);
	default:
		return Datum(Ellipsoid::Name::Airy1830,util::Vector({-446.448,125.157,-542.060}),util::Vector({-0.1502,-0.2470,-0.8421}),20.4894);
	}
}

util::Vector Datum::operator()(const util::Vector &v) const { return helmert(v); }
util::Vector Datum::operator()(util::Vector &&v) const { return std::move(helmert(v)); }
util::Vector Datum::apply(const util::Vector &v) const { return helmert(v); }
util::Vector Datum::invert(const util::Vector &v) const { return helmert.inverse()(v); }



bool operator==(const Datum &l,const Datum &r) {
	return (l.e==r.e) && (l.helmert==r.helmert);
}
bool operator!=(const Datum &l,const Datum &r){
	return (l.e!=r.e) || (l.helmert!=r.helmert);
}


}
