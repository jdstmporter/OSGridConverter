/*
 * PyLatLongPoint.hpp
 *
 *  Created on: 25 Mar 2018
 *      Author: julianporter
 */

#ifndef CPP_PYTHON_PYLATLONGPOINT_HPP_
#define CPP_PYTHON_PYLATLONGPOINT_HPP_

#include "PyHeader.hpp"
#include "../include/osgridconv.hpp"

typedef struct  {
	PyObject_HEAD
	coordinates::LatitudeLongitude *lat;
} LatLongPoint;

PyObject *LatLongPoint_new(PyTypeObject *type,PyObject *args,PyObject *keywords);
void LatLongPoint_dealloc(LatLongPoint *self);
int LatLongPoint_init(LatLongPoint *self,PyObject *args,PyObject *keywords);
PyObject * LatLongPoint_toGrid(LatLongPoint *self,PyObject *args);
PyObject * LatLongPoint_LatLong(LatLongPoint *self,PyObject *args);

class PyLatLongPoint {
public:
	PyLatLongPoint() {};
	virtual ~PyLatLongPoint() = default;

	 bool isReady();
	 void inc();
	 void add(PyObject *m,const char *name);
	 static LatLongPoint * make(const coordinates::OSGrid *grid);

};



#endif /* CPP_PYTHON_PYLATLONGPOINT_HPP_ */
