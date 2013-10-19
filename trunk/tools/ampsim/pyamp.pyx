import numpy as np
cimport numpy as np
np.import_array()
from libc.string cimport const_char

cdef extern from "intpp.h":
    ctypedef float real
    struct splinecoeffs:
        real *x0
        real *xe
        real *stepi
        int *n
        int *nmap
        int **map
        real **t
        real **c
        int (*eval)(splinecoeffs *p, real *x, real *res)
    struct splinedata:
        splinecoeffs *sc
        int m
        int n_input
        int n_output
        int n_state
        const_char *func_id
    union retval "splinedata::retval":
        char c[4]
        int i

cdef extern from "data.h":
    splinedata ps_jcm800_sd "AmpData::ps_jcm800::sd"
    splinedata ppg_jcm800_sd "AmpData::ppg_jcm800::sd"
    splinedata ppp_jcm800_sd "AmpData::ppp_jcm800::sd"
    splinedata ct_sd "AmpData::ct::sd"

cdef rangeerror(int rv, real *Uin, splinedata *p, int n, int k):
    cdef retval cl
    cl.i = rv
    l = []
    for i in range(k):
        if not cl.c[i]:
            continue
        l.append("%g not in range [%g .. %g] (parameter %d)"
                 % (Uin[i], p.sc[n].x0[i], p.sc[n].xe[i], i+1))
    raise LookupError("%s/%d: %s" % (<char*>(p.func_id), n, " / ".join(l)))

def phasesplitter(Uin):
    assert len(Uin) == 4
    cdef real Uout[5]
    cdef real t[3]
    cdef int i
    t[0] = Uin[0] - Uin[1]
    t[1] = Uin[2]
    t[2] = Uin[3]
    cdef splinecoeffs *p
    cdef int rv
    for i in range(5):
        p = &ps_jcm800_sd.sc[i]
        rv = p.eval(p, t, &Uout[i])
        if rv != 0:
            rangeerror(rv, t, &ps_jcm800_sd, i, 4)
    for i in range(3):
        Uout[i+2] += Uin[i+1]
    return [v for v in Uout]

def pushpullgate(Uin):
    assert len(Uin) == 2
    cdef real Uout[2]
    cdef real t[2]
    cdef int i
    t[0] = Uin[0] - (Uin[1] - 311.045)
    cdef splinecoeffs *p
    cdef int rv
    for i in range(2):
        p = &ppg_jcm800_sd.sc[i]
        rv = p.eval(p, t, &Uout[i])
        if rv != 0:
            rangeerror(rv, t, &ppg_jcm800_sd, i, 1)
    Uout[1] += Uin[1] - 311.045
    return [v for v in Uout]

def pushpullplate(Uin):
    assert len(Uin) == 3
    cdef real Uout[2]
    cdef real t[3]
    cdef int i
    for i in range(3):
        t[i] = Uin[i]
    cdef splinecoeffs *p
    cdef int rv
    for i in range(2):
        p = &ppp_jcm800_sd.sc[i]
        rv = p.eval(p, t, &Uout[i])
        if rv != 0:
            rangeerror(rv, t, &ppp_jcm800_sd, i, 3)
    Uout[1] += t[2]
    return [v for v in Uout]

def coupledtriode(Uin):
    assert len(Uin) == 3
    cdef real Uout[3]
    cdef real t[3]
    cdef int i
    for i in range(3):
        t[i] = Uin[i]
    t[0] -= t[1]
    cdef splinecoeffs *p
    cdef int rv
    p = &ct_sd.sc[0]
    rv = p.eval(p, t, &Uout[0])
    if rv != 0:
        rangeerror(rv, t, &ct_sd, 0, 3)
    p = &ct_sd.sc[1]
    rv = p.eval(p, t, &Uout[1])
    if rv != 0:
        rangeerror(rv, t, &ct_sd, 1, 3)
    p = &ct_sd.sc[2]
    rv = p.eval(p, t, &Uout[2])
    if rv != 0:
        rangeerror(rv, t, &ct_sd, 2, 3)
    Uout[1] += t[1]
    Uout[2] += t[2]
    return [v for v in Uout]
