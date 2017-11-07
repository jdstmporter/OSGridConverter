/*
 * algebra.hpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#ifndef ALGEBRA_HPP_
#define ALGEBRA_HPP_


#include <cmath>

/**
 * def PI
 * Returns the value of PI
 */
#define PI 3.14159265359
/**
 * def radians(x)
 * Converts \a x from degrees to radians
 */
#define radians(x) (x*PI/180.0)
/**
 * def degrees(x)
 * Converts \a x from radians to degrees
 */
#define degrees(x) (x*180.0/PI)



#endif /* ALGEBRA_HPP_ */
