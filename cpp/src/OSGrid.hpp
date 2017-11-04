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
#include <ios>
#include <tuple>

namespace coordinates {

class LatitudeLongitude;

class OSGrid {
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
	long N() const { return northings; }
	long E() const { return eastings; }
};

bool operator==(const OSGrid &l,const OSGrid &r);
bool operator!=(const OSGrid &l,const OSGrid &r);



} /* namespace coordinates */

struct _Grid { coordinates::OSGrid g; };


  inline _Grid
  grid(const coordinates::OSGrid &g)
  { return { g }; }


  template<typename _CharT, typename _Traits>
    inline std::basic_ostream<_CharT, _Traits>&
    operator<<(std::basic_ostream<_CharT, _Traits>& __os, _Grid __g)
    {
	  auto g=__g.g;
	  __os << "(" << g.N() << "N, " << g.E() << "E)";
      return __os;
    }

std::ostream & operator<<(std::ostream & o,const coordinates::OSGrid &g);

#endif /* SRC_COORDINATES_OSGRID_HPP_ */
