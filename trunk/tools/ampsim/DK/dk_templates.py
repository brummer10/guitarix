c_template_top = """
#include <cmath>
#include <cminpack.h>
#include <Eigen/Core>
#if %(np)d
#include <Eigen/LU>
#endif

using namespace Eigen;

static inline int sign(double v) {
    return v < 0 ? -1 : 1;
}

static Matrix<double, %(nx)d, 1> g_x;
double g_v_data[%(nn)d];
static Map<Matrix<double, %(nn)d, 1> >g_v(g_v_data);
static Array<double, %(nni)d, 1> g_min;
static Array<double, %(nni)d, 1> g_max;
static double g_fnorm;
static int g_info;
static int g_nfev;

extern "C" void get_structure(int **shapes, const char **method) {
    static int sz[] = { %(nx)d, %(ni)d, %(nn)d, %(no)d, %(npl)d, %(nni)d, %(nno)d, -1 }; // nx, ni, nn, no, npl, nni, nno, -1
    static const char *m = "%(method)s";
    *shapes = sz;
    *method = m;
}

extern "C" void get_info(double *v, double *x, double *minval, double *maxval, int *info, int *nfev, double *fnorm) {
    Map<Matrix<double, %(nn)d, 1> > V(v);
    V = g_v;
    Map<Matrix<double, %(nx)d, 1> > X(x);
    X = g_x;
    Map<Matrix<double, %(nni)d, 1> > Mi(minval);
    Mi = g_min;
    Map<Matrix<double, %(nni)d, 1> > Ma(maxval);
    Ma = g_max;
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

%(const_matrices)s

%(global_matrices)s

%(nonlin_code)s

static Matrix<double, %(nni)d, 1> last_good;
static Matrix<double, %(nn)d, 1> last_v0;

#if %(nn)d
int nonlin_homotopy(int n, Matrix<double, %(nni)d, 1>& start, %(namespace)s::nonlin_param& par, Map<Matrix<double, %(nn)d, 1> >& v, int *info, int *nfev, double *fnorm) {
    Matrix<double, %(nni)d, 1> end = par.p;
    for (int j = 1; j <= n; j++) {
        par.p = start + (j * (end - start)) / n;
        int ret = %(namespace)s::nonlin(par, v, info, nfev, fnorm);
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}

static inline int nonlin_solve(%(namespace)s::nonlin_param& par, Map<Matrix<double, %(nn)d, 1> >& v, int *info, int *nfev, double *fnorm) {
    int ret = %(namespace)s::nonlin(par, v, info, nfev, fnorm);
    if (ret != 0) {
        int n = 2;
        for (int j = 0; j < 16; j++) {
            v = last_v0;
            ret = nonlin_homotopy(n, last_good, par, v, info, nfev, fnorm);
            if (ret == 0) {
                break;
            }
            n *= 2;
        }
        if (ret != 0) {
            return ret;
        }
    }
    last_good = par.p;
    last_v0 = g_v;
    return 0;
}
#endif

extern "C" int calc_nonlin(int n, double *p, double *i, double *v, int *info, int *nfev, double *fnorm) {
    int ret = 0;
#if %(nn)d
    Matrix<double, %(nni)d, 1> mp;
    Matrix<double, %(nno)d, 1> mi;
    %(namespace)s::nonlin_param par(mp, mi%(nonlin_mat_list)s);
    Map<Matrix<double, %(nn)d, 1> >Mv(v);
    for (int k = 0; k < n; k++) {
        mp << Map<Matrix<double, %(nni)d, 1> >(p+k*%(nni)d);
        ret = nonlin_solve(par, Mv, info, nfev, fnorm);
        Map<Matrix<double, %(nno)d, 1> >(i+k*%(nno)d) << mi;
    }
#else
    *info = 1;
    *nfev = 0;
    *fnorm = 0;
#endif
    return ret;
}

extern "C" void calc_inv_update(const Matrix<double, %(npl)d, 1>& pot) {
    %(update_pot)s
}

extern "C" int calc_stream(double *u, double *o, int n) {
    g_min = Matrix<double, %(nni)d, 1>::Constant(HUGE_VAL);
    g_max = Matrix<double, %(nni)d, 1>::Constant(-HUGE_VAL);
    g_fnorm = 0;
    Matrix<double, %(nno)d, 1> mi;
#if %(nn)d
    Matrix<double, %(nni)d, 1> mp;
    %(namespace)s::nonlin_param par(mp, mi%(nonlin_mat_list)s);
#endif
    for (int j = 0; j < n; j++) {
#if %(nn)d
        Matrix<double, %(mp_cols)d, 1> dp;
        dp << g_x, Map<Matrix<double,%(ni)d,1> >(u+j*%(ni)d);
        %(gen_mp)s
        g_min = g_min.min(mp.array());
        g_max = g_max.max(mp.array());
        double fnorm;
        int ret = nonlin_solve(par, g_v, &g_info, &g_nfev, &fnorm);
        if (fnorm > g_fnorm) {
            g_fnorm = fnorm;
        }
        if (ret != 0) {
            return ret;
        }
#endif
        Matrix<double, %(m_cols)d, 1> d;
        d << g_x, Map<Matrix<double,%(ni)d,1> >(u+j*%(ni)d), mi;
        Matrix<double, %(nx)d, 1>& xn = g_x;
        %(gen_xn)s
        Map<Matrix<double, %(no)d, 1> > xo(o+%(no)d*j);
        %(gen_xo)s
    }
    return 0;
}

extern "C" int calc(double *u, double *x, double *v, double *x_new, double *o, int *info, int *nfev, double *fnorm) {
    int ret = 0;
    Matrix<double, %(nno)d, 1> mi;
#if %(nn)d
    Matrix<double, %(mp_cols)d, 1> dp;
    dp << Map<Matrix<double,%(nx)d,1> >(x), Map<Matrix<double,%(ni)d,1> >(u);
    Matrix<double, %(nni)d, 1> mp;
    %(namespace)s::nonlin_param par(mp, mi%(nonlin_mat_list)s);
    %(gen_mp)s
    Map<Matrix<double, %(nn)d, 1> >Mv(v);
    ret = %(namespace)s::nonlin(par, Mv, info, nfev, fnorm);
#else
    *info = 1;
    *nfev = 0;
    *fnorm = 0;
#endif
    Matrix<double, %(m_cols)d, 1> d;
    d << Map<Matrix<double,%(nx)d,1> >(x), Map<Matrix<double,%(ni)d,1> >(u), mi;
    Map<Matrix<double, %(nx)d, 1> > xn(x_new);
    %(gen_xn)s
    Map<Matrix<double, %(no)d, 1> > xo(o);
    %(gen_xo)s
    return ret;
}
"""

