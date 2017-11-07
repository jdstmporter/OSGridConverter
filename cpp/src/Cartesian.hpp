/*
 * Cartesian.hpp
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef CARTESIAN_HPP_
#define CARTESIAN_HPP_

#include "Vector.hpp"
#include "Helmert.hpp"
#include "Ellipsoid.hpp"

/**
 * \class coordinates::Cartesian
 * \brief Cartesian representation of a point
 *
 * Represents a point on the Earth's surface in Cartesianco-ordinates, so as a point in
 * three-dimensional space.  Includes machinery to perform Helmert transforms, corresponding to
 * changing from one two-dimensional mapping of the surface to another.
 */

namespace coordinates {

class Cartesian {
public:
	/**
	 * Labels for the cartesian axes
	 */
	enum class Axis : unsigned {
		X = 0,	/*!< X-axis */
		Y = 1,  /*!< Y-axis */
		Z = 2   /*!< Z-axis */
	};
private:
	util::Vector vector;
public:
	/**
	Construct instance with specified coordinates
	\param v util::Vector of coordinates (defaults to zero vector)
	*/
	Cartesian(const util::Vector &v = util::Vector(3)) : vector(v) {};
	/**
	Construct instance with specified coordinates
	\param x the x-coordinate
	\param y the x-coordinate
	\param z the x-coordinate
	*/
	Cartesian(const double x,const double y,const double z);
	/**
	 * Copy constructor
	 * \param o instance to copy
	 */
	Cartesian(const Cartesian &o) : vector(o.vector) {};
	/**
	 * Destructor
	 */
	virtual ~Cartesian() = default;

	/**
	 * Norm of projection onto X-Y plane
	 * \details If the vector is (x,y,z), this is the square-root of x*x+y*y
	 * \return sqrt(x*x+y*y)
	 */
	double P() const;
	/**
	 * Vector norm squared
	 * \return norm squared of underlying vector
	 */
	double RSquared() const;
	/**
	 * Read-only access to vector component
	 * \param axis - the axis corresponding to the coordinate to return
	 * \return the component along that axis
	 */
	double operator[](const Axis &axis) const;
	/**
	 * Helmert transform
	 * \details Apply the provided Helmert transform to give a new set of coordinates
	 * \param helmert the Helmert transform to apply
	 * \return the transformed coordinates
	 */
	Cartesian transform(const mapping::Helmert &helmert);
	/**
	 * Return the underlying vector
	 * \return the underlying vector
	 */
	util::Vector vec() const { return vector; }
};


} /* namespace coordinates */


#endif /* CARTESIAN_HPP_ */
