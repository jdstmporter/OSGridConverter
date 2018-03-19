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

struct Specification {
public:
		using IList=std::initializer_list<double>;
		Ellipsoid::Name name;
		Vector t;
		Vector r;
		double e;

		Specification() : name(), t(), r(), e(0.0) {};
		Specification(const Ellipsoid::Name &n_,IList r_,IList t_,const double e_);
		Specification(const Specification &) = default;
		virtual ~Specification() = default;
		Specification & operator=(const Specification &) = default;
	};

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

public:
	Datum(const Ellipsoid::Name & model,const Vector &t,const Vector &r,const double s) :  e(Ellipsoid::get(model)), helmert(t,r,s) {};
	Datum(const Ellipsoid::Name & model,const Helmert &h) : e(Ellipsoid::get(model)), helmert(h) {};
	Datum(const Specification & spec) : Datum(spec.name,spec.t,spec.r,spec.e) {};
	Datum(const Datum &o) : e(o.e), helmert(o.helmert) {};
	virtual ~Datum() = default;
	
	const Ellipsoid & ellipsoid() const { return e; }
	Vector operator()(const Vector &v) const { return helmert.transform(v); }
	Vector apply(const Vector &v) const { return helmert.transform(v); }
	Vector invert(const Vector &v) const { return helmert.inverseTransform(v); }


	static Datum get(const Name &key);



};

bool operator==(const Datum &l,const Datum &r);
bool operator!=(const Datum &l,const Datum &r);

} /* namespace mapping */




#endif /* DATUM_HPP_ */




