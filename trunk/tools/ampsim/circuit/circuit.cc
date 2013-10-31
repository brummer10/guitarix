#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <kinsol/kinsol.h>
#include <kinsol/kinsol_dense.h>
#include <nvector/nvector_serial.h>
#include <sundials/sundials_types.h>
#include <sundials/sundials_math.h>
#include "circuit.hpp"

#define DOUBLE_UPDATE false

//#define FTOL   RCONST(1.e-7)  /* function tolerance */
//#define STOL   RCONST(1.e-5) /* step tolerance */
#define FTOL   RCONST(1.e-11)  /* function tolerance */
#define STOL   RCONST(1.e-9) /* step tolerance */

#define ZERO   RCONST(0.0)
#define ONE    RCONST(1.0)

static void print_vec(const char *t, N_Vector v) {
    printf("%s =", t);
    for (int i = 0; i < NV_LENGTH_S(v); i++) {
	printf(" %g", Ith(v, i));
    }
    printf("\n");
}

/*
 * Check function return value...
 *    opt == 0 means SUNDIALS function allocates memory so check if
 *             returned NULL pointer
 *    opt == 1 means SUNDIALS function returns a flag so check if
 *             flag >= 0
 *    opt == 2 means function allocates memory so check if returned
 *             NULL pointer 
 */

static int check_flag(void *flagvalue, const char *funcname, int opt)
{
    int *errflag;

    /* Check if SUNDIALS function returned NULL pointer - no memory allocated */
    if (opt == 0 && flagvalue == NULL) {
	fprintf(stderr, 
		"\nSUNDIALS_ERROR: %s() failed - returned NULL pointer\n\n",
		funcname);
	return(1);
    }

    /* Check if flag < 0 */
    else if (opt == 1) {
	errflag = (int *) flagvalue;
	if (*errflag < 0) {
	    fprintf(stderr,
		    "\nSUNDIALS_ERROR: %s() failed with flag = %d\n\n",
		    funcname, *errflag);
	    return(1); 
	}
    }

    /* Check if function returned NULL pointer - no memory allocated */
    else if (opt == 2 && flagvalue == NULL) {
	fprintf(stderr,
		"\nMEMORY_ERROR: %s() failed - returned NULL pointer\n\n",
		funcname);
	return(1);
    }

    return(0);
}

/* 
 * Print final statistics contained in iopt 
 */

static void PrintFinalStats(void *kmem)
{
    long int nni, nfe, nje, nfeD;
    int flag;
  
    flag = KINGetNumNonlinSolvIters(kmem, &nni);
    check_flag(&flag, "KINGetNumNonlinSolvIters", 1);
    flag = KINGetNumFuncEvals(kmem, &nfe);
    check_flag(&flag, "KINGetNumFuncEvals", 1);

    flag = KINDlsGetNumJacEvals(kmem, &nje);
    check_flag(&flag, "KINDlsGetNumJacEvals", 1);
    flag = KINDlsGetNumFuncEvals(kmem, &nfeD);
    check_flag(&flag, "KINDlsGetNumFuncEvals", 1);

    printf("Final Statistics:\n");
    printf("  nni = %5ld    nfe  = %5ld \n", nni, nfe);
    printf("  nje = %5ld    nfeD = %5ld \n", nje, nfeD);
}


/****************************************************************
 * Spline
 *
 * http://www.thefullwiki.org/Spline_(mathematics)
 */

Spline::Spline(double *y, int n, double xstart, double h):
    count(n), x0(xstart), step(h), c(new double[n]), f(y)
{
    double *z = new double[n-1];
    double *mu = new double[n-1];
    double l = 1;
    mu[0] = 0.0;
    z[0] = 0.0;
    for (int i = 1; i < n-1; i++) {
	l = 4 - mu[i-1];
	mu[i] = 1 / l;
	z[i] = (3 * (y[i+1]-2*y[i]+y[i-1]) - z[i-1]) / l;
    }
    c[n-1] = 0.0;
    for (int i = n-2; i >= 0; i--) {
	c[i] = z[i] - mu[i] * c[i+1];
    }
    delete[] z;
    delete[] mu;
}

Spline::~Spline()
{
    delete c;
}

double Spline::eval(double x)
{
    x = (x - x0) / step;
    int i = static_cast<int>(x);
    if (i < 0) {
	i = 0;
	x = 0.0;
    } else if (i >= count-1) {
	i = count-2;
	x = 1.0;
    } else {
	x = x - i;
    }
    double b = (f[i+1]-f[i]) - (c[i+1]+2*c[i])/3;
    return ((((c[i+1]-c[i])/3 * x + c[i]) * x) + b) * x + f[i];
}

/****************************************************************
 * Grid
 */

Grid::Grid(int d, Dim *v, int n)
{
    vals = n;
    ndim = d;
    dim = v;
    weight = new double[ndim];
    idx = new int[ndim];
    idx2 = new int[ndim];
    p2dim = 1;
    for (int i = 0; i < ndim; i++) p2dim *= 2;
    pts = new double[vals*p2dim];
    grid = 0;
}

Grid::~Grid()
{
    delete[] weight;
    delete[] idx;
    delete[] idx2;
    delete[] pts;
}

