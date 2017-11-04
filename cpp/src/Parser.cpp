/*
 * Parser.cpp
 *
 *  Created on: 5 Aug 2017
 *      Author: julianporter
 */

#include "Parser.hpp"
#include "OSGrid.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>


namespace coordinates {

const std::regex Parser::lonlatNSEW ("^\\s*([+-]?(?:\\d*\\.)?\\d+)([ns])\\s*,\\s*([+-]?(?:\\d*\\.)?\\d+)([ew])\\s*$",std::regex::icase);
const std::regex Parser::lonlatPM   ("^\\s*([+-]?(?:\\d*\\.)?\\d+)\\s*,\\s*([+-]?(?:\\d*\\.)?\\d+)\\s*$",std::regex::icase);
const std::regex Parser::gridOS1     ("^\\s*([A-Z]{2})\\s*([0-9]+)\\s*$",std::regex::icase);
const std::regex Parser::gridOS2     ("^\\s*([A-Z]{2})\\s*([0-9]+)\\s+([0-9]+)\\s*$",std::regex::icase);
const std::string Parser::gridAlphabet="ABCDEFGHJKLMNOPQRSTUVWXYZ";

std::string toUpper(const std::string &str) {
	std::stringstream s;
	s << std::uppercase << str;
	return s.str();
}
unsigned padTo(const std::string &s,const unsigned n) {
	auto out=(s+std::string(n,'0')).substr(0,n);
	return std::stoul(out);
}

Parser::Result Parser::isLatLong() {
	try {
		if (std::regex_match(text,m,Parser::lonlatNSEW)) {
			double lat = std::stod(m[1]);
			auto ns =m[2];
			if(ns=="s" || ns=="S") lat*=-1.0;

			double lon = std::stod(m[3]);
			auto ew =m[4];
			if(ew=="w" || ew=="W") lon*=-1.0;

			return Result(Kind::LatLong,lat,lon);
		}
		else if (std::regex_match(text,m,Parser::lonlatPM)) {
			double lat = std::stod(m[1]);
			double lon = std::stod(m[2]);
			return Result(Kind::LatLong,lat,lon);
		}
	}
	catch(...) {}
	return Result();
}

Parser::Result Parser::completeGrid(const std::string & e,const std::string & n) {
	std::string letters=m[1];
	auto l1=Parser::gridAlphabet.find(letters.at(0));
	auto l2=Parser::gridAlphabet.find(letters.at(1));
	if(l1==std::string::npos || l2==std::string::npos) return Result();
	int e100km=((l1-2)%5)*5 + (l2%5);
	int n100km=19-5*int(l1/5) - int(l2/5);
	if(e100km<0 || e100km>6 || n100km<0 || n100km>12) return Result();

	auto ee=padTo(e,5);
	auto nn=padTo(n,5);
	return Result(Kind::Grid,ee+e100km*1.0e5,nn+n100km*1.0e5);
}

Parser::Result Parser::isGrid() {
	try {
		auto grid=toUpper(text);
		if (std::regex_match(grid,m,Parser::gridOS1)) {
			std::string numbers=m[2];
			unsigned l=numbers.size()/2;
			if(numbers.size()!=2*l) return Result();
			auto e=numbers.substr(0,l);
			auto n=numbers.substr(l,l);

			return completeGrid(e,n);
		}
		else if (std::regex_match(grid,m,Parser::gridOS2)) {
			auto e=m[2];
			auto n=m[3];
			return completeGrid(e,n);
		}
	}
	catch(std::exception &e) {
		std::cerr << "Failed to parse as grid : " << e.what() << std::endl;
	}
	return Result();
}

Parser::Kind Parser::parse() {
	auto r = isLatLong();
	if(r.kind==Kind::LatLong) parameters=r;
	else {
		auto r = isGrid();
		if(r.kind==Kind::Grid) parameters=r;
		else parameters=Result();
	}
	return parameters.kind;
}





} /* namespace coordinates */
