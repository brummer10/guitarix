#include <pygobject.h>
#include <gxw/gxinit.h>
#define PY_ARRAY_UNIQUE_SYMBOL gxw_ARRAY_API
#include <numpy/arrayobject.h>

void gxw_register_classes(PyObject *d);
extern PyMethodDef gxw_functions[];

DL_EXPORT(void) initgxw(void)
{
	PyObject *m, *d;

	gxw_init();
	init_pygobject ();
	import_array();

	m = Py_InitModule ("gxw", gxw_functions);
	d = PyModule_GetDict (m);

	gxw_register_classes(d);
	gxw_add_constants(m, "");

	if (PyErr_Occurred ()) {
		Py_FatalError ("can't initialise module gxw");
	}
}
