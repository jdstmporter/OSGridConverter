/*
 * Datum.cpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#include "Datum.hpp"
#include <algorithm>


namespace mapping {



Datum::Parameters Datum::data = Datum::Parameters();

void Datum::initialise() {
	data[Name::WGS84]      = Specification(Ellipsoid::Name::WGS84,{0.0,0.0,0.0},{0.0,0.0,0.0},0.0);
	data[Name::NTF]        = Specification(Ellipsoid::Name::Clarke1880,{168.0,60.0,-320.0},{0.0,0.0,0.0},0.0);
	data[Name::NAD83]      = Specification(Ellipsoid::Name::GRS80,{1.004,-1.910,-0.515},{0.0267,0.00034,0.011},-0.0015);
	data[Name::OSGB36]     = Specification(Ellipsoid::Name::Airy1830,{-446.448,125.157,-542.060},{-0.1502,-0.2470,-0.8421},20.4894);
	data[Name::ED50]       = Specification(Ellipsoid::Name::Intl1924,{89.5,93.8,123.1},{0.0,0.0,0.156},-1.2);
	data[Name::Irl1975]    = Specification(Ellipsoid::Name::AiryModified,{-482.530,130.596,-564.557},{-1.042,-0.214,-0.631},-8.150);
	data[Name::TokyoJapan] = Specification(Ellipsoid::Name::Bessel1841,{148.0,-507.0,-685.0},{0.0,0.0,0.0},0.0);
}

Vector _v(const std::initializer_list<double> values) {
	Vector v(3);
	std::copy_n(values.begin(),3,v.begin());
	return std::move(v);
}

Datum Datum::get(const Name &key) {
	if(data.size()==0) initialise();
	auto spec=data[key];
	return std::move(Datum(std::get<0>(spec),_v(std::get<1>(spec)),_v(std::get<2>(spec)),std::get<3>(spec),std::make_shared<Name>(key)));
}

}

bool operator==(const mapping::Datum &l,const mapping::Datum &r) {
	return (l.e==r.e) && (l.helmert==r.helmert);
}
bool operator!=(const mapping::Datum &l,const mapping::Datum &r){
	return (l.e!=r.e) || (l.helmert!=r.helmert);
}