int Grid::calc_strides()
{
    int sz = vals;
    for (Dim *p = dim+ndim; --p >= dim; ) {
	p->stride = sz;
	sz *= p->size;
    }
    return sz;
}

inline float *Grid::cell(int *ix)
{
    float *p = grid;
    for (int i = 0; i < ndim; i++) {
	p += ix[i] * dim[i].stride;
    }
    return p;
}

/****************************************************************
 * Cube
 */

Cube::Cube(int d, Dim *v, int n, int *ix, int n_in_, ComponentBase& cb_, N_Vector u0, const char *fname)
    : Grid(d, v, n),
      cb(cb_),
      mmap_size(0),
      n_in(n_in_) {
    grid = 0;
    int sz = calc_strides();
    if (fname) {
	int fd = open(fname, O_RDONLY);
	if (fd >= 0) {
	    struct stat attr;
	    if (fstat(fd, &attr) >= 0) {
		if (attr.st_size == sz*(int)sizeof(float)) {
		    void *addr = mmap(0, attr.st_size, PROT_READ, MAP_SHARED, fd, 0);
		    if (addr != (void*)-1) {
			grid = static_cast<float*>(addr);
			mmap_size = attr.st_size;
		    }
		}
	    }
	}
    }
    if (!grid) {
	grid = new float[sz];
	N_Vector x = N_VNew_Serial(ndim);
	for (int i = 0; i < ndim; i++) {
	    idx[i] = 0;
	    Ith(x,i) = dim[i].lower;
	}
	fill(ndim, ix, x, u0);
	N_VDestroy_Serial(x);
	if (fname) {
	    int fd = creat(fname, 0666);
	    if (fd < 0) {
		fprintf(stderr, "open %s for writing failed\n", fname);
	    } else {
		if (write(fd, grid, sz*sizeof(float)) != sz*(int)sizeof(float)) {
		    fprintf(stderr, "write to %s failed\n", fname);
		} else {
		    printf("written mmap file %s\n", fname);
		}
		close(fd);
	    }
	}
    }
}

Cube::~Cube()
{
    if (mmap_size) {
	munmap(grid, mmap_size);
    } else {
	delete[] grid;
    }
}

int Cube::fill(int n, int *ix, N_Vector x, N_Vector u0)
{
    N_Vector u = N_VNew_Serial(vals);
    N_VScale_Serial(ONE, u0, u);
    for (int i = 0; i < dim[*ix].size; i++) {
	idx[*ix] = i;
	Ith(x,*ix) = dim[*ix].point(i);
	if (n > 1) {
	    fill(n-1, ix+1, x, u);
	} else {
	    //printf("-> "); N_VPrint_Serial(u); N_VPrint_Serial(x);
	    if (cb.findzero(NV_DATA_S(x), NV_DATA_S(x)+n_in, u)) {
		print_vec("fill error at", x);
		N_VDestroy_Serial(u);
		return 1;
	    }
	    //printf("<- "); N_VPrint_Serial(u);
	    float *p = cell(idx);
	    for (int j = 0; j < vals; j++) {
		p[j] = Ith(u,j);
	    }
	}
	if (i == 0) {
	    N_VScale_Serial(ONE,u,u0);
	}
    }
    N_VDestroy_Serial(u);
    return 0;
}

void Cube::startvalue(N_Vector x, N_Vector s, N_Vector u)
{
    assert(NV_LENGTH_S(x)+NV_LENGTH_S(s) == ndim);
    for (int i = 0; i < NV_LENGTH_S(x); i++) {
	dim[i].index(Ith(x,i),idx[i],weight[i]);
    }
    for (int i = NV_LENGTH_S(x); i < ndim; i++) {
	dim[i].index(Ith(s,i-NV_LENGTH_S(x)),idx[i],weight[i]);
    }
    for (int i = 0; i < p2dim; i++) {
	for (int k = 0; k < ndim; k++) {
	    idx2[k] = idx[k];
	    if (i & (1 << k)) {
		idx2[k] += 1;
	    }
	}
	float *p = cell(idx2);
	for (int j = 0; j < vals; j++) {
	    pts[i*vals+j] = p[j];
	}
    }
    int n = p2dim;
    for (int i = 0; i < ndim; i++) {
	double w = weight[i];
	n /= 2;
	for (int j = 0; j < n; j++) {
	    int b = j*vals;
	    for (int k = 0; k < vals; k++) {
		pts[b+k] = pts[2*b+k] * (1-w) + pts[2*b+vals+k] * w;
	    }
	}
    }
    for (int i = 0; i < vals; i++) {
	Ith(u,i) = pts[i];
    }
}

int Cube::calc(N_Vector x, N_Vector s, N_Vector u)
{
    startvalue(x, s, u);
    return cb.findzero(NV_DATA_S(x), NV_DATA_S(s), u);
}

/****************************************************************
 ** class ComponentBase
 */

