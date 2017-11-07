/*
 * Datum.h
 *
 *  Created on: 31 Jul 2017
 *      Author: julianporter
 */

#ifndef DATUM_HPP_
#define DATUM_HPP_

#include "Vector.hpp"
#include "Ellipsoid.hpp"
#include "Helmert.hpp"
#include <tuple>
#include <initializer_list>


namespace mapping {


/**
 * \class mapping::Datum
 * \brief Represents a mapping datum
 *
 * A mapping datum is the data used to project the surface of the earth onto a two-dimensional surface.
 * It consists of a model ellipsoid (i.e.. model of the Earth's geoid in the region of interest) and
 * subsidiary information setting baseline coordinate information for the datum.  This class contains
 * the information required to specify a datum.  In addition, examples of some well-known data are
 * provided.
 */
class Datum {
	friend bool operator==(const Datum &l,const Datum &r);
	friend bool operator!=(const Datum &l,const Datum &r);
public:
	/**
	 * Names of the well-known data available out of the box
	 */
	enum class Name {
			WGS84,		/*!< World Geodetic System 84 : current UK Ordnance survey standard datum */
			NTF,		/*!< French standard datum */
			NAD83,		/*!< North American Datum 93 */
			OSGB36,		/*!< Ordnance Survey of Great Britain 36 : former Ordnance survey datum as used in older maps */
			ED50,		/*!< European Datum 50 */
			Irl1975,	/*!< Irish Republic datum 75 */
			TokyoJapan  /*!< Japanese standard Datum */
		};
private:
	Ellipsoid e;
	Helmert helmert;



public:
	/**
	 * Constructs a datum from raw data
	 *
	 * Generally for use with literal definitions
	 * \param model the tag naming the ellipsoid to use
	 * \param t the translation util::Vector
	 * \param r the Euler angles of the rotation matrix
	 * \param s the scale factor for the datum
	 */
	Datum(const Ellipsoid::Name & model,const util::Vector &t,const util::Vector &r,const double s);
	/**
	 * Construct a datum from an ellipsoid and a Helmert transform
	 * \param model the tag naming the ellipsoid to use
	 * \param h the Helmert transform
	 */
	Datum(const Ellipsoid::Name & model,const Helmert &h);

	/**
	 * Copy constructor
	 * \param o the object to copy
	 */
	Datum(const Datum &o) : e(o.e), helmert(o.helmert) {};
	/**
	 * Destructor
	 */
	virtual ~Datum() = default;
	


	/**
	 * Get the ellipsoid
	 * \return Ellipsoid
	 */
	const Ellipsoid & ellipsoid() const { return e; }
	/**
	 * Apply Helmert transform to vector
	 * \param v Vector to transform
	 * \return Transformed vector
	 */
	util::Vector operator()(const util::Vector &v) const;
	/**
	 * Apply Helmert tranfrom to vector and \e move the result
	 * \param v Vector to transform
	 * \return Transformed \b rvalue vector
	 */
	util::Vector operator()(util::Vector &&v) const;
	/**
		 * Apply Helmert transform to vector
		 * \param v Vector to transform
		 * \return Transformed vector
		 */
	util::Vector apply(const util::Vector &v) const;
	/**
		 * Apply inverse Helmert transform to vector
		 * \param v Vector to transform
		 * \return Transformed vector
		 */
	util::Vector invert(const util::Vector &v) const;

/**
 * Get one of the pre-configured named data
 * \param key the name of the datum to get
 * \returns the desired Datum
 */
	static Datum get(const Name &key);



};

bool operator==(const Datum &l,const Datum &r);
bool operator!=(const Datum &l,const Datum &r);

std::string name(const Datum::Name & n);

} /* namespace mapping */




#endif /* DATUM_HPP_ */




