/*
 * Specification.hpp
 *
 *  Created on: 3 Nov 2017
 *      Author: julianporter
 */

#ifndef SPECIFICATION_HPP_
#define SPECIFICATION_HPP_

#include "Vector.hpp"
#include "Ellipsoid.hpp"
#include "Helmert.hpp"
#include <tuple>
#include <initializer_list>

namespace mapping {

struct Specification {
public:
		using IList=std::initializer_list<double>;
		Ellipsoid::Name name;
		util::Vector t;
		util::Vector r;
		double e;

		Specification() : name(), t(3), r(3), e(0.0) {};
		Specification(const Ellipsoid::Name &n_,IList r_,IList t_,const double e_);
		Specification(const Specification &) = default;
		virtual ~Specification() = default;
		Specification & operator=(const Specification &) = default;
	};

}



#endif /* SPECIFICATION_HPP_ */
