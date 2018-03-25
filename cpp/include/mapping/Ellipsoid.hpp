/*
 * Ellipsoid.hpp
 *
 *  Created on: 29 Jul 2017
 *      Author: julianporter
 */

#ifndef ELLIPSOID_HPP_
#define ELLIPSOID_HPP_

#include "algebra.hpp"
#include <map>
#include <memory>
#include <vector>


namespace mapping {



class Ellipsoid {
	friend bool operator==(const Ellipsoid &l,const Ellipsoid &r);
	friend bool operator!=(const Ellipsoid &l,const Ellipsoid &r);
private:

	struct Axes {
		double a;
		double b;
		double f;

		Axes(const double a_=1.0,const double b_=1.0,double f_=0.0) : a(a_), b(b_), f(f_) {};
		virtual ~Axes()=default;
	};

	double A;
	double B;
	double f;
	double e1;
	double e2;
	double n;
	Vector M;

public:


	Ellipsoid(const double a=1.0,const double b=1.0, double f=0.0) noexcept;
	Ellipsoid(const Axes &a) noexcept : Ellipsoid(a.a,a.b,a.f) {};
	Ellipsoid(const Ellipsoid &other) noexcept : Ellipsoid(other.A,other.B,other.f) {};
	Ellipsoid & operator==(const Ellipsoid &other) noexcept;
	virtual ~Ellipsoid() = default;
	
	double eccentricity1() const noexcept { return e1; }
	double eccentricity2() const noexcept { return e2; }
	double majorAxis() const noexcept { return A; }
	double minorAxis() const noexcept { return B; }
	double flattening() const noexcept { return f; }
	double N() const noexcept { return n; }
	
	double meridional(double phi,double phi0) noexcept;

	enum class Name {
		WGS84,
		GRS80,
		Airy1830,
		AiryModified,
		Intl1924,
		Bessel1841,
		Clarke1880
	};
	static Ellipsoid get(const Name &key);


private:
	using Parameters=std::map<Name,Axes>;
	static Parameters ellipsoids;
	static void initialise();

};
bool operator==(const mapping::Ellipsoid &l,const mapping::Ellipsoid &r);
bool operator!=(const mapping::Ellipsoid &l,const mapping::Ellipsoid &r);


} /* namespace mapping */


#endif /* ELLIPSOID_HPP_ */