c_template_struct = """
struct fcn_param {
    Matrix<double, %(nn)d, 1>& p;
    Matrix<double, %(nn)d, 1>& i;
    Matrix<double, %(nn)d, %(nn)d>& K;
    inline fcn_param(Matrix<double, %(nn)d, 1>& p_, Matrix<double, %(nn)d, 1>& i_, Matrix<double, %(nn)d, %(nn)d>& K_)
      : p(p_), i(i_), K(K_) {}
};
struct nonlin_param {
    Matrix<double, %(nni)d, 1>&p;
    Matrix<double, %(nno)d, 1>& i;
    Matrix<double, %(nn)d, %(nn)d>& K;
    Matrix<double, %(nn)d, %(mp_cols)d>& Mp;
    Matrix<double, %(nni)d, 1>& Mpc;
    //Matrix<double, %(nno)d, %(nn)d>& Mi;
    inline nonlin_param(Matrix<double, %(nni)d, 1>& p_, Matrix<double, %(nno)d, 1>& i_, Matrix<double, %(nn)d, %(nn)d>& K_,
                        Matrix<double, %(nn)d, %(mp_cols)d>& Mp_, Matrix<double, %(nn)d, 1>& Mpc_/*, Matrix<double, %(nno)d, %(nn)d>& Mi_*/)
      : p(p_), i(i_), K(K_), Mp(Mp_), Mpc(Mpc_)/*, Mi(Mi_)*/ {}
};
"""

c_template_struct_const = """
struct fcn_param {
    Matrix<double, %(nn)d, 1>& p;
    Matrix<double, %(nn)d, 1>& i;
    inline fcn_param(Matrix<double, %(nn)d, 1>& p_, Matrix<double, %(nn)d, 1>& i_): p(p_), i(i_) {}
};
struct nonlin_param {
    Matrix<double, %(nni)d, 1>& p;
    Matrix<double, %(nno)d, 1>& i;
    inline nonlin_param(Matrix<double, %(nni)d, 1>& p_, Matrix<double, %(nno)d, 1>& i_): p(p_), i(i_) {}
};
"""

