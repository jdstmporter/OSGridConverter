/*
 * Helmert.hpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#ifndef HELMERT_HPP_
#define HELMERT_HPP_


#include <valarray>
#include <memory>
#include <stdexcept>
#include "algebra.hpp"


namespace mapping {

bool operator==(const Vector &l,const Vector &r);
bool operator!=(const Vector &l,const Vector &r);

bool operator==(const Matrix &l,const Matrix &r);
bool operator!=(const Matrix &l,const Matrix &r);

class Helmert;
using helmert_t = std::shared_ptr<Helmert>;
enum class HelmertType {
	Exact,
	Approximate
};

helmert_t getHelmertTransform(const HelmertType &type,const Vector &t,const Vector &angles,const double scale);


class Helmert {
	friend bool operator==(const Helmert &l,const Helmert &r);
	friend bool operator!=(const Helmert &l,const Helmert &r);

protected:
	Vector angles;
	Vector t;
	double scale;

	virtual Matrix matrix(const Vector &a,const double sc) const { throw std::runtime_error("Not implemented"); };
	virtual Matrix matrix() const { return matrix(angles,scale); };

	virtual Vector offset() const { return t; };

	virtual Vector invertedAngles() const { throw std::runtime_error("Not implemented"); };

public:


	Helmert() : angles(Zero(3)), t(Zero(3)), scale(1.0) {};
	Helmert(const Vector &t_,const Vector &angles_,const double scale_) : angles(angles_), t(t_), scale(scale_) {};
	Helmert(const Helmert &o) = default;
	virtual ~Helmert() = default;

	Helmert & operator=(const Helmert &o) = default;

	virtual helmert_t inverse() const;
	Vector transform(Vector x) const;

};


bool operator==(const Helmert &l,const Helmert &r);
bool operator!=(const Helmert &l,const Helmert &r);



} /* namespace mapping */



#endif /* HELMERT_HPP_ */
