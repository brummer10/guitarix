c_template_top = """
#include <cmath>
#include <cminpack.h>
#include <Eigen/Core>

using namespace Eigen;

static int nonlin(Matrix<double, %(nn)d, 1>& i, double *v, int *info, int *nfev, double *fnorm);

static inline int sign(double v) {
    return v < 0 ? -1 : 1;
}

static Matrix<double, %(nx)d, 1> g_x;
static Matrix<double, %(nn)d, 1> g_v;
static double g_fnorm;
static int g_info;
static int g_nfev;

extern "C" void get_info(double *v, double *x, int *info, int *nfev, double *fnorm) {
    Map<Matrix<double, %(nn)d, 1> > V(v);
    V = g_v;
    Map<Matrix<double, %(nx)d, 1> > X(x);
    X = g_x;
    *info = g_info;
    *nfev = g_nfev;
    *fnorm = g_fnorm;
}

extern "C" void set_state(double *v, double *x) {
    Map<Matrix<double, %(nn)d, 1> > V(v);
    g_v = V;
    Map<Matrix<double, %(nx)d, 1> > X(x);
    g_x = X;
}

static double __attribute__((aligned(16))) mx_data[%(nx)d*%(m_cols)d] = { %(mx_data)s };
static const Map<Matrix<double, %(nx)d, %(m_cols)d>, Aligned> Mx(mx_data);
static double __attribute__((aligned(16))) mo_data[%(no)d*%(m_cols)d] = { %(mo_data)s };
static const Map<Matrix<double, %(no)d, %(m_cols)d>, Aligned> Mo(mo_data);
static double __attribute__((aligned(16))) mp_data[%(nn)d*%(mp_cols)d] = { %(mp_data)s };
static const Map<Matrix<double, %(nn)d, %(mp_cols)d>, Aligned> Mp(mp_data);

extern "C" void calc_stream(double *u, double *o, int n) {
    for (int j = 0; j < n; j++) {
        Matrix<double, %(nn)d, 1> i;
#if %(nn)d
        Matrix<double, %(mp_cols)d, 1> dp;
        dp << g_x, Map<Matrix<double,%(ni)d,1> >(u+j*%(ni)d);
        i = Mp * dp;
        nonlin(i, &g_v(0), &g_info, &g_nfev, &g_fnorm);
#endif
        Matrix<double, %(m_cols)d, 1> d;
        d << g_x, Map<Matrix<double,%(ni)d,1> >(u+j*%(ni)d), i;
        g_x = Mx * d;
        Map<Matrix<double, %(no)d, 1> > xo(o+%(no)d*j);
        xo = Mo * d;
    }
}

extern "C" int calc(double *u, double *x, double *v, double *x_new, double *o, int *info, int *nfev, double *fnorm) {
    int ret = 0;
    Matrix<double, %(nn)d, 1> i;
#if %(nn)d
    Matrix<double, %(mp_cols)d, 1> dp;
    dp << Map<Matrix<double,%(nx)d,1> >(x), Map<Matrix<double,%(ni)d,1> >(u);
    i = Mp * dp;
    ret = nonlin(i, v, info, nfev, fnorm);
#else
    *info = 1;
    *nfev = 0;
    *fnorm = 0;
#endif
    Matrix<double, %(m_cols)d, 1> d;
    d << Map<Matrix<double,%(nx)d,1> >(x), Map<Matrix<double,%(ni)d,1> >(u), i;
    Map<Matrix<double, %(nx)d, 1> > xn(x_new);
    xn = Mx * d;
    Map<Matrix<double, %(no)d, 1> > xo(o);
    xo = Mo * d;
    return ret;
}
"""

c_template_hybr = """
static int fcn(void *p_, int n, const double *v, double *fvec, int iflag ) {
    const double *p = static_cast<const double *>(p_);
    /* nonlinear function for root-finding */
    %(fvec)s
    return 0;
}

static int nonlin(Matrix<double, %(nn)d, 1>& i, double *v, int *info, int *nfev, double *fnorm) {
    int j, n, maxfev, ml, mu, mode, nprint, ldfjac, lr;
    double xtol, epsfcn, factor;
    double fvec[%(nn)d], diag[%(nn)d], fjac[%(nn)d*%(nn)d], r[(%(nn)d*(%(nn)d+1))/2], qtf[%(nn)d], wa1[%(nn)d], wa2[%(nn)d], wa3[%(nn)d], wa4[%(nn)d];
    ldfjac = %(nn)d;
    lr = (%(nn)d*(%(nn)d+1))/2;

    ml = %(nn)d-1; /* unbanded jacobian */
    mu = %(nn)d-1; /* unbanded jacobian */

    /* parameter */
    xtol = sqrt(__cminpack_func__(dpmpar)(1));
    maxfev = 2000;
    epsfcn = 0.;
    mode = 2;  /* explicit variable scaling with diag */
    for (j = 0; j < %(nn)d; j++) {
        diag[j] = 1;
    }
    factor = 1.e2;
    nprint = 0;
    /**/

    /* find root */
    *info = __cminpack_func__(hybrd)(fcn, &i(0), %(nn)d, v, fvec, xtol, maxfev, ml, mu, epsfcn,
                                    diag, mode, factor, nprint, nfev,
                                    fjac, ldfjac, r, lr, qtf, wa1, wa2, wa3, wa4);
    *fnorm = __cminpack_func__(enorm)(n, fvec);
    /* "currents" (should optimize: take from last function evaluation) */
    %(i)s
    return *info == 1 ? 0 : -1;
}
"""

