/*
 * Vector.hpp
 *
 *  Created on: 2 Nov 2017
 *      Author: julianporter
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <vector>
#include <initializer_list>

namespace util {

class Vector {
public:
	using vec_t = std::vector<double>;
	using  iterator = vec_t::iterator;
	using  const_iterator = vec_t::const_iterator;
private:
	std::vector<double> v;
public:
	Vector(const int &n) : v(n,0.0) {};
	Vector(std::initializer_list<double> values) : v(values) {};
	Vector(const std::vector<double> &vv) : v(vv) {};
	Vector(std::vector<double> &&vv) : v(vv) {};
	Vector(const Vector &o) : v(o.v) {};
	Vector(Vector &&o) : v(std::move(o.v)) {};
	virtual ~Vector() = default;

	Vector & operator=(const Vector &);
	Vector & operator=(Vector &&);

	iterator begin() { return v.begin(); }
	iterator end() { return v.end(); }
	const_iterator cbegin() const { return v.cbegin(); }
	const_iterator cend() const { return v.cend(); }

	int size() const { return v.size(); };
	double norm() const;
	double normSquared() const;
	double & operator[](int n) { return v[n]; }
	double operator()(int n) const { return v[n]; }



};

Vector operator+(const Vector &l,const Vector &r);
Vector operator*(const Vector &l,const double s);
Vector operator*(const double s,const Vector &l);
Vector operator-(const Vector &l,const Vector &r);
Vector operator-(const Vector &l);
double operator|(const Vector &l,const Vector &r);
bool operator==(const Vector &l,const Vector &r);
bool operator!=(const Vector &l,const Vector &r);


} /* namespace util */

#endif /* VECTOR_HPP_ */
