/*
 * Helmert.hpp
 *
 *  Created on: 30 Jul 2017
 *      Author: julianporter
 */

#ifndef HELMERT_HPP_
#define HELMERT_HPP_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

using Vector = boost::numeric::ublas::vector<double>;
using Zero   = boost::numeric::ublas::zero_vector<double>;
using Matrix = boost::numeric::ublas::matrix<double>;
using ID     = boost::numeric::ublas::identity_matrix<double>;


namespace mapping {

class HelmertMatrix {
friend Vector operator*(const HelmertMatrix &h,const Vector &v);
private:
	Vector r;
	double s;
	Matrix mx;	
	
	double determinant(); 
	static Matrix rsMatrix(const Vector & r,const double s);
	
public:
	
	HelmertMatrix() : r(Zero(3)), s(1.0), mx(ID(3)) {};
	HelmertMatrix(Vector & R, const double S) : r(R), s(1.0+S), mx(HelmertMatrix::rsMatrix(r,s)) {}; 
	HelmertMatrix(const Matrix & m) : r(Zero(3)), s(1.0), mx(m) {};
	HelmertMatrix(const HelmertMatrix &other) : r(other.r), s(other.s), mx(other.mx) {};
	HelmertMatrix & operator=(const HelmertMatrix &other);
	virtual ~HelmertMatrix() = default;
	
	HelmertMatrix inverse();
	
};
Vector operator*(const HelmertMatrix &h,const Vector &v);


class Helmert {
public:
	Helmert();
	virtual ~Helmert();
};

} /* namespace mapping */

#endif /* HELMERT_HPP_ */