c_template_lm = """
static int fcn(void *p_, int m, int n, const double *v, double *fvec, int iflag ) {
    const double *p = static_cast<const double *>(p_);
    /* nonlinear function for root-finding */
    %(fvec)s
    return 0;
}

static int nonlin(Matrix<double, %(nn)d, 1>& i, double *v, int *info, int *nfev, double *fnorm) {
    int j, n, maxfev, mode, nprint, ldfjac, ipvt[%(nn)d];
    double ftol, xtol, gtol, epsfcn, factor;
    double fvec[%(nn)d], diag[%(nn)d], fjac[%(nn)d*%(nn)d], qtf[%(nn)d], wa1[%(nn)d], wa2[%(nn)d], wa3[%(nn)d], wa4[%(nn)d];
    ldfjac = %(nn)d;

    /* parameter */
    ftol = sqrt(__cminpack_func__(dpmpar)(1));
    xtol = sqrt(__cminpack_func__(dpmpar)(1));
    gtol = 0.;
    maxfev = 2000;
    epsfcn = 0.;
    mode = 2;  /* explicit variable scaling with diag */
    for (j = 0; j < %(nn)d; j++) {
        diag[j] = 1;
    }
    factor = 1.e2;
    nprint = 0;
    /**/

    /* find root */
    *info = __cminpack_func__(lmdif)(fcn, &i(0), %(nn)d, %(nn)d, v, fvec, ftol, xtol, gtol, maxfev, epsfcn, 
                                    diag, mode, factor, nprint, nfev, fjac, ldfjac, 
                                    ipvt, qtf, wa1, wa2, wa3, wa4);
    *fnorm = __cminpack_func__(enorm)(n, fvec);
    /* "currents" (should optimize: take from last function evaluation) */
    %(i)s
    return (*info < 1 || *info > 4) ? -1 : 0;
}
"""

if 0:
    h_template = """
#ifndef AUTOWRAP__WRAPPED_CODE_0__H
#define AUTOWRAP__WRAPPED_CODE_0__H

int calc(const double *u, const double *x, double *v, double *x_new, double *o);

#endif
    """

    pyx_template = """
cdef extern from "dk_code.h":
    int calc(double *u, double *x, double *v, double *x_new, double *o)

def calc_c(u_, x_, v_):
    cdef double u[%(ni)d]
    cdef double x[%(nx)d]
    cdef double v[%(nn)d]
    cdef double x_new[%(nx)d]
    cdef double o[%(no)d]
    cdef int i
    for i in range(%(ni)d):
        u[i] = u_[i]
    for i in range(%(nx)d):
        x[i] = x_[i]
    for i in range(%(nn)d):
        v[i] = v_[i]
    i = calc(u, x, v, x_new, o)
    if i != 1:
        pass #raise ValueError("convergence")
    return [o[i] for i in range(%(no)d)], [x_new[i] for i in range(%(nx)d)], [v[i] for i in range(%(nn)d)]
    """

    setup_template = """
from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
import commands

def pkgconfig(*packages, **kw):
    flag_map = {'-I': 'include_dirs', '-L': 'library_dirs', '-l': 'libraries'}
    for token in commands.getoutput("pkg-config --libs --cflags %%s" %% ' '.join(packages)).split():
        kw.setdefault(flag_map.get(token[:2]), []).append(token[2:])
    return kw

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = [Extension('dk_sim_%(mcount)d', ['dk_sim.pyx', 'dk_code.cpp'], **pkgconfig('cminpack'))]
    )
    """

else:
    setup_template = """
from distutils.core import setup
from distutils.extension import Extension

setup(ext_modules = [Extension('dk_sim_%(mcount)d', ['dk_code.cpp'],
%(flags)s)])
    """

c_template = {
    "linear": "",
    None: c_template_hybr,
    "hybr": c_template_hybr,
    "lm": c_template_lm,
}

def get_setup_template():
    return setup_template

def get_cpp_template(method):
    return c_template_top + c_template[method]