ComponentBase::ComponentBase(int neq, int ndim, int nvals, int n_in, int n_out, int n_params_)
    : NEQ(neq),
      NDIM(ndim),
      NVALS(nvals),
      N_IN(n_in),
      N_OUT(n_out),
      n_params(n_params_),
      params(new realtype[n_params_]),
      param_names(new const char*[n_params_]),
      in_names(new const char*[n_in]),
      out_names(new const char*[n_out]),
      state_names(new const char*[ndim-n_out]),
      var_names(new const char*[neq]),
      ix(new int[ndim]),
      verbose(false),
      ranges(new Dim[ndim]),
      cube(0),
      user_data(),
      constraints(0),
      Gco(params[0]),
      Gcf(params[1]),
      mu(params[2]),
      Ex(params[3]),
      Kg1(params[4]),
      Kg2(params[5]),
      Kp(params[6]),
      Kvb(params[7]) {
    const char *p[] = { "Gco", "Gcf", "mu", "Ex", "Kg1", "Kg2", "Kp", "Kvb", 0 };
    set_names(param_names, p, param_off);
}
      
ComponentBase::~ComponentBase() {
    delete[] params;
    delete[] param_names;
    delete[] in_names;
    delete[] out_names;
    delete[] state_names;
    delete[] var_names;
    delete[] ix;
    delete[] ranges;
    delete cube;
    if (constraints) {
	N_VDestroy_Serial(constraints);
    }
}

int ComponentBase::set_range(int i, double lower, double upper, int size) {
    if (i > NDIM) {
	return 0;
    }
    ranges[i].lower = lower;
    ranges[i].upper = upper;
    ranges[i].size = size;
    return 1;
}

void ComponentBase::init(N_Vector u0, const char* fname) {
    N_Vector u = N_VNew_Serial(NEQ);
    for (int i = 0; i < NEQ; i++) {
	Ith(u,i) = Ith(u0,i);
    }
    delete cube;
    cube = new Cube(NDIM, ranges, NEQ, ix, N_IN, *this, u, fname);
    N_VDestroy_Serial(u);
}

//static
int ComponentBase::sfunc(N_Vector x, N_Vector u, void *data) {
    ComponentBase *self = static_cast<ComponentBase*>(data);
    return self->func(x, u, &self->user_data);
}

int ComponentBase::findzero(realtype *x, realtype *state, N_Vector u) {
    int flag;

    N_Vector s = N_VNew_Serial(NEQ);
    if (check_flag((void *)s, "N_VNew_Serial", 0)) return 1;
    N_VConst_Serial(ONE,s); /* no scaling */

    realtype fnormtol = FTOL;
    realtype scsteptol = STOL;

    void *kmem = KINCreate();
    if (check_flag((void *)kmem, "KINCreate", 0)) return 1;

    user_data.inval = x;
    user_data.state = state;
    flag = KINSetUserData(kmem, this);
    if (check_flag(&flag, "KINSetUserData", 1)) return flag;

    if (constraints) {
	flag = KINSetConstraints(kmem, constraints);
	if (check_flag(&flag, "KINSetConstraints", 1)) {
	    return flag;
	}
    }

    flag = KINSetFuncNormTol(kmem, fnormtol);
    if (check_flag(&flag, "KINSetFuncNormTol", 1)) return flag;
    flag = KINSetScaledStepTol(kmem, scsteptol);
    if (check_flag(&flag, "KINSetScaledStepTol", 1)) return flag;

    flag = KINInit(kmem, sfunc, u);
    if (check_flag(&flag, "KINInit", 1)) return flag;

    /* Call KINDense to specify the linear solver */

    flag = KINDense(kmem, NEQ);
    if (check_flag(&flag, "KINDense", 1)) return flag;

    //flag = KINSetPrintLevel(kmem, 3); 
    //if (check_flag(&flag, "KINSetPrintLevel", 1)) return flag;

    int glstr = KIN_NONE;
    //int glstr = KIN_LINESEARCH;
    int mset = 1;
    flag = KINSetMaxSetupCalls(kmem, mset);
    if (check_flag(&flag, "KINSetMaxSetupCalls", 1)) return flag;
    flag = KINSol(kmem, u, glstr, s, s);
    if (flag > 1) {
	printf("res = %d\n", flag);
	return flag;
    }
    if (check_flag(&flag, "KINSol", 1)) return flag;
    if (verbose) {
	PrintFinalStats(kmem);
    }
    N_VDestroy_Serial(s);
    KINFree(&kmem);
    user_data.inval = 0;
    user_data.state = 0;
    return 0;
}

void ComponentBase::startvalue(N_Vector x, N_Vector s, N_Vector u) {
    cube->startvalue(x, s, u);
}

int ComponentBase::calc(N_Vector x, N_Vector s, N_Vector u) {
    return cube->calc(x, s, u);
}

inline realtype ComponentBase::Ig(realtype Ugk) {
    if (Ugk < Gco) {
	return ZERO;
    }
    return Gcf*pow(Ugk-Gco,1.5);
}

inline realtype ComponentBase::Ia(realtype Ugk, realtype Uak) {
    if (Uak < ZERO) {
	return ZERO;
    }
    realtype E1;
    realtype t = Kp*(1/mu+Ugk/sqrt(Kvb+Uak*Uak));
    if (t > 500) {
	E1 = Uak/Kp*t;
    } else if (t < -500) {
	return ZERO;
    } else {
	E1 = Uak/Kp*log(1+exp(t));
    }
    return pow(E1,Ex) / Kg1 * 2*(E1 > 0.0);
}

