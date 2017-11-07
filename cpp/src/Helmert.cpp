/*
 * Helmert.cpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#include "Helmert.hpp"
#include <stdexcept>
#include <algorithm>
#include <utility>



namespace mapping {





Helmert & Helmert::operator=(const Helmert &o) {
	scale=o.scale;
	translation=o.translation;
	rotation=o.rotation;
	return *this;
}

Helmert & Helmert::operator=(Helmert &&o) {
	scale=o.scale;
	std::swap(translation,o.translation);
	std::swap(rotation,o.rotation);
	return *this;
}


util::Matrix Helmert::matrix() const {
	util::Matrix m(3);
	for(auto i=0;i<3;i++) {
		m(i,i)=1+scale;
		auto j=(i+1)%3;
		auto k=(i+2)%3;
		m(j,k)=-rotation(i);
		m(k,j)= rotation(i);
	}
	return m;
}

Helmert Helmert::inverse() const {
	return std::move(Helmert(-translation,-rotation,scale));
}

util::Vector Helmert::operator()(const util::Vector &x) const {
	return util::prod(matrix(),x)+translation;
}
//util::Vector Helmert::operator()(util::Vector &&x) const {
//	return util::prod(mx,x)+t;
//}





bool operator==(const Helmert &l,const Helmert &r) {
	return (l.scale==r.scale) && (l.translation==r.translation) && (l.rotation==r.rotation);
}
bool operator!=(const Helmert &l,const Helmert &r){
	return (l.scale!=r.scale) || (l.translation!=r.translation) || (l.rotation!=r.rotation);
}

} /* namespace mapping */


  
