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


/**
 * \class mapping::Helmert
 * \brief Represents a Helmert transformation betwwen geodetic coordinate systems
 */
class Helmert {
	friend bool operator==(const Helmert &l,const Helmert &r);
	friend bool operator!=(const Helmert &l,const Helmert &r);
private:
	double scale;				/*!< The scale factor */
	util::Vector translation;	/*!< The translation vector */
	util::Vector rotation;			/*!< The rotation matrix */

	util::Matrix matrix() const;	/*<! \return the matrix */


public:
	/**
	 * Default constructor
	 */
	Helmert() : scale(0), translation(3), rotation(3) {};
	/**
		 * Constructs transform from raw information available in a Datum
		 * \param t the translation vector
		 * \param rot vector of (small) Euler angles of the rotation
		 * \param s the datum's scale factor
		 */
	Helmert(const util::Vector & t,const util::Vector & rot, const double s)  : scale(s), translation(t),
			rotation(rot) {};
	/*
	 * Copy constructor
	 * \param o the transformation to copy
	 */
	Helmert(const Helmert &o) : scale(o.scale), translation(o.translation), rotation(o.rotation) {};
	/*
	* Move constructor
	* \param o the transformation to move
	*/
		Helmert(Helmert &&o) : scale(o.scale), translation(std::move(o.translation)), rotation(std::move(o.rotation)) {};
	/**
	 * Destructor
	 */
	virtual ~Helmert() = default;

	/**
	 * Copy assignment operator
	 * \param o the object to copy
	 */
	Helmert & operator=(const Helmert &o);
	/**
		 * Move assignment operator
		 * \param o the object to move
		 */
		Helmert & operator=(Helmert &&o);
	/**
	 * Inverse transformation
	 * \return the inverse to this Helmert transformation
	 */
	Helmert inverse() const;
	/**
	 * Apply the transformation
	 * \param x the util::Vector to transform
	 * \return the transformed util::Vector
	 */
	util::Vector operator()(const util::Vector &x) const;
	//util::Vector operator()(util::Vector &&x) const;
};

/**
 *  \relates mapping::Helmert
 * \brief equality test
 * \details Two instances of mapping::Helmert are equal iff their scales, translations and
 * rotation matrices are the same
 * \param l left-hand-side
 * \param r right-hand-side
 * \return \a l=r
 */
bool operator==(const Helmert &l,const Helmert &r);
/**
 *  \relates mapping::Helmert
 * \brief inequality test
 * \details Two instances of mapping::Helmert are unequal iff their scales or translations or
 * their rotation matrices are unequal
 * \param l left-hand-side
 * \param r right-hand-side
 * \return \a l<>r
 */
bool operator!=(const Helmert &l,const Helmert &r);

} /* namespace mapping */



#endif /* HELMERT_HPP_ */
