/*
 * Lame.c
 *
 *  Created on: 1 Dec 2017
 *      Author: julianporter
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <exception>
#include <tuple>
#include <sstream>
#include <regex>
#include <iostream>
#include <cmath>
#include "../include/osgridconv.hpp"


static PyObject *GeoError;



class PException : public std::exception {
private:
	PyObject *ex;
	std::string message;
public:
	PException(PyObject *type,const std::string &message_) : std::exception(), ex(type), message(message_) {};
	virtual ~PException() = default;

	virtual const char *what() const noexcept { return message.c_str(); };
	PyObject *operator()() {
		PyErr_SetString(ex,what());
		return nullptr;
	}
};


typedef struct  {
	PyObject_HEAD
	coordinates::OSGrid grid;
} PointEN;

typedef struct  {
	PyObject_HEAD
	coordinates::LatitudeLongitude lat;
} PointLL;



static PyObject * PointEN_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PointEN *self;

    self = (PointEN *)type->tp_alloc(type, 0);
    self->grid=coordinates::OSGrid(0,0);
    return (PyObject *)self;
}

static PyObject * PointLL_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PointLL *self;

    self = (PointLL *)type->tp_alloc(type, 0);
    self->lat=coordinates::LatitudeLongitude(0,0);
    return (PyObject *)self;
}

static void PointEN_dealloc(PointEN *self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

static void PointLL_dealloc(PointLL *self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}


static int PointEN_init(PointEN *self, PyObject *args, PyObject *kwds)
{
	const char *c=nullptr;
	if (PyArg_ParseTuple(args,"z",c)) {
		if(c!=nullptr) {
			std::string s(c);
			self->grid=coordinates::OSGrid(s);
			return 0;
		}
		PyErr_SetString(PyExc_SystemError,"Null string parameter provided");
		return -1;
	}
	PyErr_Clear();
	long e=0,n=0;
	if(PyArg_ParseTuple(args,"ll",&e,&n)) {
		self->grid=coordinates::OSGrid(n,e);
		return 0;
	}
	PyErr_SetString(PyExc_SystemError,"Parameter must be string or long, long");
	return -1;
}

static int PointLL_init(PointLL *self, PyObject *args, PyObject *kwds)
{
	double lat=0.0,lon=0.0;
	if(PyArg_ParseTuple(args,"dd",&lon,&lat)) {
		self->lat=coordinates::LatitudeLongitude(lon,lat);
		return 0;
	}
	PyErr_SetString(PyExc_SystemError,"Parameter must be double, double");
	return -1;
}

static PyObject * getEastingNorthing(PointEN *self,void *closure) {
	try {
		return Py_BuildValue("(ll)",self->grid.E(),self->grid.N());
	}
	catch(...) {
		return PException(GeoError,"Bad value")();
	}
}

static PyObject * getGrid(PointEN *self,void *closure) {
	try {
		return PyUnicode_FromFormat("%s",self->grid.tag().c_str());
	}
	catch(...) {
		return PException(GeoError,"Bad value")();
	}
}





static PyObject * getLongitudeLatitude(PointLL *self,void *closure) {
	try {
		return Py_BuildValue("(dd)",self->lat.Longitude(),self->lat.Latitude());
	}
	catch(...) {
		return PException(GeoError,"Bad value")();
	}
}

static PyObject * toEN(PointLL *self,void *closure);
static PyObject * toLongitudeLatitude(PointEN *self,void *closure);

static PyGetSetDef PointEN_properties[] = {
    {"EN", (getter)getEastingNorthing, NULL, "Return the (easting,northing) pair of the point"},
	{"LongLat", (getter)toLongitudeLatitude, NULL, "Return the (longitude,latitude) of the point"},
	{"Grid", (getter)getGrid, NULL, "Return the OS Grid Reference of the point"},
    {NULL}  /* Sentinel */
};

static PyGetSetDef PointLL_properties[] = {
    {"EN", (getter)toEN, NULL, "Return the (easting,northing) pair of the point"},
	{"LongLat", (getter)getLongitudeLatitude, NULL, "Return the (longitude,latitude) of the point"},
    {NULL}  /* Sentinel */
};




static PyTypeObject PointENType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "geoconv.PointEN",             /* tp_name */
    sizeof(PointEN),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)PointEN_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
	0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
	0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Object representing a point on the Earth's surface",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
	0,             /* tp_methods */
    0,             /* tp_members */
	PointEN_properties,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PointEN_init,      /* tp_init */
    0,                         /* tp_alloc */
    PointEN_new,                 /* tp_new */
};


static PyTypeObject PointLLType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "geoconv.PointLL",             /* tp_name */
    sizeof(PointLL),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)PointLL_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
	0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
	0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Object representing a point on the Earth's surface",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
	0,             /* tp_methods */
    0,             /* tp_members */
	PointLL_properties,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PointLL_init,      /* tp_init */
    0,                         /* tp_alloc */
    PointLL_new,                 /* tp_new */
};


static PyObject * toEN(PointLL *self,void *closure) {
	try {
		PointEN *out=PyObject_New(PointEN,&PointENType);
		out->grid=coordinates::OSGrid(self->lat);
		return (PyObject *)out;
	}
	catch(...) {
		return PException(GeoError,"Bad value")();
	}
}

static PyObject * toLongitudeLatitude(PointEN *self,void *closure) {
	try {
		;
		PointLL *out=PyObject_New(PointLL,&PointLLType);
		out->lat=coordinates::LatitudeLongitude(self->grid);
		return (PyObject *)out;
	}
	catch(...) {
		return PException(GeoError,"Bad value")();
	}
}



static struct PyModuleDef module = {
		PyModuleDef_HEAD_INIT,
		"geoconv",
		"Conversion between longitude/latitude and OS map grid",			/// Documentation string
		-1,			/// Size of state (-1 if in globals)
		NULL,
		NULL,		/// Slots
		NULL,		/// traverse
		NULL,		/// clear
		NULL		/// free
};

void attach(PyObject *module,PyObject *type,const std::string &name) {
	std::cerr << "Attaching object " << name << std::endl;
	Py_INCREF(type);
	auto result=PyModule_AddObject(module,name.c_str(),type);
	std::cerr << "Result was " << result << std::endl;
	if(result<0) throw std::runtime_error("Cannot attach");
}

PyMODINIT_FUNC PyInit_geoconv(void) {

	std::cerr << "Starting " << std::endl;
	if(PyType_Ready(&PointENType)<0) return NULL;
	if(PyType_Ready(&PointLLType)<0) return NULL;
	std::cerr << "Making module" << std::endl;
	PyObject *m = PyModule_Create(&module);
	if(m==NULL) return NULL;
	try {
		attach(m,(PyObject *)&PointENType,"PointEN");
		attach(m,(PyObject *)&PointLLType,"PointLL");

		std::cerr << "Creating error" << std::endl;
		GeoError=PyErr_NewException("geoconv.Error",NULL,NULL);
		if(GeoError==nullptr) throw std::runtime_error("Cannot allocate Error");
		attach(m,GeoError,"Error");
		return m;
	}
	catch(std::exception &e) {
		PyErr_SetString(PyExc_ImportError,e.what());
		return NULL;
	}
}