inline realtype ComponentBase::Iap(realtype Ug1k, realtype Ug2k, realtype Uak) {
    realtype E1;
    if (Ug2k <= 0.0) {
	return ZERO;
    }
    realtype t = Kp*(1/mu+Ug1k/Ug2k);
    if (t > 500) {
	E1 = Ug2k/Kp*t;
    } else if (t < -500) {
	return ZERO;
    } else {
	E1 = Ug2k/Kp*log(1+exp(t));
    }
    return pow(E1,Ex)/Kg1 * 2*(E1 > 0.0) * atan(Uak/Kvb);
}

inline realtype ComponentBase::Is(realtype Ug1k, realtype Ug2k) {
    realtype t = Ug2k/mu+Ug1k;
    if (t < 0) {
	return ZERO;
    }
    return exp(Ex*log(t))/Kg2;
}


/****************************************************************
 ** Components
 */

TriodeCircuit::TriodeCircuit()
    : ComponentBase(3+2, 2, 2, 1, 1, param_off+8),
      Ck(params[param_off+0]),
      G1(params[param_off+1]),
      G2(params[param_off+2]),
      Gg(params[param_off+3]),
      Gk(params[param_off+4]),
      Ga(params[param_off+5]),
      Gl(params[param_off+6]),
      Un(params[param_off+7]) {
    const char *p_names[] = {
	"Ck", "G1", "G2", "Gg", "Gk", "Ga", "Gl", "Un", 0 };
    set_names(param_names+param_off, p_names, n_params-param_off);
    static const char *i_names[] = { "Uin", 0 };
    set_names(in_names, i_names, N_IN);
    static const char *o_names[] = { "Ua", 0 };
    set_names(out_names, o_names, N_OUT);
    static const char *s_names[] = { "Uc1m", 0 };
    set_names(state_names, s_names, NDIM-N_IN);
    static const char *v_names[] = { "Ug", "Uk", "Ua", "l", "L", 0 };
    set_names(var_names, v_names, NEQ);
    ix[0] = 1;
    ix[1] = 0;
    constraints = N_VNew_Serial(NEQ);
    Ith(constraints,0) =  ZERO;   /* no constraint on f1 */
    Ith(constraints,1) =  ZERO;   /* no constraint on f2 */
    Ith(constraints,2) =  ZERO;   /* no constraint on f3 */
    Ith(constraints,3) =  ONE;    /* l = Ua - Uk >= 0 */
    Ith(constraints,4) = -ONE;    /* L = Ua - Un <= 0 */
}

void TriodeCircuit::update(N_Vector y, N_Vector x, N_Vector state) {
    realtype *fdata = NV_DATA_S(y);
    realtype Uk = fdata[1];
    realtype Uc1m = Uk;
    if (DOUBLE_UPDATE) {
	realtype Ug = fdata[0];
	realtype Ua = fdata[2];
	Uc1m = Uc1m - (Uk*Gk - Ia(Ug-Uk,Ua-Uk) - Ig(Ug-Uk)) / (Ck*fs);
    }
    Ith(state,0) = Uc1m;
}

int TriodeCircuit::func(N_Vector u, N_Vector f, UserData *data) {
    realtype *udata = NV_DATA_S(u);
    realtype *fdata = NV_DATA_S(f);

    //printf("-> %g,%g,%g,%g,%g\n", Ith(u,0), Ith(u,1), Ith(u,2), Ith(u,3), Ith(u,4));
    realtype Ug = udata[0];
    realtype Uk = udata[1];
    realtype Ua = udata[2];
    realtype l  = udata[3];
    realtype L  = udata[4];
    realtype Uc = Uk;

    realtype Uin = data->inval[0];
    realtype Uc1m = data->state[0];

    realtype ia = Ia(Ug-Uk,Ua-Uk);
    realtype ig = Ig(Ug-Uk);
    fdata[0] = G2*(Uin*G1+Ug*G2)/(G1+Gg+G2)-Ug*G2-ig;
    fdata[1] = Uc1m-Uc-(Uk*Gk-ia-ig)/(Ck*fs);
    fdata[2] = Un*Ga-Ua*Ga-Ua*Gl-ia;
    fdata[3] = l - (Ua - Uk);
    fdata[4] = L - (Ua - Un);
    //printf("<- %g,%g,%g,%g,%g\n", Ith(f,0), Ith(f,1), Ith(f,2), Ith(f,3), Ith(f,4));

    return(0);
}


