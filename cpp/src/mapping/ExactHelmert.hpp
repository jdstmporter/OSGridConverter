/*
 * ExactHelmert.hpp
 *
 *  Created on: 1 Mar 2018
 *      Author: julianporter
 */

#ifndef MAPPING_EXACTHELMERT_HPP_
#define MAPPING_EXACTHELMERT_HPP_

#include "Helmert.hpp"

namespace mapping {
namespace helmert {

class ExactHelmert : public Helmert {
private:

protected:

	virtual Matrix matrix(const Vector &a,const double sc) const;
	virtual Vector invertedAngles() const;


public:
	ExactHelmert() : Helmert() {};
	ExactHelmert(const Vector &angles_, const Vector &t_, const double scale_) : Helmert(angles_,t_,scale_) {};
	ExactHelmert(const ExactHelmert &o) = default;
	virtual ~ExactHelmert() = default;

	ExactHelmert & operator=(const ExactHelmert &o) = default;
};


} /* namespace helmert */
} /* namespace mapping */

#endif /* MAPPING_EXACTHELMERT_HPP_ */
