#include <pygobject.h>
#define PY_ARRAY_UNIQUE_SYMBOL gxwidgets_ARRAY_API
#include <numpy/arrayobject.h>

void gxwidgets_register_classes(PyObject *d);
extern PyMethodDef gxwidgets_functions[];

DL_EXPORT(void) initgxwidgets(void)
{
	PyObject *m, *d;

	init_pygobject ();
	import_array();

	m = Py_InitModule ("gxwidgets", gxwidgets_functions);
	d = PyModule_GetDict (m);

	gxwidgets_register_classes(d);
	/*gxwidgets_add_constants(m, ""); no constants atm */

	if (PyErr_Occurred ()) {
		Py_FatalError ("can't initialise module hello_widget");
	}
}
