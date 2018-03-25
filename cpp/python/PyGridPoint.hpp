/*
 * PyGridPoint.hpp
 *
 *  Created on: 25 Mar 2018
 *      Author: julianporter
 */

#ifndef CPP_PYTHON_PYGRIDPOINT_HPP_
#define CPP_PYTHON_PYGRIDPOINT_HPP_
#include "PyHeader.hpp"
#include "../include/osgridconv.hpp"

typedef struct  {
	PyObject_HEAD
	coordinates::OSGrid *grid;
} GridPoint;

PyObject *GridPoint_new(PyTypeObject *type,PyObject *args,PyObject *keywords);
void GridPoint_dealloc(GridPoint *self);
int GridPoint_init(GridPoint *self,PyObject *args,PyObject *keywords);
PyObject * GridPoint_toLatLong(GridPoint *self,PyObject *args);
PyObject * GridPoint_EN(GridPoint *self,PyObject *args);
PyObject * GridPoint_OSGridReference(GridPoint *self,PyObject *args);

class PyGridPoint {
public:
	PyGridPoint() {};
	virtual ~PyGridPoint() = default;

	 bool isReady();
	 void inc();
	 void add(PyObject *m,const char *name);
	 static GridPoint * make(const coordinates::LatitudeLongitude *lat);

};

#endif /* CPP_PYTHON_PYGRIDPOINT_HPP_ */
