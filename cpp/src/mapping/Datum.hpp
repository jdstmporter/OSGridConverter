/*
 * Datum.h
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef DATUM_HPP_
#define DATUM_HPP_

#include "algebra.hpp"
#include "Ellipsoid.hpp"
#include "Helmert.hpp"
#include <tuple>
#include <initializer_list>


namespace mapping {



class Datum {
	friend bool operator==(const Datum &l,const Datum &r);
	friend bool operator!=(const Datum &l,const Datum &r);
public:
	enum class Name {
			WGS84,
			NTF,
			NAD83,
			OSGB36,
			ED50,
			Irl1975,
			TokyoJapan
		};
private:
	Ellipsoid e;
	Helmert helmert;
	using Specification=std::tuple<Ellipsoid::Name,std::initializer_list<double>,std::initializer_list<double>,double>;

public:
	Datum(const Ellipsoid::Name & model,const Vector &t,const Vector &r,const double s) :  e(Ellipsoid::get(model)), helmert(Helmert(t,r,s)) {};
	Datum(const Ellipsoid::Name & model,const Helmert &h) : e(Ellipsoid::get(model)), helmert(h) {};
	Datum(const Datum &o) : e(o.e), helmert(o.helmert) {};
	virtual ~Datum() = default;
	
	const Ellipsoid & ellipsoid() const { return e; }
	Vector & operator()(const Vector &v) const { return helmert(v); }
	Vector & apply(const Vector &v) const { return helmert(v); }
	Vector & invert(const Vector &v) const { return helmert.inverse()(v); }



	static Datum get(const Name &key);

private:
	using Parameters=std::map<Datum::Name,Specification>;
	static Parameters data;
	static void initialise();

};



} /* namespace mapping */

bool operator==(const mapping::Datum &l,const mapping::Datum &r);
bool operator!=(const mapping::Datum &l,const mapping::Datum &r);


#endif /* DATUM_HPP_ */




