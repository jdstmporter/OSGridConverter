/*
 * OSGrid.hpp
 *
 *  Created on: 6 Aug 2017
 *      Author: julianporter
 */

#ifndef SRC_COORDINATES_OSGRID_HPP_
#define SRC_COORDINATES_OSGRID_HPP_

#include <string>
#include <iostream>
#include <tuple>

namespace coordinates {

class LatitudeLongitude;

class OSGrid {
friend std::ostream & operator<<(std::ostream &o,const OSGrid &grid);
friend bool operator==(const OSGrid &l,const OSGrid &r);
friend bool operator!=(const OSGrid &l,const OSGrid &r);
private:
	long northings;
	long eastings;
public:
	OSGrid(const std::string & slug);
	OSGrid(const LatitudeLongitude &latlong);
	OSGrid(const double N,const double E) : northings(N), eastings(E) {};
	OSGrid(const long N,const long E) : northings(N), eastings(E) {};
	virtual ~OSGrid() = default;
	
	std::tuple<long,long> coordinates() const { return std::make_tuple(eastings,northings); }
	
};

} /* namespace coordinates */

std::ostream & operator<<(std::ostream &o,const coordinates::OSGrid &grid);
bool operator==(const coordinates::OSGrid &l,const coordinates::OSGrid &r);
bool operator!=(const coordinates::OSGrid &l,const coordinates::OSGrid &r);

#endif /* SRC_COORDINATES_OSGRID_HPP_ */
