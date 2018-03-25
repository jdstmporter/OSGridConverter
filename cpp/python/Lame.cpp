/*
 * Lame.c
 *
 *  Created on: 1 Dec 2017
 *      Author: julianporter
 */

#include "PyHeader.hpp"
#include "PyGridPoint.hpp"
#include "PyLatLongPoint.hpp"

static const char *ModuleName="geoconv";

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        ModuleName,
        NULL,
        -1,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
};

PyMODINIT_FUNC PyInit_geoconv(void)
{

    PyObject *m = PyModule_Create(&moduledef);
    if (!m) return NULL;



    PyGridPoint p;
    //inotify_WatcherType.tp_new = PyType_GenericNew;
    if (!p.isReady()) return NULL;
    p.inc();
    p.add(m,"GridPoint");

    PyLatLongPoint l;
    //inotify_WatcherType.tp_new = PyType_GenericNew;
    if (!l.isReady()) return NULL;
    l.inc();
    l.add(m,"LatLongPoint");


    return m;
}



