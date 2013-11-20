from __future__ import division
import quik

class MyLoader(object):
    def load_template(self, name):
        return globals()[name]

class Template(quik.Template):
    def render(self, namespace, loader=MyLoader()):
        return quik.Template.render(self, namespace, loader)

c_template_top = Template("""
#include <iostream>
#include <cmath>
#include <cminpack.h>
#include <Eigen/Core>
%if (@np > 0)
#include <Eigen/LU>
%end
#include "gx_plugin.h"

using namespace Eigen;

#define N_(x) (x)

static inline int sign(creal v) {
    return v < 0 ? -1 : 1;
}

static Matrix<creal, @nx, 1> g_x;
creal g_v_data[@nn];
static Map<Matrix<creal, @nn, 1> >g_v(g_v_data);
static Array<creal, @nni, 1> g_min;
static Array<creal, @nni, 1> g_max;
static creal g_fnorm;
static int g_info;
static int g_nfev;

#define INTERFACE_VERSION 1

extern "C" __attribute__ ((visibility ("default")))
int get_interface_version() {
    return INTERFACE_VERSION;
}

extern "C" __attribute__ ((visibility ("default")))
void get_structure(const char **name, int *data_size, const int **shapes,
                   const char **method, const char ***pot_vars, const double **pot,
                   const char ***out_labels, const char **comment) {
    static const char *n = "@name";
    static int sz[] = { @nx, @ni, @nn, @no, @npl, @nni, @nno, -1 }; // nx, ni, nn, no, npl, nni, nno, -1
    static const char *m = "@method";
    static const char *pvars[] = {@pot_vars};
    static double pvalues[] = {@pot};
    static const char *ol[] = {@out_labels};
    static const char *c = "@comment";
    if (name) *name = n;
    if (data_size) *data_size = sizeof(creal);
    if (shapes) *shapes = sz;
    if (method) *method = m;
    if (pot_vars) *pot_vars = pvars;
    if (pot) *pot = pvalues;
    if (out_labels) *out_labels = ol;
    if (comment) *comment = c;
}

extern "C" __attribute__ ((visibility ("default")))
void get_dc(creal *v0, creal *x0, creal *p0, creal *o0, creal *op) {
    if (v0) {
        static creal v0_data[] = {@v0_data};
        for (int i = 0; i < @nn; i++) {
            v0[i] = v0_data[i];
        }
    }
    if (x0) {
        static creal x0_data[] = {@x0_data};
        for (int i = 0; i < @nx; i++) {
            x0[i] = x0_data[i];
        }
    }
    if (p0) {
        static creal p0_data[] = {@p0_data};
        for (int i = 0; i < @nni; i++) {
            p0[i] = p0_data[i];
        }
    }
    if (o0) {
        static creal o0_data[] = {@o0_data};
        for (int i = 0; i < @no; i++) {
            o0[i] = o0_data[i];
        }
    }
    if (op) {
        static creal op_data[] = {@op_data};
        for (int i = 0; i < @ni; i++) {
            op[i] = op_data[i];
        }
    }
}

extern "C" __attribute__ ((visibility ("default")))
void get_info(creal *v, creal *x, creal *minval, creal *maxval, int *info, int *nfev, creal *fnorm) {
    Map<Matrix<creal, @nn, 1> > V(v);
    V = g_v;
    Map<Matrix<creal, @nx, 1> > X(x);
    X = g_x;
    Map<Matrix<creal, @nni, 1> > Mi(minval);
    Mi = g_min;
    Map<Matrix<creal, @nni, 1> > Ma(maxval);
    Ma = g_max;
    *info = g_info;
    *nfev = g_nfev;
    *fnorm = g_fnorm;
}

extern "C" __attribute__ ((visibility ("default")))
void set_state(creal *v, creal *x) {
    Map<Matrix<creal, @nn, 1> > V(v);
    g_v = V;
    Map<Matrix<creal, @nx, 1> > X(x);
    g_x = X;
}

@const_matrices

@global_matrices

static Matrix<creal, @npl, 1> last_pot;

struct nonlin_param {
    Matrix<creal, @nni, 1> *p;
    Matrix<creal, @nno, 1> *i;
%if (@solver && @solver.blocklist)
    Map<Matrix<creal, @nn, 1> > *v;
%end
%if (!@have_constant_matrices)
    Matrix<creal, @nn, @nn> *K;
    Matrix<creal, @nn, @mp_cols> *Mp;
    Matrix<creal, @nni, 1> *Mpc;
    //Matrix<creal, @nno, @nn> *Mi;
%end
    inline nonlin_param(Matrix<creal, @nni, 1> *p_, Matrix<creal, @nno, 1> *i_%if(@solver && @solver.blocklist), Map<Matrix<creal, @nn, 1> > *v_%end%if(!@have_constant_matrices), Matrix<creal, @nn, @nn> *K_, Matrix<creal, @nn, @mp_cols> *Mp_, Matrix<creal, @nn, 1> *Mpc_/*, Matrix<creal, @nno, @nn> *Mi_*/%end)
      : p(p_), i(i_)%if(@solver && @solver.blocklist), v(v_)%end%if(!@have_constant_matrices), K(K_), Mp(Mp_), Mpc(Mpc_)/*, Mi(Mi_)*/%end {}
};

extern "C" __attribute__ ((visibility ("default")))
void calc_inv_update(const creal *pot) {
    Map<const Matrix<creal, @npl, 1> >pm(pot);
    last_pot = pm;
    @update_pot
}

%for @c in @components:
%parse ("c_template_nonlin")
%end

%if (@solver)
%set @c = @solver:
%parse ("c_template_nonlin")
%end

extern "C" __attribute__ ((visibility ("default")))
int calc_stream(creal *u, creal *o, int n) {
    Matrix<creal, @nno, 1> mi;
%if (@nn)
    g_min = Matrix<creal, @nni, 1>::Constant(HUGE_VAL);
    g_max = Matrix<creal, @nni, 1>::Constant(-HUGE_VAL);
    g_fnorm = 0;
    Matrix<creal, @nni, 1> mp;
    Map<Matrix<creal, @nn, 1> > Mv(&g_v(0));
    nonlin_param par(&mp, &mi@nonlin_mat_list);
%end
    for (int j = 0; j < n; j++) {
#define GET_U (u+j*@ni)
#define DTP_U creal
        @pre_filter
%if (@nn)
        Matrix<creal, @mp_cols, 1> dp;
        dp << g_x, Map<Matrix<creal,@ni,1> >(GET_U);
        @gen_mp
        g_min = g_min.min(mp.array());
        g_max = g_max.max(mp.array());
        creal fnorm;
        int ret = nonlin::nonlin_solve(par, g_v, &g_info, &g_nfev, &fnorm);
        if (fnorm > g_fnorm) {
            g_fnorm = fnorm;
        }
        if (ret != 0) {
            return ret;
        }
%end
        Matrix<creal, @m_cols, 1> d;
%if (@nn)
        d << g_x, Map<Matrix<creal,@ni,1> >(GET_U), mi;
%else
        d << g_x, Map<Matrix<creal,@ni,1> >(GET_U);
%end
        Matrix<creal, @nx, 1>& xn = g_x;
        @gen_xn
        Map<Matrix<creal, @no, 1> > xo(o+@no*j);
        @gen_xo
#undef GET_U
#undef DTP_U
    }
    return 0;
}

extern "C" __attribute__ ((visibility ("default")))
int calc(creal *u, creal *x, creal *v, creal *x_new, creal *o, int *info, int *nfev, creal *fnorm) {
#define GET_U (u)
#define DTP_U creal
    @pre_filter
    int ret = 0;
    Matrix<creal, @nno, 1> mi;
%if (@nn)
    Matrix<creal, @mp_cols, 1> dp;
    dp << Map<Matrix<creal,@nx,1> >(x), Map<Matrix<creal,@ni,1> >(u);
    Matrix<creal, @nni, 1> mp;
    Map<Matrix<creal, @nn, 1> >Mv(v);
    nonlin_param par(&mp, &mi@nonlin_mat_list);
    @gen_mp
    ret = @namespace::nonlin(par, Mv, info, nfev, fnorm);
%else
    *info = 1;
    *nfev = 0;
    *fnorm = 0;
%end
    Matrix<creal, @m_cols, 1> d;
    d << Map<Matrix<creal,@nx,1> >(x), Map<Matrix<creal,@ni,1> >(u), mi;
    Map<Matrix<creal, @nx, 1> > xn(x_new);
    @gen_xn
    Map<Matrix<creal, @no, 1> > xo(o);
    @gen_xo
    return ret;
#undef GET_U
#undef DTP_U
}

class DKPlugin: public PluginDef {
private:
    float pots[@npl];
    creal pots_last[@npl];
    Matrix<creal, @nx, 1> x_last;
public:
    DKPlugin();
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static void process(int count, float *input, float *output, PluginDef *plugin);
    static int registerparam(const ParamReg& reg);
    static int uiloader(const UiBuilder& builder, int form);
    static void del_instance(PluginDef *plugin);
};

DKPlugin::DKPlugin():
    PluginDef(), pots(), pots_last(), x_last() {
    version = PLUGINDEF_VERSION;
    id = "@id";
    name = N_("@name");
    category = N_("External");
    mono_audio = process;
    set_samplerate = init;
    register_params = registerparam;
    load_ui = uiloader;
    delete_instance = del_instance;
    get_dc(0, &x_last(0), 0, 0, 0);
}

#define PARAM(p) ("@id" "." p)

int DKPlugin::registerparam(const ParamReg& reg) {
    %if (@regs)
        DKPlugin& self = *static_cast<DKPlugin*>(reg.plugin);
    %end
    %for @r in @regs:
        reg.registerVar(PARAM("@r.id"), N_("@r.name"), "S", N_("@r.desc"), &self.pots[@r.varidx], 0.5, 0, 1, 0.01);
    %end
    return 0;
}

void DKPlugin::init(unsigned int samplingFreq, PluginDef *plugin) {
    //DKPlugin& self = *static_cast<DKPlugin*>(plugin);
    //self.sample_rate = samplingFreq;
    //const double *t;
    //get_structure(0, 0, 0, 0, 0, &t, 0, 0);
    //FIXME: overwritten by registration parameters?
    //for (int i = 0; i < @npl; i++) {
    //    self.pots[i] = t[i];
    //}
}

void DKPlugin::process(int n, float *u, float *o, PluginDef *plugin) {
    DKPlugin& self = *static_cast<DKPlugin*>(plugin);
%if (@npl)
    creal t[@npl];
    @calc_pots
%end
// start copied and modified code
    Matrix<creal, @nno, 1> mi;
%if (@nn)
    g_min = Matrix<creal, @nni, 1>::Constant(HUGE_VAL);
    g_max = Matrix<creal, @nni, 1>::Constant(-HUGE_VAL);
    g_fnorm = 0;
    Matrix<creal, @nni, 1> mp;
    Map<Matrix<creal, @nn, 1> > Mv(&g_v(0));
    nonlin_param par(&mp, &mi@nonlin_mat_list);
%end
    for (int j = 0; j < n; j++) {
#define GET_U (u+j*@ni)
#define DTP_U float
        @pre_filter
%if (@npl)
        for (int k = 0; k < @npl; k++) {
            self.pots_last[k] = @timecst * t[k] + (1-@timecst) * self.pots_last[k];
        }
        calc_inv_update(self.pots_last);
%end
%if (@nn)
        Matrix<creal, @mp_cols, 1> dp;
        dp << self.x_last, Map<Matrix<float,@ni,1> >(GET_U).cast<creal>();
        @gen_mp
        g_min = g_min.min(mp.array());
        g_max = g_max.max(mp.array());
        creal fnorm;
        int ret = nonlin::nonlin_solve(par, g_v, &g_info, &g_nfev, &fnorm);
        if (fnorm > g_fnorm) {
            g_fnorm = fnorm;
        }
        if (ret != 0) {
            return;
        }
%end
        Matrix<creal, @m_cols, 1> d;
        d << self.x_last, Map<Matrix<float,@ni,1> >(GET_U).cast<creal>(), mi;
        Matrix<creal, @nx, 1>& xn = self.x_last;
        @gen_xn
        Map<Matrix<float, @no, 1> > xo(o+@no*j);
        @gen_xo_float
#undef GET_U
#undef DTP_U
    }
// end copied code
}

int DKPlugin::uiloader(const UiBuilder& b, int form) {
    if (!(form & UI_FORM_STACK)) {
        return -1;
    }
    %parse ("module_ui_template")
    return 0;
}

void DKPlugin::del_instance(PluginDef *p)
{
    delete static_cast<DKPlugin*>(p);
}

#if false

PluginDef *plugin() {
    return new DKPlugin;
}

#else

extern "C" __attribute__ ((visibility ("default")))
int get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    const int count = 1;
    if (!pplugin) {
        return count;
    }
    switch (idx) {
    case 0: *pplugin = new DKPlugin; return count;
    default: *pplugin = 0; return -1;
    }
}

#endif
""")

