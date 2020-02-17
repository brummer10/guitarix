import numpy as np
cimport numpy as np

cdef extern from "gx_compiler.h":
    pass

cdef extern from "ts9nonlin.h":
    double ts9nonlin(double x)
    extern float x0ts9 "ts9table.low"
    extern float hts9 "ts9table.istep"
    extern int nts9 "ts9table.size"

def ts9func(x):
    return ts9nonlin(x)

ts9func_range = [(x0ts9, hts9, nts9)]
