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
private:
	double A;
	double B;
	double f;
	double e1;
	double e2;
	double n;
	Vector M;

public:


	Ellipsoid(const double a=1.0,const double b=1.0) noexcept;
	Ellipsoid(const std::vector<double> &params) noexcept : Ellipsoid(params[0],params[1]) {};
	Ellipsoid(const Ellipsoid &other) noexcept : Ellipsoid(other.A,other.B) {};
	Ellipsoid & operator==(const Ellipsoid &other) noexcept;
	virtual ~Ellipsoid() = default;
	
	double eccentricity1() noexcept { return e1; }
	double eccentricity2() noexcept { return e2; }
	double majorAxis() noexcept { return A; }
	double minorAxis() noexcept { return B; }
	double flattening() noexcept { return f; }
	
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
	using Parameters=std::map<Name,std::vector<double>>;
	static Parameters ellipsoids;
	static void initialise();

};



} /* namespace mapping */



#endif /* ELLIPSOID_HPP_ */