CoupledTriodeCircuit::CoupledTriodeCircuit()
    : ComponentBase(7, 3, 3, 1, 1, param_off+13),
      Ck(params[param_off+0]),
      Ca(params[param_off+1]),
      Un(params[param_off+2]),
      G1(params[param_off+3]),
      G2(params[param_off+4]),
      Gg(params[param_off+5]),
      Gk(params[param_off+6]),
      Ga(params[param_off+7]),
      G3(params[param_off+8]),
      Gg2(params[param_off+9]),
      Gk2(params[param_off+10]),
      Ga2(params[param_off+11]),
      Gl(params[param_off+12]) {
    const char *p_names[] = {
	"Ck", "Ca", "Un", "G1", "G2", "Gg", "Gk", "Ga", "G3", "Gg2", "Gk2", "Ga2", "Gl", 0 };
    set_names(param_names+param_off, p_names, n_params-param_off);
    static const char *i_names[] = { "Uin", 0 };
    set_names(in_names, i_names, N_IN);
    static const char *o_names[] = { "U2", 0 };
    set_names(out_names, o_names, N_OUT);
    static const char *s_names[] = { "Uc1m", "Uc2m", 0 };
    set_names(state_names, s_names, NDIM-N_IN);
    static const char *v_names[] = { "Ug", "Uk", "Ua", "U2", "Ug2", "Uk2", "Ua2", 0 };
    set_names(var_names, v_names, NEQ);
    ix[0] = 2;
    ix[1] = 1;
    ix[2] = 0;
}

void CoupledTriodeCircuit::update(N_Vector y, N_Vector x, N_Vector state)
{
    realtype *fdata = NV_DATA_S(y);
    realtype Uk = fdata[1];
    realtype Ua = fdata[2];
    realtype U2 = fdata[3];

    realtype Uc1m = Uk;
    realtype Uc2m = Ua-U2;

    if (DOUBLE_UPDATE) {
	realtype Ug = fdata[0];
	realtype Ug2 = fdata[4];
	realtype ia1 = Ia(Ug-Uk,Ua-Uk);
	realtype ig1 = Ig(Ug-Uk);
	Uc1m = Uc1m - (Uk*Gk-ia1-ig1) / (Ck*fs);
	Uc2m = Uc2m + ((U2-Ug2)*G3) / (Ca*fs);
    }
    Ith(state,0) = Uc1m;
    Ith(state,1) = Uc2m;
}

int CoupledTriodeCircuit::func(N_Vector u, N_Vector f, UserData *data) {
    realtype *udata = NV_DATA_S(u);
    realtype *fdata = NV_DATA_S(f);

    //printf("<- %g,%g,%g,%g,%g,%g,%g\n", Ith(u,0), Ith(u,1), Ith(u,2), Ith(u,3), Ith(u,4), Ith(u,5), Ith(u,6));
    realtype Ug = udata[0];
    realtype Uk = udata[1];
    realtype Ua = udata[2];
    realtype U2 = udata[3];
    realtype Ug2 = udata[4];
    realtype Uk2 = udata[5];
    realtype Ua2 = udata[6];
    realtype Uc1 = Uk;
    realtype Uc2 = Ua-U2;

    realtype Uin = data->inval[0];
    realtype Uc1m = data->state[0];
    realtype Uc2m = data->state[1];

    realtype ia1 = Ia(Ug-Uk,Ua-Uk);
    realtype ig1 = Ig(Ug-Uk);
    realtype ia2 = Ia(Ug2-Uk2,Ua2-Uk2);
    realtype ig2 = Ig(Ug2-Uk2);
    fdata[0] = G2*(Uin*G1+Ug*G2)/(G1+Gg+G2)-Ug*G2-ig1;
    fdata[1] = Uc1m-Uc1-(Uk*Gk-ia1-ig1)/(Ck*fs);
    fdata[2] = (Un-Ua)*Ga-ia1-(U2-Ug2)*G3;
    fdata[3] = Uc2m-Uc2+((U2-Ug2)*G3)/(Ca*fs);
    fdata[4] = (U2-Ug2)*G3-Ug2*Gg2-ig2;
    fdata[5] = Uk2*Gk2-ia2-ig2;
    fdata[6] = (Un-Ua2)*Ga2-Ua2*Gl-ia2;
    //printf("<- %g,%g,%g,%g,%g,%g,%g\n", Ith(f,0), Ith(f,1), Ith(f,2), Ith(f,3), Ith(f,4), Ith(f,5), Ith(f,6));

    return(0);
}


PowerAmpGate::PowerAmpGate()
    : ComponentBase(3, 2, 2, 1, 1, param_off+5),
      C1(params[param_off+0]),
      G1(params[param_off+1]),
      Gb(params[param_off+2]),
      Gg(params[param_off+3]),
      Ub(params[param_off+4]) {
    const char *p_names[] = { "C1", "G1", "Gb", "Gg", "Ub", 0 };
    set_names(param_names+param_off, p_names, n_params-param_off);
    static const char *i_names[] = { "Uin", 0 };
    set_names(in_names, i_names, N_IN);
    static const char *o_names[] = { "Ug", 0 };
    set_names(out_names, o_names, N_OUT);
    static const char *s_names[] = { "Uc1m", 0 };
    set_names(state_names, s_names, NDIM-N_IN);
    static const char *v_names[] = { "U0", "U1", "Ug", 0 };
    set_names(var_names, v_names, NEQ);
    ix[0] = 1;
    ix[1] = 0;
}

