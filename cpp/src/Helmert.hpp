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
	double scale;				
	util::Vector translation;	
	util::Vector rotation;			

	util::Matrix matrix() const;	


public:

	Helmert() : scale(0), translation(3), rotation(3) {};
	Helmert(const util::Vector & t,const util::Vector & rot, const double s)  : scale(s), translation(t),
			rotation(rot) {};
    /*! \brief Copy constructor */
	Helmert(const Helmert &o) : scale(o.scale), translation(o.translation), rotation(o.rotation) {};
	/*! \brief Move constructor */ 
	Helmert(Helmert &&o) : scale(o.scale), translation(std::move(o.translation)), rotation(std::move(o.rotation)) {}; 
	virtual ~Helmert() = default;

	/*! \brief Copy assign */
	Helmert & operator=(const Helmert &o);
	/*! \brief Move assign */
	Helmert & operator=(Helmert &&o);

	Helmert inverse() const;

	util::Vector operator()(const util::Vector &x) const;
	//util::Vector operator()(util::Vector &&x) const;
};


bool operator==(const Helmert &l,const Helmert &r);
bool operator!=(const Helmert &l,const Helmert &r);

} /* namespace mapping */



#endif /* HELMERT_HPP_ */