c_template_hybr = """
namespace %(namespace)s {
%(struct_decl)s

%(const_matrices)s

/* nonlinear function for root-finding */
static int fcn(void *p, int n, const double *v, double *fvec, int iflag ) {
    fcn_param& par = *static_cast<fcn_param *>(p);
    %(i)s
    Matrix<double, %(nn)d, 1>Mv;
    Mv << %(v_list)s;
    Map<Matrix<double, %(nn)d, 1> >Mfvec(fvec);
    %(equation)s
    return 0;
}

static int nonlin(struct nonlin_param &par, Map<Matrix<double, %(nn)d, 1> >& v, int *info, int *nfev, double *fnorm) {
    int j, maxfev, ml, mu, mode, nprint, ldfjac, lr;
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
    factor = %(solver_hybr_factor)e;
    nprint = 0;
    /**/

    %(local_matrix_declaration)s
    fcn_param fcn_p(%(fcn_p_list)s);

    %(p_transform)s

    /* find root */
    *info = __cminpack_func__(hybrd)(fcn, &fcn_p, %(nn)d, &v(0), fvec, xtol, maxfev, ml, mu, epsfcn,
                                    diag, mode, factor, nprint, nfev,
                                    fjac, ldfjac, r, lr, qtf, wa1, wa2, wa3, wa4);
    *fnorm = __cminpack_func__(enorm)(%(nn)d, fvec);

    %(i_transform)s

    if (*info == 1) {
        return 0;
    } else if (*info == 5 && *fnorm < 1e-20) {
        return 0;
    } else {
        return -1;
    }
}
} // end namespace
"""

c_template_lm = """
namespace %(namespace)s {
%(struct_decl)s

%(const_matrices)s

/* nonlinear function for root-finding */
static int fcn(void *p, int m, int n, const double *v, double *fvec, int iflag ) {
    fcn_param& par = *static_cast<fcn_param *>(p);
    %(i)s
    Matrix<double, %(nn)d, 1>Mv;
    Mv << %(v_list)s;
    Map<Matrix<double, %(nn)d, 1> >Mfvec(fvec);
    %(equation)s
    return 0;
}

static int nonlin(struct nonlin_param &par, Map<Matrix<double, %(nn)d, 1> >& v, int *info, int *nfev, double *fnorm) {
    int j, maxfev, mode, nprint, ldfjac, ipvt[%(nn)d];
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
    factor = %(solver_lm_factor)e;
    nprint = 0;
    /**/

    %(local_matrix_declaration)s
    fcn_param fcn_p(%(fcn_p_list)s);

    %(p_transform)s

    /* find root */
    *info = __cminpack_func__(lmdif)(fcn, &fcn_p, %(nn)d, %(nn)d, &v(0), fvec, ftol, xtol, gtol, maxfev, epsfcn,
                                    diag, mode, factor, nprint, nfev, fjac, ldfjac,
                                    ipvt, qtf, wa1, wa2, wa3, wa4);
    *fnorm = __cminpack_func__(enorm)(%(nn)d, fvec);

    %(i_transform)s

    return (*info < 1 || *info > 4) ? -1 : 0;
}
} // end namespace
"""