void PowerAmpGate::update(N_Vector y, N_Vector x, N_Vector state) {
    realtype *fdata = NV_DATA_S(y);
    realtype U0 = fdata[0];
    realtype U1 = fdata[1];
    realtype Uc1m = U0-U1;

    if (DOUBLE_UPDATE) {
	realtype Ug = fdata[2];
	Uc1m = Uc1m + ((U1-Ub)*Gb+(U1-Ug)*Gg)/(C1*fs);
    }
    Ith(state,0) = Uc1m;
}

int PowerAmpGate::func(N_Vector u, N_Vector f, UserData *data) {
    realtype *udata = NV_DATA_S(u);
    realtype *fdata = NV_DATA_S(f);

    realtype U0 = udata[0];
    realtype U1 = udata[1];
    realtype Ug = udata[2];
    realtype Uc1 = U0 - U1;

    realtype Uin = data->inval[0];
    realtype Uc1m = data->state[0];

    fdata[0] = C1*(Uc1-Uc1m)*fs-(Uin-U0)*G1;
    fdata[1] = (Uin-U0)*G1-(U1-Ub)*Gb-(U1-Ug)*Gg;
    fdata[2] = (U1-Ug)*Gg-Ig(Ug);

    return(0);
}


PowerAmpPlate::PowerAmpPlate()
    : ComponentBase(5+2, 3, 2, 2, 2, param_off+5),
      C2(params[param_off+0]),
      Gd(params[param_off+1]),
      Ga(params[param_off+2]),
      Gs(params[param_off+3]),
      Un(params[param_off+4]) {
    const char *p_names[] = { "C2", "Gd", "Ga", "Gs", "Un", 0 };
    set_names(param_names+param_off, p_names, n_params-param_off);
    static const char *i_names[] = { "Ug1", "Ug2", 0 };
    set_names(in_names, i_names, N_IN);
    static const char *o_names[] = { "Ua1", "Ua2", 0 };
    set_names(out_names, o_names, N_OUT);
    static const char *s_names[] = { "Uc2m", 0 };
    set_names(state_names, s_names, NDIM-N_IN);
    static const char *v_names[] = { "Us1", "Us2", "Ud", "Ua1", "Ua2", "L1", "L2", 0 };
    set_names(var_names, v_names, NEQ);
    ix[0] = 2;
    ix[1] = 1;
    ix[2] = 0;
    constraints = N_VNew_Serial(NEQ);
    Ith(constraints,0) =  ZERO;   /* no constraint on f1 */
    Ith(constraints,1) =  ZERO;   /* no constraint on f2 */
    Ith(constraints,2) =  ZERO;   /* no constraint on f3 */
    Ith(constraints,3) =  ZERO;   /* no constraint on f4 */
    Ith(constraints,4) =  ZERO;   /* no constraint on f5 */
    Ith(constraints,5) =  ONE;    /* L1 = Us1 - Ud/2 >= 0 */
    Ith(constraints,6) =  ONE;    /* L2 = Us2 - Ud/2 >= 0 */
}

void PowerAmpPlate::update(N_Vector y, N_Vector x, N_Vector state) {
    realtype *fdata = NV_DATA_S(y);
    realtype Ud  = fdata[2];
    realtype Uc2m = Ud;
    if (DOUBLE_UPDATE) {
	realtype Us1 = fdata[0];
	realtype Us2 = fdata[1];
	realtype Ua1 = fdata[3];
	realtype Ua2 = fdata[4];
	realtype Ug1 = Ith(x,0);
	realtype Ug2 = Ith(x,1);
	realtype ia1 = Iap(Ug1,Us1,Ua1);
	realtype is1 = Is(Ug1,Us1);
	realtype ia2 = Iap(Ug2,Us2,Ua2);
	realtype is2 = Is(Ug2,Us2);
	Uc2m = Uc2m + ((Un-Uc2m)*Gd-(ia1+ia2+is1+is2))/(C2*fs);
    }
    Ith(state,0) = Uc2m;
}

int PowerAmpPlate::func(N_Vector u, N_Vector f, UserData *data) {
    realtype *udata = NV_DATA_S(u);
    realtype *fdata = NV_DATA_S(f);

    realtype Us1 = udata[0];
    realtype Us2 = udata[1];
    realtype Ud  = udata[2];
    realtype Ua1 = udata[3];
    realtype Ua2 = udata[4];
    realtype L1  = udata[5];
    realtype L2  = udata[6];
    realtype Uc2 = Ud;

    realtype Ug1 = data->inval[0];
    realtype Ug2 = data->inval[1];
    realtype Uc2m = data->state[0];

    realtype ia1 = Iap(Ug1,Us1,Ua1);
    realtype is1 = Is(Ug1,Us1);
    realtype ia2 = Iap(Ug2,Us2,Ua2);
    realtype is2 = Is(Ug2,Us2);
    fdata[0] = -ia1+(Ud-Ua1)*Ga;
    fdata[1] = -ia2+(Ud-Ua2)*Ga;
    fdata[2] = -is1+(Ud-Us1)*Gs;
    fdata[3] = -is2+(Ud-Us2)*Gs;
    fdata[4] = -ia1-ia2-is1-is2+(Un-Ud)*Gd-C2*(Uc2-Uc2m)*fs;
    fdata[5] = L1 - (Us1 - -Ud);
    fdata[6] = L2 - (Us2 - -Ud);

    return(0);
}


