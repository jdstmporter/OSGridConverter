/*
 * Generator.hpp
 *
 *  Created on: 31 Oct 2017
 *      Author: julianporter
 */

#ifndef SRC_TESTS_GENERATOR_HPP_
#define SRC_TESTS_GENERATOR_HPP_

#include <random>
#include <string>
#include <geoconv.hpp>
#include <chrono>

namespace test {

class Generator {
private:
	using Tag=mapping::Datum::Name;
	int n;
	std::mt19937 source;
	std::uniform_real_distribution<double> uniform;

	static unsigned seed() noexcept;

protected:
	double random(const double lo,const double hi) noexcept;
public:
	Generator(const int n_=3) : n(n_), source(Generator::seed()), uniform(0,1) {};

	coordinates::LatitudeLongitude latLong(const Tag & tag = Tag::WGS84) noexcept;
	coordinates::OSGrid grid(const Tag & tag = Tag::WGS84) noexcept;

	util::Vector vector() noexcept;
	void reset();
		
};

double gridDiff(const coordinates::OSGrid &g1,const coordinates::OSGrid &g2);
double logGridDiff(const coordinates::OSGrid &g1,const coordinates::OSGrid &g2);
double latLongDiff(const coordinates::LatitudeLongitude &l1,const coordinates::LatitudeLongitude &l2);

std::string gridString(const coordinates::OSGrid &g);

} /* namespace test */

#endif /* SRC_TESTS_GENERATOR_HPP_ */
