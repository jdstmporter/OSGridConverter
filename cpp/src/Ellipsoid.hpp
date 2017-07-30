/*
 * Ellipsoid.hpp
 *
 *  Created on: 29 Jul 2017
 *      Author: julianporter
 */

#ifndef ELLIPSOID_HPP_
#define ELLIPSOID_HPP_

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <map>
#include <memory>

using namespace boost::numeric::ublas;

namespace mapping {



class Ellipsoid {
private:
	double A;
	double B;
	double f;
	double e1;
	double e2;
	double n;
	vector<double> M;
	
	
	
public:
	Ellipsoid(const double a=1.0,const double b=1.0) noexcept;
	Ellipsoid(const Ellipsoid &other) noexcept : Ellipsoid(other.A,other.B) {};
	Ellipsoid & operator==(const Ellipsoid &other) noexcept;
	virtual ~Ellipsoid() = default;
	
	double eccentricity1() noexcept { return e1; }
	double eccentricity2() noexcept { return e2; }
	double majorAxis() noexcept { return A; }
	double minorAxis() noexcept { return B; }
	double flattening() noexcept { return f; }
	
	double meridional(double phi,double phi0) noexcept;


};

class Model {
public:
	enum class Name {
		WGS84,
		GRS80,
		Airy1830,
		AiryModified,
		Intl1924,
		Bessel1841,
		Clarke1880
	};
private:
	std::map<Name,Ellipsoid> ellipsoids;
	static std::shared_ptr<Model> the;
public:
	

	
	Model();
	virtual ~Model() = default;
	
	Ellipsoid get(const Name &key) { return ellipsoids[key]; }
	static Ellipsoid ellipsoid(const Name &key);
};

} /* namespace mapping */



#endif /* ELLIPSOID_HPP_ */