c_template_table = """
#ifndef _INTPP_H
#define _INTPP_H 1

//typedef double real;
typedef float real;
typedef %(solver_table_maptype)s maptype;

struct splinecoeffs {
    real *x0;
    real *xe;
    real *stepi; // 1/h
    int *n;
    int *nmap;
    maptype **map;
    real **t;
    real **c;
    int (*eval)(splinecoeffs *p, real *x, real *res);
};

struct splinedata {
    splinecoeffs *sc;
    int m;
    int n_input;
    int n_output;
    int n_state;
    const char *func_id;
    template<int K0> static int splev(splinecoeffs *p, real *x, real *res);
    template<int K0, int K1> static int splev(splinecoeffs *p, real *x, real *res);
    template<int K0, int K1, int K2> static int splev(splinecoeffs *p, real *x, real *res);
    template<int K0, int K1, int K2, int K3> static int splev(splinecoeffs *p, real *x, real *res);
    union retval {
        char c[4];
        int i;
    };
};

class SplineCalc {
  protected:
    splinedata *sd;
    real *s0;
    real *temp;
  public:
    SplineCalc(splinedata *sd_, real *s0_);
    ~SplineCalc();
    void reset();
    void calc(real *in, real *out);
};

#define CHECK_BOUNDS

#ifdef CHECK_BOUNDS
void report(splinedata *sd, real *t, int i);
static inline void check(splinedata *sd, real *t, int i) { if (i) report(sd, t, i); }
#else
#define check(sd, t, i) i
#endif

#endif /* !_INTPP_H */
/// BEGIN intpp.cc
#include <cstdio>
#include <cstdlib>
//#include "intpp.h"

#include "intpp_inst.cc"

/****************************************************************
 ** fpbspl evaluates the k non-zero b-splines of order k
 ** at t[l] <= x < t[l+1] using the stable recurrence relation
 ** of de boor and cox.
 **
 ** t: knot array
 ** k: order (2 <= k <= 6)
 ** h[k]: output array
 */
template<int K> static void fpbspl(float *t, real x, int l, real *h)
{
    real hh[K-1];
    h[0] = 1;
    for (int j = 0; j < K-1; j++) {
        for (int i = 0; i <= j; i++) {
            hh[i] = h[i];
        }
        h[0] = 0;
        for (int i = 0; i <= j; i++) {
            int li = l+i+1;
            int lj = li-j-1;
            real f = hh[i]/(t[li]-t[lj]);
            h[i] = h[i]+f*(t[li]-x);
            h[i+1] = f*(x-t[lj]);
        }
    }
}

/****************************************************************
 ** search for knot interval
 ** n: len(map)
 ** k: order
 ** returns index l: t[l] <= x < t[l+1]
 */
static inline int find_index(int n, int k, real *x, real xi, real x0, real xe, real stepi, char* cl)
{
    int l;
    if (k %% 2) {
        l = static_cast<int>((xi - x0) * stepi + 0.5);
    } else {
        l = static_cast<int>((xi - x0) * stepi);
    }
    if (l < 0) {
        *cl = -1;
        *x = x0;
        return 0;
    }
    if (l >= n) {
        *cl = 1;
        *x = xe;
        return n-1;
    }
    *x = xi;
    return l;
}

template<int K>
static inline int forward(int i, splinecoeffs *p, real *xi, real *x, int ll,
                          splinedata::retval *cl, real *h)
{
    int l = p->map[i][find_index(p->nmap[i], K, &x[i], xi[i], p->x0[i], p->xe[i], p->stepi[i], &cl->c[i])];
    fpbspl<K>(p->t[i],x[i],l,h);
    return ll*p->n[i] + l-K+1;
}

/****************************************************************
 ** evaluate the spline function at x
 **
 ** t[n+k]: knot array
 ** c[m][n]: coefficents
 ** k: order (2 <= k <= 5), order = degree + 1
 ** x: function argument
 ** res: output array (size m)
 */
template<int K0>
int splinedata::splev(splinecoeffs *p, real xi[1], real *res)
{
    real h[K0];
    real x;
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, &x, ll, &cl, h);
    real sp = 0;
    for (int j = 0; j < K0; j++) {
        sp += p->c[0][ll+j]*h[j];
    }
    *res = sp;
    return cl.i;
}

/****************************************************************
 ** evaluate the X-dim spline function
 **
 ** t: array of pointers to knot arrays
 ** c[m][n[0]]...[n[X-1]]: coefficents
 ** k: orders (2 <= k[i] <= 5), order = degree + 1
 ** x: function arguments
 ** res[m]: output array
 */
template<int K0, int K1>
int splinedata::splev(splinecoeffs *p, real xi[2], real *res)
{
    real h[2][6];
    real x[2];
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, x, ll, &cl, h[0]);
    ll = forward<K1>(1, p, xi, x, ll, &cl, h[1]);
    float *cc = p->c[0];
    int lc = ll;
    int j[2];
    real sp = 0;
    for (j[0] = 0; j[0] < K0; j[0]++) {
        for (j[1] = 0; j[1] < K1; j[1]++) {
            sp += cc[lc]*h[0][j[0]]*h[1][j[1]];
            lc += 1;
        }
        lc += p->n[1]-K1;
    }
    *res = sp;
    return cl.i;
}

template<int K0, int K1, int K2>
int splinedata::splev(splinecoeffs *p, real xi[3], real *res)
{
    real h[3][6];
    real x[3];
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, x, ll, &cl, h[0]);
    ll = forward<K1>(1, p, xi, x, ll, &cl, h[1]);
    ll = forward<K2>(2, p, xi, x, ll, &cl, h[2]);
    float *cc = p->c[0];
    int lc = ll;
    int j[3];
    real sp = 0;
    for (j[0] = 0; j[0] < K0; j[0]++) {
        for (j[1] = 0; j[1] < K1; j[1]++) {
            for (j[2] = 0; j[2] < K2; j[2]++) {
                sp += cc[lc]*h[0][j[0]]*h[1][j[1]]*h[2][j[2]];
                lc += 1;
            }
            lc += p->n[2]-K2;
        }
        lc += (p->n[1]-K1)*p->n[2];
    }
    *res = sp;
    return cl.i;
}

template<int K0, int K1, int K2, int K3>
int splinedata::splev(splinecoeffs *p, real xi[4], real *res)
{
    real h[4][6];
    real x[4];
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, x, ll, &cl, h[0]);
    ll = forward<K1>(1, p, xi, x, ll, &cl, h[1]);
    ll = forward<K2>(2, p, xi, x, ll, &cl, h[2]);
    ll = forward<K3>(3, p, xi, x, ll, &cl, h[3]);
    float *cc = p->c[0];
    int lc = ll;
    int j[4];
    real sp = 0;
    for (j[0] = 0; j[0] < K0; j[0]++) {
        for (j[1] = 0; j[1] < K1; j[1]++) {
            for (j[2] = 0; j[2] < K2; j[2]++) {
                for (j[3] = 0; j[3] < K3; j[3]++) {
                    sp += cc[lc]*h[0][j[0]]*h[1][j[1]]*h[2][j[2]]*h[3][j[3]];
                    lc += 1;
                }
                lc += p->n[3]-K3;
            }
            lc += (p->n[2]-K2)*p->n[3];
        }
        lc += (p->n[1]-K1)*p->n[2]*p->n[3];
    }
    *res = sp;
    return cl.i;
}

SplineCalc::SplineCalc(splinedata *sd_, real *s0_)
    : sd(sd_),
      s0(s0_),
      temp(new real[sd->n_input+sd->n_state]) {
}

SplineCalc::~SplineCalc() {
    delete[] temp;
}

#ifdef CHECK_BOUNDS
void report(splinedata *sd, real *t, int i)
{
    printf("%%s:", sd->func_id);
    splinedata::retval cl;
    cl.i = i;
    for (int n = 0; n < 4; n++) {
        if (cl.c[n] < 0) {
            printf(" %%d:L[%%g]", n, t[n]);
        } else if (cl.c[n] > 0) {
            printf(" %%d:U[%%g]", n, t[n]);
        }
    }
    printf("\\n");
}
#endif

void SplineCalc::calc(real *in, real *out)
{
    for (int i = 0; i < sd->n_input; i++) {
        temp[i] = in[i];
    }
    real t[sd->m];
    for (int i = 0; i < sd->m; i++) {
        splinecoeffs *p = &sd->sc[i];
        check(sd, temp, (*p->eval)(p, temp, &t[i]));
    }
    for (int i = 0; i < sd->n_output; i++) {
        out[i] = t[i];
    }
    for (int i = 0; i < sd->n_state; i++) {
        temp[i+sd->n_input] = t[i+sd->n_output];
    }
}

void SplineCalc::reset()
{
    for (int i = 0; i < sd->n_state; i++) {
        temp[i+sd->n_input] = s0[i];
    }
}
/// END intpp.cc

#include "data.h"

namespace %(namespace)s {
%(struct_decl)s

static int nonlin(struct nonlin_param &par, Map<Matrix<double, %(nn)d, 1> >& v, int *info, int *nfev, double *fnorm) {
    float t[AmpData::%(solver_table_name)s::sd.m];
    float m[%(nno)d];
    Map<Matrix<float, %(nni)d, 1> >mp(m);
    mp = par.p.cast<float>();
    for (int j = 0; j < AmpData::%(solver_table_name)s::sd.m; j++) {
        splinecoeffs *pc = &AmpData::%(solver_table_name)s::sd.sc[j];
        check(&AmpData::%(solver_table_name)s::sd, m, (*pc->eval)(pc, m, &t[j]));
    }
    par.i = Map<Matrix<float, %(nno)d, 1> >(t).cast<double>();
    *info = 1;
    *nfev = 0;
    *fnorm = 0;
    return 0;
}
} // end namespace
"""

setup_template = """
from distutils.core import setup
from distutils.extension import Extension

setup(ext_modules = [Extension('dk_sim_%(mcount)d', ['dk_code.cpp'%(extra_sources)s],
%(flags)s)])
"""

c_template = {
    "linear": "",
    "table": c_template_table,
    None: c_template_hybr,
    "hybr": c_template_hybr,
    "lm": c_template_lm,
}

def get_setup_template():
    return setup_template

def get_templates(method):
    return c_template_top, c_template[method]
