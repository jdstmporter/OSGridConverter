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


/**
 * \class coordinates::Parser
 * \brief Parses string representations of co-ordinates into appropriate objects
 *
 * Takes a string representation of co-ordinates and converts it to the appropriate coordinate
 * object.  Valid formats are:
 * Format                                   |  Parsed as                     | Description
 * -----------------------------------------|--------------------------------|------------
 * (+/-) nnn.nnnn[N/S], (+/-) eee.eeee[E/W] | coordinates::LatitudeLongitude | expressed in degrees North/South and East/West
 * (+/-) nnn.nnnn, (+/-) eee.eeee           | coordinates::LatitudeLongitude | expressed in degrees North and East
 * LL nnnnnn eeeeee                         | coordinates::OSGrid            | Ordnance Survey map grid reference where LL is thre alphabetic grid square, nnnnnn is northings and eeeeee is eastings
 */
namespace coordinates {

class OSGrid;

class Parser {
public:
	/**
	 * Result of the parse
	 */
	enum class Kind {
		LatLong,	/*!< represents coordinates::LatitudeLongitude*/
		Grid,		/*!< represents coordinates::OSGrid*/
		Unknown,	/*!< not recognised */
		Unparsed    /*!< not yet parsed */
	};
	/**
	 * The alphabet used in OSGrid grid squares
	 *
	 * Ordinance Survey grid square names are made up of two characters from the alphabet
	 * "ABCDEFGHJKLMNOPQRSTUVWXYZ".
	 */
	static const std::string gridAlphabet;

	/**
	 * \struct coordinates::Parser::Result
	 * \brief Results from parsing a string
	 */
	struct Result {
		Parser::Kind kind;	/*!< the identified kind of the string */
		double E;		/*!< easting value if it's a grid reference */
		double N;		/*!< northing value if it's a grid reference */
		double lat;		/*!< latitude value if it's latitude / longitude */
		double lon;		/*!< longitude value if it's latitude / longitude */

		Result() : kind(Kind::Unknown) , E(), N(), lat(), lon() {};
		/**
		 * Initialise with given values
		 *
		 * Initialise depending on \a kind
		 * \param kind the Kind of the result
		 * \param first easting if \a kind is Kind::Grid, latitude if it is Kind::LatLong
		 * \param second northing if \a kind is Kind::Grid, longitude if it is Kind::LatLong
		 */
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
		/**
		 * Initialise from a pair
		 *
		 * The same as Result(kind,p.first,p.second)
		 * \param kind the Kind of the result
		 * \param p the values
		 */
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
