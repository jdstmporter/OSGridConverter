/*
 * OSGB36.cpp
 *
 *  Created on: 1 Aug 2017
 *      Author: julianporter
 */

#include "OSGB36.hpp"


namespace mapping {

const double OSGB36::F0      = 0.9996012717;
const double OSGB36::phi0    = radians(49.0);
const double OSGB36::lambda0 = radians(-2.0);
const int OSGB36::N0 = -100000;
const int OSGB36::E0 =  400000;

OSGB36::OSGB36(double Phi,double LambdaE) : ellipsoid(Ellipsoid::get(Ellipsoid::Name::Airy1830)),phi(Phi), E(LambdaE), transforms() {
	auto s=sin(phi);
	auto c=cos(phi);
	auto t=tan(phi);
	auto t2=t*t;
	auto t4=t2*t2;
	auto t6=t4*t2;
	auto e=ellipsoid.eccentricity1();
	auto af=ellipsoid.majorAxis()*OSGB36::F0;
	auto v = 1.0-e*s*s;
	auto nu = af/sqrt(v);
	auto nu3=nu*nu*nu;
	auto nu5=nu3*nu*nu;
	auto nu7=nu5*nu*nu;
	auto nc=nu*c;
	auto nc3=nc*c*c;
	auto nc5=nc3*c*c;
	auto rho = af*(1-e)*pow(v,-1.5);
	auto eta1 = nu/rho;
	auto eta2 = eta1-1.0;
	auto M = ellipsoid.meridional(phi, OSGB36::phi0)*ellipsoid.minorAxis()*OSGB36::F0;

	transforms[Tr::I] = M+OSGB36::N0;
	transforms[Tr::II] = nc*s/2.0;
	transforms[Tr::III] = nc3*s*(5.0-t2+9.0*nu*nu)/24.0;
	transforms[Tr::IIIA] = nc5*s*(61.0-58.0*t2+t4)/720.0;
	transforms[Tr::IV] = nc;
	transforms[Tr::V] = nc3*(eta1-t2)/6.0;
	transforms[Tr::VI] = nc5*(5.0- 18.0*t2+t4+14.0*eta2-58.0*t2*eta2)/120.0;
	transforms[Tr::VII] = t/(2.0*rho*nu);
	transforms[Tr::VIII] = t/(24.0*rho*nu3*(5.0+3.0*t2+eta2-9.0*t2*eta2));
	transforms[Tr::IX] = t/(720.0*rho*nu5*(61.0+90.0*t2+45.0*t4));
	transforms[Tr::X] = 1.0/(c*nu);
	transforms[Tr::XI] = 1.0/(6.0*c*nu3*(eta1+2.0*t2));
	transforms[Tr::XII] = 1.0/(120.0*c*nu5*(5.0+28.0*t2+24.0*t4));
	transforms[Tr::XIIA] = 1.0/(5040.0*c*nu7*(61.0+662.0*t2+1320.0*t4+720.0*t6));
}

OSGB36::Pair OSGB36::toLatLong() {
	auto dE = E-OSGB36::E0;
	auto p  = phi - transforms[Tr::VII]*pow(dE,2) + transforms[Tr::VIII]*pow(dE,4) - transforms[Tr::IX]*pow(dE,6);
	auto l  = OSGB36::lambda0 + transforms[Tr::X]*dE - transforms[Tr::XI]*pow(dE,3) + transforms[Tr::XII]*pow(dE,5) - transforms[Tr::XIIA]*pow(dE,7);
	return std::make_tuple(p,l);
}
OSGB36::Pair OSGB36::fromLatLong() {
	auto dl = E-OSGB36::lambda0;
    auto n  = transforms[Tr::I] + transforms[Tr::II]*pow(dl,2) + transforms[Tr::III]*pow(dl,4) + transforms[Tr::IIIA]*pow(dl,6);
    auto e  = OSGB36::E0 + transforms[Tr::IV]*dl + transforms[Tr::V]*pow(dl,3) + transforms[Tr::VI]*pow(dl,5);
    return std::make_tuple(e,n);
}

} /* namespace mapping */
