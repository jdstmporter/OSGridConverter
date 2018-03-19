/*
 * algebra.cpp
 *
 *  Created on: 18 Mar 2018
 *      Author: julianporter
 */

#include "algebra.hpp"

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

Matrix transpose(const Matrix &m) {
	return trans(m);
}

}


