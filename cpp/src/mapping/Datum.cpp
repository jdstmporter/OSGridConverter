/*
 * Datum.cpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#include "Datum.hpp"
#include <algorithm>


namespace mapping {


Vector _v(double x,double y,double z) {
	Vector v(3);
	v[0]=x;
	v[1]=y;
	v[2]=z;
	return v;
}


Datum Datum::get(const DatumName &key) {
	switch(key) {
	case DatumName::WGS84:
		return Datum(Ellipsoid::Name::WGS84,_v(0.0,0.0,0.0),_v(0.0,0.0,0.0),0.0);
	case DatumName::NTF:
		return Datum(Ellipsoid::Name::Clarke1880,_v(168.0,60.0,-320.0),_v(0.0,0.0,0.0),0.0);
	case DatumName::NAD83:
		return Datum(Ellipsoid::Name::GRS80,_v(1.004,-1.910,-0.515),_v(0.0267,0.00034,0.011),-0.0015);
	case DatumName::OSGB36:
		return Datum(Ellipsoid::Name::Airy1830,_v(-446.448,125.157,-542.060),_v(-0.1502,-0.2470,-0.8421),20.4894);
	default:
		return Datum(Ellipsoid::Name::Airy1830,_v(-446.448,125.157,-542.060),_v(-0.1502,-0.2470,-0.8421),20.4894);
	}
}




}

std::ostream & operator<<(std::ostream &o,const mapping::Datum &d) {
	o << d.ellipsoid() << ", HELMERT";
	return o;
}


