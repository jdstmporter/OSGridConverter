/*
 * Parser.hpp
 *
 *  Created on: 5 Aug 2017
 *      Author: julianporter
 */

#ifndef COORDINATES_PARSER_HPP_
#define COORDINATES_PARSER_HPP_

#include <string>
#include <regex>
#include <iostream>



namespace coordinates {

class OSGrid;

class Parser {
public:
	enum class Kind {
		LatLong,
		Grid,
		Unknown,
		Unparsed
	};
	static const std::string gridAlphabet;

	struct Result {
		Parser::Kind kind;
		double E, N;
		double lat, lon;

		Result() : kind(Kind::Unknown) , E(), N(), lat(), lon() {};
		Result(Parser::Kind kind_,double first,double second) : kind(kind_), E(), N(), lat(), lon() {
			switch(kind) {
			case Kind::LatLong:
				lat=first;
				lon=second;
				break;
			case Kind::Grid:
				E=first;
				N=second;
				break;
			default:
				break;
			}
		}
		Result(Parser::Kind kind,std::pair<double,double> p) : Result(kind,p.first,p.second) {};
	};

private:
	std::string text;
	Result parameters;

	std::smatch m;

	static const std::regex lonlatNSEW;
	static const std::regex lonlatPM;
	static const std::regex gridOS1;
	static const std::regex gridOS2;


	Result isLatLong();
	Result isGrid();
	Result completeGrid(const std::string & e,const std::string & n);

public:

	Parser(const std::string & line) : text(line), parameters(), m() {};
	virtual ~Parser() = default;
	
	Kind parse();
	Result & operator()() { return parameters; }

	static std::string toString(const OSGrid &g);

	
};





} /* namespace coordinates */

#endif /* COORDINATES_PARSER_HPP_ */
