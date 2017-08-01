/*
 * OSGB36.hpp
 *
 *  Created on: 1 Aug 2017
 *      Author: julianporter
 */

#ifndef OSGB36_HPP_
#define OSGB36_HPP_

#include "algebra.hpp"
#include "Datum.hpp"
#include "Ellipsoid.hpp"
#include <map>
#include <tuple>
#include <cmath>


namespace mapping {

class OSGB36 {
private:
	enum class Tr {
		I, II, III, IIIA, IV, V, VI, VII, VIII, IX, X, XI, XII, XIIA
	};

	Ellipsoid ellipsoid;
	double phi;
	double E;
	std::map<Tr,double> transforms;
public:
	using Pair=std::tuple<double,double>;

	static const double F0;
	static const double phi0;
	static const double lambda0;
	static const int N0;
	static const int E0;

	OSGB36(double Phi,double LambdaE);
	virtual ~OSGB36() = default;
	
	double operator[](const Tr t) { return transforms[t]; }

	Pair toLatLong();
	Pair fromLatLong();
	
	
};

} /* namespace mapping */

#endif /* OSGB36_HPP_ */
