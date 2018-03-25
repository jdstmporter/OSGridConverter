/*
 * PyGridPoint.cpp
 *
 *  Created on: 25 Mar 2018
 *      Author: julianporter
 */

#include "PyGridPoint.hpp"
#include "PyLatLongPoint.hpp"

 PyObject * GridPoint_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    auto *self = (GridPoint *)type->tp_alloc(type, 0);
    if(self!=NULL) self->grid=NULL;
    return (PyObject *)self;
}

 void GridPoint_dealloc(GridPoint *self) {
	if(self->grid) delete self->grid;
	auto p=(PyObject *)self;
	p->ob_type->tp_free(p);
}

 int GridPoint_init(GridPoint *self, PyObject *args, PyObject *kwds)
{
	const char *c=nullptr;
	long e=0,n=0;
	if (PyArg_ParseTuple(args,"z",c)) {
		if(c!=nullptr) {
			std::string s(c);
			self->grid=new coordinates::OSGrid(s);
			return 0;
		}
		else {
			PyErr_SetString(PyExc_SystemError,"Null string parameter provided");
			return -1;
		}
		PyErr_Clear();
	}
	else if(PyArg_ParseTuple(args,"ll",&e,&n)) {
		self->grid=new coordinates::OSGrid(n,e);
		return 0;
	}
	else {
		PyErr_SetString(PyExc_SystemError,"Parameter must be string or long, long");
		return -1;
	}
}

 PyObject * GridPoint_EN(PyObject *self,PyObject *args) {
	try {
		auto s=(GridPoint *)self;
		return Py_BuildValue("(ll)",s->grid->E(),s->grid->N());
	}
	catch(...) {
		return PException(PyExc_OSError,"Bad value")();
	}
}

 PyObject * GridPoint_OSGridReference(PyObject *self,PyObject *args) {
	try {
		auto s=(GridPoint *)self;
		return PyUnicode_FromFormat("%s",s->grid->tag().c_str());
	}
	catch(...) {
		return PException(PyExc_OSError,"Bad value")();
	}
}

 PyObject * GridPoint_toLatLong(PyObject *self,PyObject *args) {
	try {
		auto s=(GridPoint *)self;
		return (PyObject *)PyLatLongPoint::make(s->grid);
	}
	catch(...) {
		return PException(PyExc_OSError,"Bad value")();
	}
}

static PyMethodDef GridPointMethods[] = {
    {"toLatLong",  GridPoint_toLatLong, METH_VARARGS,"Convert to latitude / longitude"},
	{"coordinates", GridPoint_EN, METH_VARARGS, "Get easting / northing"},
	{"OSgridRef", GridPoint_OSGridReference,METH_VARARGS,"Get OS Grid Reference"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

const char *gridPointName="geoconv.GridPoint";
 const char *gridPointDocstr="Representation of Grid Point";


 PyTypeObject geoconv_GridPointType = {
 	PyVarObject_HEAD_INIT(NULL,0)
     (char *)gridPointName,             		/*tp_name*/
     sizeof(GridPoint), 			/*tp_basicsize*/
     0,                         	/*tp_itemsize*/
     (destructor)GridPoint_dealloc,		/*tp_dealloc*/
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
 	gridPointDocstr,								/* tp_doc */
 	0,   								/* tp_traverse */
 	0,           						/* tp_clear */
 	0,		               				/* tp_richcompare */
 	0,		               				/* tp_weaklistoffset */
 	0,		               				/* tp_iter */
 	0,		               				/* tp_iternext */

	GridPointMethods,             		/* tp_methods */
 	0,             		/* tp_members */
 	0,                         			/* tp_getset */
 	0,                         			/* tp_base */
 	0,                         			/* tp_dict */
 	0,                         			/* tp_descr_get */
 	0,                         			/* tp_descr_set */
 	0,                         			/* tp_dictoffset */
 	(initproc)GridPoint_init,      		/* tp_init */
 	0,                         			/* tp_alloc */
 	(newfunc)GridPoint_new,                 		/* tp_new */
 };

 bool PyGridPoint::isReady() { return PyType_Ready(&geoconv_GridPointType)>=0; }
  void PyGridPoint::inc() { Py_INCREF(&geoconv_GridPointType); }
  void PyGridPoint::add(PyObject *m,const char *name) {
  	PyModule_AddObject(m,name,(PyObject *)&geoconv_GridPointType);
  }
  GridPoint * PyGridPoint::make(const coordinates::LatitudeLongitude *lat) {
  	auto g=(GridPoint *)_PyObject_New(&geoconv_GridPointType);
  	g->grid=new coordinates::OSGrid(*lat);
  	return g;
  }

