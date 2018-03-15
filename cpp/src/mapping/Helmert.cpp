/*
 * Helmert.cpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#include "Helmert.hpp"
#include <stdexcept>
#include <algorithm>
#include <functional>
#include "ApproximateHelmert.hpp"
#include "ExactHelmert.hpp"

using namespace boost::numeric::ublas;

namespace mapping {

bool operator==(const Vector &l,const Vector &r) {
	return std::equal(l.begin(),l.end(),r.begin());
}
bool operator!=(const Vector &l,const Vector &r) {
	return !std::equal(l.begin(),l.end(),r.begin());
}

bool operator==(const Matrix &l,const Matrix &r) {
	return std::equal(l.begin1(),l.end1(),r.begin1());
}
bool operator!=(const Matrix &l,const Matrix &r) {
	return !std::equal(l.begin1(),l.end1(),r.begin1());
}

bool operator==(const Helmert &l,const Helmert &r) {
	return l.matrix()==r.matrix() && l.offset()==r.offset();
};
bool operator!=(const Helmert &l,const Helmert &r) {
	return l.matrix()!=r.matrix() || l.offset()!=r.offset();
};

Vector Helmert::transform(Vector x) const {
	return prod(matrix(),x)+offset();
}

helmert_t Helmert::inverse() const {
	Vector b=invertedAngles();

	auto t2=-prod(matrix(b,1.0/scale),t);
	return std::move(std::make_shared<Helmert>(b,t2,1.0/scale));
}


helmert_t getHelmertTransform(const HelmertType &type,const Vector &t,const Vector &angles,const double scale) {
	helmert_t h;
	switch(type) {
	case HelmertType::Approximate: {
		auto p=std::make_shared<helmert::ApproximateHelmert>(t,angles,scale);
		h=std::static_pointer_cast<Helmert>(p);
		break;
		}
	case HelmertType::Exact: {
		auto p=new helmert::ExactHelmert(t,angles,scale);
		h=std::shared_ptr<Helmert>(static_cast<Helmert *>(p));
		break;
		}
	}
	return std::move(h);
}












} /* namespace mapping */


  