c_template_nonlin = Template("""
namespace @c.namespace {
struct fcn_param {
    Matrix<creal, @nn, 1> *p;
    Matrix<creal, @nn, 1> *i;
%if (@c.blocklist||@c.use_blocks)
    Map<Matrix<creal, @nn, 1> > *Mv;
%end
%if (!@have_constant_matrices)
    Matrix<creal, @nn, @nn> *K;
%end
    inline fcn_param(Matrix<creal, @nn, 1> *p_, Matrix<creal, @nn, 1> *i_%if(@c.blocklist||@c.use_blocks), Map<Matrix<creal, @nn, 1> > *Mv_%end%if(!@have_constant_matrices), Matrix<creal, @nn, @nn> *K_%end)
      : p(p_), i(i_)%if(@c.blocklist||@c.use_blocks), Mv(Mv_)%end%if(!@have_constant_matrices), K(K_)%end {}
};
@c.const_matrices

/* nonlinear function for root-finding */
%if (@method == "hybr")
static int fcn(void *p, int n, const double *v, double *fvec, int iflag ) {
%else %% @method == "lm"
static int fcn(void *p, int m, int n, const double *v, double *fvec, int iflag ) {
%end
%if (@c.blocklist)
    nonlin_param& par = *static_cast<nonlin_param *>(p);
    int ret;
    Map<const Matrix<double, @c.nn, 1> >Mv(v);
    Matrix<creal, @nni, 1> *pp = par.p;
    Matrix<creal, @nni, 1> pt = *par.p;
    par.p = &pt;
    %for @bl in @c.blocklist:
        @bl.block
        ret = @bl.namespace::nonlin_solve(par, *par.v, &g_info, &g_nfev, &g_fnorm);
        if (ret != 0) {
            par.p = pp;
            return 1;
        }
    %end
    Map<Matrix<double, @c.nn, 1> >Mfvec(fvec);
    par.i->block<@nn-@c.block_off, 1>(@c.block_off, 0) = Mv;
    @c.equation
    par.p = pp;
%else
    fcn_param& par = *static_cast<fcn_param *>(p);
    @c.i
    @c.fcn_local_matrix_declaration
    mv << @c.v_list;
    Map<Matrix<double, @c.nn, 1> >Mfvec(fvec);
    @c.equation
%end
    return 0;
}

static int nonlin(struct nonlin_param &par, Map<Matrix<creal, @nn, 1> >& v, int *info, int *nfev, creal *fnorm) {
    int j, maxfev, mode, nprint, ldfjac;
    double xtol, epsfcn, factor;
    double fvec[@c.nn], diag[@c.nn], fjac[@c.nn*@c.nn], qtf[@c.nn], wa1[@c.nn], wa2[@c.nn], wa3[@c.nn], wa4[@c.nn];
%if (@method == "hybr")
    int ml, mu, lr;
    double r[(@c.nn*(@c.nn+1))/2];
    lr = (@c.nn*(@c.nn+1))/2;
    ml = @c.nn-1; /* unbanded jacobian */
    mu = @c.nn-1; /* unbanded jacobian */
%else %% @method == "lm"
    int ipvt[@c.nn];
    double ftol, gtol;
    ftol = sqrt(__cminpack_func__(dpmpar)(1)); // parameter
    gtol = 0.; // parameter
%end
    ldfjac = @c.nn;

    /* parameter */
    xtol = @c.solver_xtol;
    maxfev = 2000;
    epsfcn = 0.;
    mode = 2;  /* explicit variable scaling with diag */
    for (j = 0; j < @c.nn; j++) {
        diag[j] = 1;
    }
    factor = @c.solver_factor;
    nprint = 0;
    /**/

    @c.local_matrix_declaration
    @c.p_transform
%if (@c.blocklist)
    nonlin_param fcn_p(@c.nonlin_mat_list);
%else
    fcn_param fcn_p(@c.fcn_p_list);
%end

    /* find root */
%if (@method == "hybr")
    *info = __cminpack_func__(hybrd)(fcn, &fcn_p, @c.nn, &v(@c.block_off), fvec, xtol, maxfev, ml, mu, epsfcn,
                                    diag, mode, factor, nprint, nfev,
                                    fjac, ldfjac, r, lr, qtf, wa1, wa2, wa3, wa4);
%else %% @method == "lm"
    *info = __cminpack_func__(lmdif)(fcn, &fcn_p, @c.nn, @c.nn, &v(@c.block_off), fvec, ftol, xtol, gtol, maxfev, epsfcn,
                                    diag, mode, factor, nprint, nfev, fjac, ldfjac,
                                    ipvt, qtf, wa1, wa2, wa3, wa4);
%end
    *fnorm = __cminpack_func__(enorm)(@c.nn, fvec);

    @c.i_transform

%if (@method == "hybr")
    if (*info == 1) {
        return 0;
    } else if (*info == 5 && *fnorm < 1e-20) {
        return 0;
    } else {
        return -1;
    }
%else %% @method == "lm"
    return (*info < 1 || *info > 4) ? -1 : 0;
%end
}

static Matrix<creal, @c.nni, 1> last_good;
static Matrix<creal, @c.nn, 1> last_v0;

int nonlin_homotopy(int n, Matrix<creal, @c.nni, 1>& start, nonlin_param& par, Map<Matrix<creal, @nn, 1> >& v, int *info, int *nfev, creal *fnorm) {
    Matrix<creal, @c.nni, 1> end = @c.par_p;
    for (int j = 1; j <= n; j++) {
        @c.par_p = start + (j * (end - start)) / n;
        int ret = nonlin(par, v, info, nfev, fnorm);
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}

static inline int nonlin_solve(nonlin_param& par, Map<Matrix<creal, @nn, 1> >& v, int *info, int *nfev, creal *fnorm) {
    int ret = nonlin(par, v, info, nfev, fnorm);
    if (ret != 0) {
        int n = 2;
        for (int j = 0; j < 64000; j++) {
            v@c.v_block = last_v0;
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
    last_good = @c.par_p;
    last_v0 = g_v@c.v_block;
    return 0;
}
} // end namespace @c.namespace

extern "C" __attribute__ ((visibility ("default")))
int calc_@{c.namespace}(int n, creal *p, creal *i, creal *v, int *info, int *nfev, creal *fnorm) {
    int ret = 0;
    Matrix<creal, @nni, 1> mp;
    Matrix<creal, @nno, 1> mi;
    Map<Matrix<creal, @nn, 1> >Mv(v);
    nonlin_param par(&mp, &mi@nonlin_mat_list);
    for (int k = 0; k < n; k++) {
        calc_inv_update(p+k*(@nni+@npl));
        %if (@c.blocklist)
            mp.block<@nni, 1>(0, 0) << Map<Matrix<creal, @nni, 1> >(p+k*(@nni+@npl)+@npl);
            ret = @c.namespace::nonlin_solve(par, Mv, info, nfev, fnorm);
            Map<Matrix<creal, @c.nno, 1> >(i+k*@nno) << mi.block<@nno, 1>(0, 0);
        %else
            mp.block<@c.nni, 1>(@c.block_off, 0) << Map<Matrix<creal, @c.nni, 1> >(p+k*(@c.nni+@c.npl)+@c.npl);
            ret = @c.namespace::nonlin_solve(par, Mv, info, nfev, fnorm);
            Map<Matrix<creal, @c.nno, 1> >(i+k*@c.nno) << mi.block<@c.nno, 1>(@c.block_off, 0);
        %end
    }
    return ret;
}

""")

