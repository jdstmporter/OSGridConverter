/*
 * PyLatLongPoint.cpp
 *
 *  Created on: 25 Mar 2018
 *      Author: julianporter
 */

#include "PyLatLongPoint.hpp"
#include "PyGridPoint.hpp"

 PyObject * LatLongPoint_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{   auto self = (LatLongPoint *)type->tp_alloc(type, 0);
    if(self!=NULL) self->lat=NULL;
    return (PyObject *)self;
}


 void LatLongPoint_dealloc(LatLongPoint *self) {
	if(self->lat) delete self->lat;
	auto p=(PyObject *)self;
	p->ob_type->tp_free(p);
}




 int LatLongPoint_init(LatLongPoint *self, PyObject *args, PyObject *kwds)
{
	double lat=0.0,lon=0.0;
	if(PyArg_ParseTuple(args,"dd",&lon,&lat)) {
		self->lat=new coordinates::LatitudeLongitude(lon,lat);
		return 0;
	}
	PyErr_SetString(PyExc_SystemError,"Parameter must be double, double");
	return -1;
}



 PyObject * LatLongPoint_LatLong(PyObject *self,PyObject *args) {
	try {
		auto s=(LatLongPoint *)self;
		return Py_BuildValue("(dd)",s->lat->Longitude(),s->lat->Latitude());
	}
	catch(...) {
		return PException(PyExc_OSError,"Bad value")();
	}
}

 PyObject * LatLongPoint_toGrid(PyObject *self,PyObject *args) {
	try {
		auto s=(LatLongPoint *)self;
		return (PyObject *)PyGridPoint::make(s->lat);
	}
	catch(...) {
		return PException(PyExc_OSError,"Bad value")();
	}
}

static PyMethodDef LatLongPointMethods[] = {
    {"toLatLong",  LatLongPoint_toGrid, METH_VARARGS,"Convert to latitude / longitude"},
	{"coordinates", LatLongPoint_LatLong, METH_VARARGS, "Get easting / northing"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

const char *latlongPointName="geoconv.LatLongPoint";
 const char *latlongPointDocstr="Representation of Lat/Long Point";


 PyTypeObject geoconv_LatLongPointType = {
 	PyVarObject_HEAD_INIT(NULL,0)
     (char *)latlongPointName,             		/*tp_name*/
     sizeof(LatLongPoint), 			/*tp_basicsize*/
     0,                         	/*tp_itemsize*/
     (destructor)LatLongPoint_dealloc,		/*tp_dealloc*/
     0,                         			/*tp_print*/
 	0,                         			/*tp_getattr*/
 	0,                         			/*tp_setattr*/
 	0,                         			/*tp_compare*/
 	0,                         			/*tp_repr*/
 	0,                         			/*tp_as_number*/
 	0,                  /*tp_as_sequence*/
 	0,                         			/*tp_as_mapping*/
 	0,                         			/*tp_hash */
 	0,                         			/*tp_call*/
 	0,                         			/*tp_str*/
 	0,                         			/*tp_getattro*/
 	0,                         			/*tp_setattro*/
 	0,                         			/*tp_as_buffer*/
 	Py_TPFLAGS_DEFAULT, 				/*tp_flags*/
	latlongPointDocstr,								/* tp_doc */
 	0,   								/* tp_traverse */
 	0,           						/* tp_clear */
 	0,		               				/* tp_richcompare */
 	0,		               				/* tp_weaklistoffset */
 	0,		               				/* tp_iter */
 	0,		               				/* tp_iternext */

	LatLongPointMethods,             		/* tp_methods */
 	0,             		/* tp_members */
 	0,                         			/* tp_getset */
 	0,                         			/* tp_base */
 	0,                         			/* tp_dict */
 	0,                         			/* tp_descr_get */
 	0,                         			/* tp_descr_set */
 	0,                         			/* tp_dictoffset */
 	(initproc)LatLongPoint_init,      		/* tp_init */
 	0,                         			/* tp_alloc */
 	(newfunc)LatLongPoint_new,                 		/* tp_new */
 };

 bool PyLatLongPoint::isReady() { return PyType_Ready(&geoconv_LatLongPointType)>=0; }
  void PyLatLongPoint::inc() { Py_INCREF(&geoconv_LatLongPointType); }
  void PyLatLongPoint::add(PyObject *m,const char *name) {
  	PyModule_AddObject(m,name,(PyObject *)&geoconv_LatLongPointType);
  }
  LatLongPoint * PyLatLongPoint::make(const coordinates::OSGrid *grid) {
  	auto l=(LatLongPoint *)_PyObject_New(&geoconv_LatLongPointType);
  	l->lat=new coordinates::LatitudeLongitude(*grid);
  	return l;
  }