PhaseSplitter::PhaseSplitter()
    : ComponentBase(9, 4, 5, 1, 2, param_off+16),
      C1(params[param_off+0]),
      C2(params[param_off+1]),
      C3(params[param_off+2]),
      Un(params[param_off+3]),
      G1(params[param_off+4]),
      Gg1(params[param_off+5]),
      Gg2(params[param_off+6]),
      Gk(params[param_off+7]),
      G2(params[param_off+8]),
      G3(params[param_off+9]),
      G4(params[param_off+10]),
      G5(params[param_off+11]),
      Ga1(params[param_off+12]),
      Ga2(params[param_off+13]),
      Gl1(params[param_off+14]),
      Gl2(params[param_off+15]) {
    const char *p_names[] = {
	"C1", "C2", "C3", "Un", "G1", "Gg1", "Gg2", "Gk", "G2", "G3", "G4", "G5", "Ga1", "Ga2", "Gl1", "Gl2", 0 };
    set_names(param_names+param_off, p_names, n_params-param_off);
    static const char *i_names[] = { "Uin", 0 };
    set_names(in_names, i_names, N_IN);
    static const char *o_names[] = { "Ua1", "Ua2", 0 };
    set_names(out_names, o_names, N_OUT);
    static const char *s_names[] = { "Uc1m", "Uc2m", "Uc3m", 0 };
    set_names(state_names, s_names, NDIM-N_IN);
    static const char *v_names[] = { "U1", "Ug1", "Uk", "Ua1", "U2", "U3", "U4", "Ug2", "Ua2", 0 };
    set_names(var_names, v_names, NEQ);
    ix[0] = 3;
    ix[1] = 2;
    ix[2] = 1;
    ix[3] = 0;
}

void PhaseSplitter::update(N_Vector y, N_Vector x, N_Vector state) {
    realtype *fdata = NV_DATA_S(y);
    realtype U1  = fdata[0];
    realtype Ug1 = fdata[1];
    realtype U3  = fdata[5];
    realtype U4  = fdata[6];
    realtype Ug2 = fdata[7];
    realtype Uc1m = U1-Ug1;
    realtype Uc2m = Ug2-U3;
    realtype Uc3m = U3-U4;
    if (DOUBLE_UPDATE) {
	realtype Uk  = fdata[2];
	realtype U2  = fdata[4];
	realtype ig1 = Ig(Ug1-Uk);
	realtype ig2 = Ig(Ug2-Uk);
	Uc1m = Uc1m + ((Ug1-U2)*Gg1+ig1) / (C1*fs);
	Uc2m = Uc2m - ((Ug2-U2)*Gg2+ig2) / (C2*fs);
	Uc3m = Uc3m + (U4*G4) / (C3*fs);
    }
    Ith(state,0) = Uc1m;
    Ith(state,1) = Uc2m;
    Ith(state,2) = Uc3m;
}

int PhaseSplitter::func(N_Vector u, N_Vector f, UserData *data) {
    realtype *udata = NV_DATA_S(u);
    realtype *fdata = NV_DATA_S(f);

    realtype U1  = udata[0];
    realtype Ug1 = udata[1];
    realtype Uk  = udata[2];
    realtype Ua1 = udata[3];
    realtype U2  = udata[4];
    realtype U3  = udata[5];
    realtype U4  = udata[6];
    realtype Ug2 = udata[7];
    realtype Ua2 = udata[8];
    realtype Uc1 = U1 - Ug1;
    realtype Uc2 = Ug2 - U3;
    realtype Uc3 = U3 - U4;

    realtype Uin = data->inval[0];
    realtype Uc1m = data->state[0];
    realtype Uc2m = data->state[1];
    realtype Uc3m = data->state[2];

    realtype ia1 = Ia(Ug1-Uk,Ua1-Uk);
    realtype ig1 = Ig(Ug1-Uk);
    realtype ia2 = Ia(Ug2-Uk,Ua2-Uk);
    realtype ig2 = Ig(Ug2-Uk);
    fdata[0] = (Uin-U1)*G1-(Ug1-U2)*Gg1-ig1;
    fdata[1] = C1*(Uc1-Uc1m)*fs-(Uin-U1)*G1;
    fdata[2] = (Uk-U2)*Gk-ia1-ig1-ia2-ig2;
    fdata[3] = (Un-Ua1)*Ga1-Ua1*Gl1-ia1;
    fdata[4] = (Un-Ua2)*Ga2-Ua2*Gl2-ia2;
    fdata[5] = -ig2+(U2-Ug2)*Gg2-C2*(Uc2-Uc2m)*fs;
    fdata[6] = (Ug1-U2)*Gg1+(Uk-U2)*Gk-(U2-Ug2)*Gg2-(U2-U3)*G2;
    fdata[7] = (U2-U3)*Gg2-U3*G3-U3*G5-U4*G4+C2*(Uc2-Uc2m)*fs;
    fdata[8] = C3*(Uc3-Uc3m)*fs-U4*G4;

    return(0);
}