c_template_table = Template("""
#ifndef _INTPP_H
#define _INTPP_H 1

#define real realtype  // real conflicts with Eigen::real of new eigen library version
//typedef double real;
typedef float real;
typedef @solver_table_maptype maptype;

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
template<int K> static void fpbspl(real *t, real x, int l, real *h)
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
    real *cc = p->c[0];
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
    real *cc = p->c[0];
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
    real *cc = p->c[0];
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

namespace @namespace {
@struct_decl

static int nonlin(struct nonlin_param &par, Map<Matrix<creal, @nn, 1> >& v, int *info, int *nfev, creal *fnorm) {
    real t[AmpData::@solver_table_name::sd.m];
    real m[@nni+@npl];
    Map<Matrix<real, @nni+@npl, 1> >mp(m);
    mp << last_pot.cast<real>(), par.p.cast<real>();
    for (int j = 0; j < AmpData::@solver_table_name::sd.m; j++) {
        splinecoeffs *pc = &AmpData::@solver_table_name::sd.sc[j];
        check(&AmpData::@solver_table_name::sd, m, (*pc->eval)(pc, m, &t[j]));
    }
    par.i = Map<Matrix<real, @nno, 1> >(t).cast<creal>();
    *info = 1;
    *nfev = 0;
    *fnorm = 0;
    return 0;
}
} // end namespace
""")

setup_template = Template("""
from distutils.core import setup
from distutils.extension import Extension

setup(ext_modules = [Extension('dk_sim_@mcount', ['dk_code.cpp'@extra_sources],
@flags)])
""")

faust_filter_template = Template("""
declare id "@id";
declare name "@name";

import("filter.lib");

process = pre : iir((@b_list),(@a_list)) with {
    LogPot(a, x) = if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = if(b, 1 - x, x);
    s = 0.993;
    fs = float(SR);
    pre = @pre_filter;

    %for @sl in @sliders:
        @id = vslider("@sl.id[name:@sl.name]", 0.5, 0, 1, 0.01) : Inverted(@sl.inv) : LogPot(@sl.loga) : smooth(s);
    %end

    @coeffs
};
""")

module_ui_template = Template("""
b.openHorizontalhideBox("");
%if (@have_master_slider)
    b.create_master_slider(PARAM("@master_slider_id"), 0);
%end
b.closeBox();
b.openHorizontalBox("");
%for @k in @knob_ids:
    b.create_small_rackknobr(PARAM("@k"), 0);
%end
b.closeBox();
""")
