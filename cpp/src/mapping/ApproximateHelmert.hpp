/*
 * ApproximateHelmert.hpp
 *
 *  Created on: 1 Mar 2018
 *      Author: julianporter
 */

#ifndef MAPPING_APPROXIMATEHELMERT_HPP_
#define MAPPING_APPROXIMATEHELMERT_HPP_

#include "Helmert.hpp"

namespace mapping {
namespace helmert {

class ApproximateHelmert : public Helmert {
private:

	static std::valarray<unsigned> indices(const unsigned index);

protected:
	virtual Matrix matrix(const Vector &a,const double sc) const;
	virtual Vector invertedAngles() const;

public:
	ApproximateHelmert() : Helmert() {};
	ApproximateHelmert(const Vector & T,const Vector & R, const double S) : Helmert(T,R,S) {};
	ApproximateHelmert(const ApproximateHelmert &o) = default;
	virtual ~ApproximateHelmert() = default;

	ApproximateHelmert & operator=(const ApproximateHelmert &o) = default;
};


} /* namespace helmert */
} /* namespace mapping */

#endif /* MAPPING_APPROXIMATEHELMERT_HPP_ */