PowerAmpPlateTrans::PowerAmpPlateTrans()
    : ComponentBase(5+2, 3, 2, 2, 2, param_off+5),
      C2(params[param_off+0]),
      Gd(params[param_off+1]),
      Ga(params[param_off+2]),
      Gs(params[param_off+3]),
      Un(params[param_off+4]) {
    const char *p_names[] = { "C2", "Gd", "Ga", "Gs", "Un", 0 };
    set_names(param_names+param_off, p_names, n_params-param_off);
    static const char *i_names[] = { "Ug1", "Ug2", 0 };
    set_names(in_names, i_names, N_IN);
    static const char *o_names[] = { "Ua1", "Ua2", 0 };
    set_names(out_names, o_names, N_OUT);
    static const char *s_names[] = { "Uc2m", 0 };
    set_names(state_names, s_names, NVALS-N_OUT);
    static const char *v_names[] = { "Us1", "Us2", "Ud", "Ua1", "Ua2", "L1", "L2", 0 };
    set_names(var_names, v_names, NEQ);
    ix[0] = 2;
    ix[1] = 1;
    ix[2] = 0;
    constraints = N_VNew_Serial(NEQ);
    Ith(constraints,0) =  ZERO;   /* no constraint on f1 */
    Ith(constraints,1) =  ZERO;   /* no constraint on f2 */
    Ith(constraints,2) =  ZERO;   /* no constraint on f3 */
    Ith(constraints,3) =  ZERO;   /* no constraint on f4 */
    Ith(constraints,4) =  ZERO;   /* no constraint on f5 */
    Ith(constraints,5) =  ONE;    /* L1 = Us1 - Ud/2 >= 0 */
    Ith(constraints,6) =  ONE;    /* L2 = Us2 - Ud/2 >= 0 */
}

void PowerAmpPlateTrans::update(N_Vector y, N_Vector x, N_Vector state) {
    realtype *fdata = NV_DATA_S(y);
    realtype Ud  = fdata[2];
    realtype Uc2m = Ud;
    if (DOUBLE_UPDATE) {
	realtype Us1 = fdata[0];
	realtype Us2 = fdata[1];
	realtype Ua1 = fdata[3];
	realtype Ua2 = fdata[4];
	realtype Ug1 = Ith(x,0);
	realtype Ug2 = Ith(x,1);
	realtype ia1 = Iap(Ug1,Us1,Ua1);
	realtype is1 = Is(Ug1,Us1);
	realtype ia2 = Iap(Ug2,Us2,Ua2);
	realtype is2 = Is(Ug2,Us2);
	Uc2m = Uc2m + ((Un-Uc2m)*Gd-(ia1+ia2+is1+is2))/(C2*fs);
    }
    Ith(state,0) = Uc2m;
}

int PowerAmpPlateTrans::func(N_Vector u, N_Vector f, UserData *data) {
    realtype *udata = NV_DATA_S(u);
    realtype *fdata = NV_DATA_S(f);

    realtype Us1 = udata[0];
    realtype Us2 = udata[1];
    realtype Ud  = udata[2];
    realtype Ua1 = udata[3];
    realtype Ua2 = udata[4];
    realtype L1  = udata[5];
    realtype L2  = udata[6];
    realtype Uc2 = Ud;

    realtype Ug1 = data->inval[0];
    realtype Ug2 = data->inval[1];
    realtype Uc2m = data->state[0];

    realtype ia1 = Iap(Ug1,Us1,Ua1);
    realtype is1 = Is(Ug1,Us1);
    realtype ia2 = Iap(Ug2,Us2,Ua2);
    realtype is2 = Is(Ug2,Us2);
    fdata[0] = -ia1+(Ud-Ua1)*Ga;
    fdata[1] = -ia2+(Ud-Ua2)*Ga;
    fdata[2] = -is1+(Ud-Us1)*Gs;
    fdata[3] = -is2+(Ud-Us2)*Gs;
    fdata[4] = -ia1-ia2-is1-is2+(Un-Ud)*Gd-C2*(Uc2-Uc2m)*fs;
    fdata[5] = L1 - (Us1 - -Ud);
    fdata[6] = L2 - (Us2 - -Ud);

    return(0);
}


/*
 *--------------------------------------------------------------------
 * MAIN PROGRAM
 *--------------------------------------------------------------------
 */

#if 0
int main()
{
    N_Vector u = N_VNew_Serial(NEQ);
    for (int i = 0; i < 200; i++) {
	realtype Uin = RCONST(-40.0) + i * (RCONST(40.0)-RCONST(-40.0))/200;
	for (int j = 0; j < 12; j++) {
	    realtype Uc1m = RCONST(-15.0) + j * (RCONST(15.0)-RCONST(-15.0))/12;
	    Ith(u,0) = RCONST(0.0);
	    Ith(u,1) = RCONST(0.0);
	    Ith(u,2) = RCONST(340.0);
	    printf("-> %g, %g\n", Uin, Uc1m);
	    fflush(stdout);
	    if (tc(Uin, Uc1m, u)) {
		return 1;
	    }
	    printf("<- %g, %g, %g\n", Ith(u,0), Ith(u,1), Ith(u,2));
	}
    }
    N_VDestroy_Serial(u);
    return 0;
}
#endif
