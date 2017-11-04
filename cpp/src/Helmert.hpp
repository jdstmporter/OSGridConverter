/*
 * Helmert.hpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#ifndef HELMERT_HPP_
#define HELMERT_HPP_


#include <valarray>
#include "Vector.hpp"
#include "Matrix.hpp"


namespace mapping {



class Helmert {
	friend bool operator==(const Helmert &l,const Helmert &r);
	friend bool operator!=(const Helmert &l,const Helmert &r);
private:
	util::Vector t;
	util::Matrix mx;
	util::Matrix inv;

	double determinant();
	static util::Matrix matrix(const util::Vector &r, const double s);
	static util::Matrix inverseMatrix(const util::Vector &r, const double s);
	static std::valarray<unsigned> indices(const unsigned index);

public:
	Helmert() : t(3), mx(3), inv(3) {};
	Helmert(const util::Vector & T, const util::Matrix & MX, const util::Matrix &INV) : t(T),  mx(MX), inv(INV) {};
	Helmert(const util::Vector & T,const util::Vector & R, const double S);
	Helmert(const Helmert &o) : t(o.t), mx(o.mx), inv(o.inv) {};
	virtual ~Helmert() = default;

	Helmert & operator=(const Helmert &o);
	Helmert inverse() const;
	util::Vector operator()(const util::Vector &x) const;
	//util::Vector operator()(util::Vector &&x) const;
};

bool operator==(const Helmert &l,const Helmert &r);
bool operator!=(const Helmert &l,const Helmert &r);

} /* namespace mapping */



#endif /* HELMERT_HPP_ */
