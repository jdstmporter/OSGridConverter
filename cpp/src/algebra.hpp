/*
 * algebra.hpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#ifndef ALGEBRA_HPP_
#define ALGEBRA_HPP_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#define PI 3.14159265359
#define radians(x) (x*PI/180.0)

namespace mapping {

using Vector = boost::numeric::ublas::vector<double>;
using Zero   = boost::numeric::ublas::zero_vector<double>;
using Matrix = boost::numeric::ublas::matrix<double>;
using ID     = boost::numeric::ublas::identity_matrix<double>;



}

#endif /* ALGEBRA_HPP_ */
