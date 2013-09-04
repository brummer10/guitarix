#include <stdio.h>
#include <stdlib.h>
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

#define FTOL   RCONST(1.e-7)  /* function tolerance */
#define STOL   RCONST(1.e-5) /* step tolerance */

#define ZERO   RCONST(0.0)
#define ONE    RCONST(1.0)

/* Private Helper Functions */
static void PrintFinalStats(void *kmem);
static int check_flag(void *flagvalue, const char *funcname, int opt);

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

Cube::Cube(int d, Dim *v, int n, int *ix, vfunc f/*ComponentBase& cb_*/, N_Vector u0, const char *fname)
    : Grid(d, v, n),
      func(f)/*cb(cb_)*/,
      mmap_size(0) {
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

void Cube::fill(int n, int *ix, N_Vector x, N_Vector u0)
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
	    func(x,u);//cb.findzero(x, u);
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
}

int Cube::calc(N_Vector x, N_Vector u)
{
    for (int i = 0; i < ndim; i++) {
	dim[i].index(Ith(x,i),idx[i],weight[i]);
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
    return func(x,u);//cb.findzero(x, u);
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
      params(new realtype*[n_params_]),
      param_names(new const char*[n_params_]),
      in_names(new const char*[n_in]),
      out_names(new const char*[n_out]),
      state_names(new const char*[nvals-n_out]),
      ix(new int[ndim]),
      ranges(new Dim[ndim]),
      cube(0),
      user_data(0) {
}
      
ComponentBase::~ComponentBase() {
    delete[] params;
    delete[] param_names;
    delete[] in_names;
    delete[] out_names;
    delete[] state_names;
    delete[] ix;
    delete[] ranges;
    delete cube;
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

void ComponentBase::init(realtype *u0) {
    N_Vector u = N_VNew_Serial(NEQ);
    for (int i = 0; i < NEQ; i++) {
	Ith(u,i) = u0[i];
    }
    delete cube;
    //cube = new Cube(NDIM, ranges, NEQ, ix, *this, u);
    N_VDestroy_Serial(u);
}

//static
int ComponentBase::sfunc(N_Vector x, N_Vector u, void *data) {
    ComponentBase *self = static_cast<ComponentBase*>(data);
    return self->func(x, u, self->user_data);
}

int ComponentBase::findzero(N_Vector x, N_Vector u) {
    int flag;

    N_Vector s = N_VNew_Serial(NEQ);
    if (check_flag((void *)s, "N_VNew_Serial", 0)) return(1);
    N_VConst_Serial(ONE,s); /* no scaling */

    realtype fnormtol = FTOL;
    realtype scsteptol = STOL;

    void *kmem = KINCreate();
    if (check_flag((void *)kmem, "KINCreate", 0)) return(1);

    user_data = NV_DATA_S(x);
    flag = KINSetUserData(kmem, user_data);
    if (check_flag(&flag, "KINSetUserData", 1)) return(1);

    // N_Vector c = N_VNew_Serial(NEQ);
    // if (check_flag((void *)c, "N_VNew_Serial", 0)) return(1);
    // Ith(c,0) =  ZERO;   /* no constraint on f1 */
    // Ith(c,1) =  ZERO;   /* no constraint on f2 */
    // Ith(c,2) =  ZERO;   /* no constraint on f3 */
    // Ith(c,3) =  ONE;    /* l = Ua - Uk >= 0 */
    // Ith(c,4) = -ONE;    /* L = Ua - Un <= 0 */
    // flag = KINSetConstraints(kmem, c);
    // if (check_flag(&flag, "KINSetConstraints", 1)) return(1);
    // N_VDestroy_Serial(c);

    flag = KINSetFuncNormTol(kmem, fnormtol);
    if (check_flag(&flag, "KINSetFuncNormTol", 1)) return(1);
    flag = KINSetScaledStepTol(kmem, scsteptol);
    if (check_flag(&flag, "KINSetScaledStepTol", 1)) return(1);

    flag = KINInit(kmem, sfunc, u);
    if (check_flag(&flag, "KINInit", 1)) return(1);

    /* Call KINDense to specify the linear solver */

    flag = KINDense(kmem, NEQ);
    if (check_flag(&flag, "KINDense", 1)) return(1);

    //flag = KINSetPrintLevel(kmem, 3); 
    //if (check_flag(&flag, "KINSetPrintLevel", 1)) return(1);

    int glstr = KIN_NONE;
    //int glstr = KIN_LINESEARCH;
    int mset = 1;
    flag = KINSetMaxSetupCalls(kmem, mset);
    if (check_flag(&flag, "KINSetMaxSetupCalls", 1)) return(1);
    flag = KINSol(kmem, u, glstr, s, s);
    if (flag > 1) {
	printf("res = %d\n", flag);
	return 1;
    }
    if (check_flag(&flag, "KINSol", 1)) return(1);
    //PrintFinalStats(kmem);

    N_VDestroy_Serial(s);
    KINFree(&kmem);
    user_data = 0;
    return 0;
}

int ComponentBase::operator()(N_Vector x, N_Vector u) {
    return cube->calc(x, u);
}

/*
 *--------------------------------------------------------------------
 * FUNCTIONS CALLED BY KINSOL
 *--------------------------------------------------------------------
 */

namespace TriodeCircuit {

    realtype Gco = -0.2;
    realtype Gcf = 1e-5;
    realtype mu  = 100.0;
    realtype Ex  = 1.4;
    realtype Kg1 = 1060.0;
    realtype Kp  = 600.0;
    realtype Kvb = 300.0;

    realtype Ck  = 680e-9;

    realtype G1  = 1/68e3;  // 1/R1
    realtype G2  = 1/1e0;   // 1/R2
    realtype Gg  = 1/1e6;   // 1/Rg
    realtype Gk  = 1/2.7e3; // 1/Rk
    realtype Ga  = 1/100e3; // 1/Ra
    realtype Gl  = 1/4e6;   // 1/Rl

    typedef struct {
	realtype Uin;
	realtype Uc1m;
    } *UserData;

    inline realtype Ig(realtype Ugk)
    {
	if (Ugk < Gco) {
	    return ZERO;
	}
	return Gcf*pow(Ugk-Gco,1.5);
    }

    inline realtype Ia(realtype Ugk, realtype Uak)
    {
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

    static int func(N_Vector u, N_Vector f, void *user_data)
    {
	realtype *udata = NV_DATA_S(u);
	realtype *fdata = NV_DATA_S(f);

	//printf("-> %g,%g,%g,%g,%g\n", Ith(u,0), Ith(u,1), Ith(u,2), Ith(u,3), Ith(u,4));
	realtype Ug = udata[0];
	realtype Uk = udata[1];
	realtype Ua = udata[2];
	realtype l  = udata[3];
	realtype L  = udata[4];
	realtype Uc = Uk;

	UserData data = (UserData)user_data;
	realtype Uin = data->Uin;
	realtype Uc1m = data->Uc1m;

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

    void update(N_Vector y, N_Vector state)
    {
	realtype *fdata = NV_DATA_S(y);
	realtype Ug = fdata[0];
	realtype Uk = fdata[1];
	realtype Ua = fdata[2];
	realtype Uc1m = Ith(state,0);
	Uc1m = Uc1m - (Uk*Gk - Ia(Ug-Uk,Ua-Uk) - Ig(Ug-Uk)) / (Ck*fs);
	Ith(state,0) = Uc1m;
    }

    int tc(N_Vector x, N_Vector u)
    {
	int flag;

	N_Vector s = N_VNew_Serial(NEQ);
	if (check_flag((void *)s, "N_VNew_Serial", 0)) return(1);
	N_VConst_Serial(ONE,s); /* no scaling */

	realtype fnormtol = FTOL;
	realtype scsteptol = STOL;

	void *kmem = KINCreate();
	if (check_flag((void *)kmem, "KINCreate", 0)) return(1);

	UserData data = (UserData)malloc(sizeof *data);
	flag = KINSetUserData(kmem, data);
	if (check_flag(&flag, "KINSetUserData", 1)) return(1);

	N_Vector c = N_VNew_Serial(NEQ);
	if (check_flag((void *)c, "N_VNew_Serial", 0)) return(1);
	Ith(c,0) =  ZERO;   /* no constraint on f1 */
	Ith(c,1) =  ZERO;   /* no constraint on f2 */
	Ith(c,2) =  ZERO;   /* no constraint on f3 */
	Ith(c,3) =  ONE;    /* l = Ua - Uk >= 0 */
	Ith(c,4) = -ONE;    /* L = Ua - Un <= 0 */
	flag = KINSetConstraints(kmem, c);
	if (check_flag(&flag, "KINSetConstraints", 1)) return(1);
	N_VDestroy_Serial(c);

	flag = KINSetFuncNormTol(kmem, fnormtol);
	if (check_flag(&flag, "KINSetFuncNormTol", 1)) return(1);
	flag = KINSetScaledStepTol(kmem, scsteptol);
	if (check_flag(&flag, "KINSetScaledStepTol", 1)) return(1);

	flag = KINInit(kmem, func, u);
	if (check_flag(&flag, "KINInit", 1)) return(1);

	/* Call KINDense to specify the linear solver */

	flag = KINDense(kmem, NEQ);
	if (check_flag(&flag, "KINDense", 1)) return(1);

	//flag = KINSetPrintLevel(kmem, 3); 
	//if (check_flag(&flag, "KINSetPrintLevel", 1)) return(1);

	int glstr = KIN_NONE;
	//int glstr = KIN_LINESEARCH;
	int mset = 1;
	data->Uin = Ith(x,0);
	data->Uc1m = Ith(x,1);
	flag = KINSetMaxSetupCalls(kmem, mset);
	if (check_flag(&flag, "KINSetMaxSetupCalls", 1)) return(1);
	flag = KINSol(kmem, u, glstr, s, s);
	if (flag > 1) {
	    printf("res = %d\n", flag);
	    return 1;
	}
	if (check_flag(&flag, "KINSol", 1)) return(1);
	//PrintFinalStats(kmem);

	N_VDestroy_Serial(s);
	KINFree(&kmem);
	free(data);
	return 0;
    }

    static Dim vtriode[NDIM] = {{-40.0, 40.0, 2}, {-15.0, 15.0, 2}};
    static Cube *cube = 0;

    int set_range(int i, double lower, double upper, int size)
    {
	if (i > NDIM) {
	    return 0;
	}
	vtriode[i].lower = lower;
	vtriode[i].upper = upper;
	vtriode[i].size = size;
	return 1;
    }

    void init(realtype u0[NEQ])
    {
	N_Vector u = N_VNew_Serial(NEQ);
	for (int i = 0; i < NEQ; i++) {
	    Ith(u,i) = u0[i];
	}
	delete cube;
	int ix[NDIM] = {1,0};
	cube = new Cube(NDIM, vtriode, NEQ, ix, tc, u);
	N_VDestroy_Serial(u);
    }

    int triodecircuit(N_Vector x, N_Vector u)
    {
	return cube->calc(x, u);
    }

} // TriodeCircuit

namespace CoupledTriodeCircuit {

    realtype Gco = -0.2;
    realtype Gcf = 1e-5;
    realtype mu  = 100.0;
    realtype Ex  = 1.4;
    realtype Kg1 = 1060.0;
    realtype Kp  = 600.0;
    realtype Kvb = 300.0;

    realtype Ck = 680e-9;
    realtype Ca = 22e-9;
    realtype Un = 350;

    realtype G1 = 1/68e3;   // 1/R1
    realtype G2 = 1/1e0;    // 1/R2
    realtype Gg = 1/1e6;    // 1/Rg
    realtype Gk = 1/2.7e3;  // 1/Rk
    realtype Ga = 1/100e3;  // 1/Ra
    realtype G3 = 1/470e3;  // 1/R3
    realtype Gg2 = 1/1e6;   // 1/Rg2
    realtype Gk2 = 1/10e3;  // 1/Rk2
    realtype Ga2 = 1/100e3; // 1/Ra2
    realtype Gl = 1/4e6;    // 1/Rl

    typedef struct {
	realtype Uin;
	realtype Uc1m;
	realtype Uc2m;
    } *UserData;

    inline realtype Ig(realtype Ugk)
    {
	if (Ugk < Gco) {
	    return ZERO;
	}
	return Gcf*pow(Ugk-Gco,1.5);
    }

    inline realtype Ia(realtype Ugk, realtype Uak)
    {
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

    int func(N_Vector u, N_Vector f, void *user_data)
    {
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

	UserData data = (UserData)user_data;
	realtype Uin = data->Uin;
	realtype Uc1m = data->Uc1m;
	realtype Uc2m = data->Uc2m;

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

    void update(N_Vector y, N_Vector state)
    {
	realtype *fdata = NV_DATA_S(y);
	realtype Ug = fdata[0];
	realtype Uk = fdata[1];
	realtype Ua = fdata[2];
	realtype U2 = fdata[3];
	realtype Ug2 = fdata[4];
	realtype Uc1m = Ith(state,0);
	realtype Uc2m = Ith(state,1);

	realtype ia1 = Ia(Ug-Uk,Ua-Uk);
	realtype ig1 = Ig(Ug-Uk);
	Uc1m = Uc1m - (Uk*Gk-ia1-ig1) / (Ck*fs);
	Uc2m = Uc2m + ((U2-Ug2)*G3) / (Ca*fs);

	Ith(state,0) = Uc1m;
	Ith(state,1) = Uc2m;
    }

    int tc(N_Vector x, N_Vector u)
    {
	int flag;

	N_Vector s = N_VNew_Serial(NEQ);
	if (check_flag((void *)s, "N_VNew_Serial", 0)) return(1);
	N_VConst_Serial(ONE,s); /* no scaling */

	realtype fnormtol = FTOL;
	realtype scsteptol = STOL;

	void *kmem = KINCreate();
	if (check_flag((void *)kmem, "KINCreate", 0)) return(1);

	UserData data = (UserData)malloc(sizeof *data);
	flag = KINSetUserData(kmem, data);
	if (check_flag(&flag, "KINSetUserData", 1)) return(1);

	// N_Vector c = N_VNew_Serial(NEQ);
	// if (check_flag((void *)c, "N_VNew_Serial", 0)) return(1);
	// Ith(c,0) =  ZERO;   /* no constraint on f1 */
	// Ith(c,1) =  ZERO;   /* no constraint on f2 */
	// Ith(c,2) =  ZERO;   /* no constraint on f3 */
	// Ith(c,3) =  ONE;    /* l = Ua - Uk >= 0 */
	// Ith(c,4) = -ONE;    /* L = Ua - Un <= 0 */
	// flag = KINSetConstraints(kmem, c);
	// if (check_flag(&flag, "KINSetConstraints", 1)) return(1);
	// N_VDestroy_Serial(c);

	flag = KINSetFuncNormTol(kmem, fnormtol);
	if (check_flag(&flag, "KINSetFuncNormTol", 1)) return(1);
	flag = KINSetScaledStepTol(kmem, scsteptol);
	if (check_flag(&flag, "KINSetScaledStepTol", 1)) return(1);

	flag = KINInit(kmem, func, u);
	if (check_flag(&flag, "KINInit", 1)) return(1);

	/* Call KINDense to specify the linear solver */

	flag = KINDense(kmem, NEQ);
	if (check_flag(&flag, "KINDense", 1)) return(1);

	//flag = KINSetPrintLevel(kmem, 3); 
	//if (check_flag(&flag, "KINSetPrintLevel", 1)) return(1);

	int glstr = KIN_NONE;
	//int glstr = KIN_LINESEARCH;
	int mset = 1;
	data->Uin = Ith(x,0);
	data->Uc1m = Ith(x,1);
	data->Uc2m = Ith(x,2);
	flag = KINSetMaxSetupCalls(kmem, mset);
	if (check_flag(&flag, "KINSetMaxSetupCalls", 1)) return(1);
	flag = KINSol(kmem, u, glstr, s, s);
	if (flag > 1) {
	    printf("res = %d\n", flag);
	    return 1;
	}
	if (check_flag(&flag, "KINSol", 1)) return(1);
	//PrintFinalStats(kmem);

	N_VDestroy_Serial(s);
	KINFree(&kmem);
	free(data);
	return 0;
    }

    static Dim vtriode[NDIM] = {{-20.0, 20.0, 80}, {0.0, 10.0, 30}, {100.0, 350.0, 8}};
    static Cube *cube = 0;

    int set_range(int i, double lower, double upper, int size)
    {
	if (i > NDIM) {
	    return 0;
	}
	vtriode[i].lower = lower;
	vtriode[i].upper = upper;
	vtriode[i].size = size;
	return 1;
    }

    void init(realtype u0[NEQ])
    {
	N_Vector u = N_VNew_Serial(NEQ);
	for (int i = 0; i < NEQ; i++) {
	    Ith(u,i) = u0[i];
	}
	delete cube;
	int ix[NDIM] = {2,1,0};
	cube = new Cube(NDIM, vtriode, NEQ, ix, tc, u);
	N_VDestroy_Serial(u);
    }

    int coupledtriodecircuit(N_Vector x, N_Vector u)
    {
	return cube->calc(x, u);
    }

} // CoupledTriodeCircuit

namespace PowerAmpCircuit {

    realtype Gco = -0.2;
    realtype Gcf = 1e-5;
    realtype mu  = 8.7;
    realtype Ex  = 1.35;
    realtype Kg1 = 1460.0;
    realtype Kg2 = 4500.0;
    realtype Kp  = 48.0;
    realtype Kvb = 12.0;

    realtype C1 = 22e-9;
    realtype C2 = 100e-6;
    realtype Ub = -50;
    realtype Un = 450;

    realtype G1 = 1/30e3;  // 1/R1
    realtype Gb = 1/220e3; // 1/Rb
    realtype Gg = 1/5e3;   // 1/Rg
    realtype Ga = 1/1.7e3; // 1/Ra
    realtype Gs = 1/1e3;   // 1/Rs
    realtype Gd = 1/500;   // 1/Rd

    inline realtype Ig(realtype Ugk)
    {
	if (Ugk < Gco) {
	    return ZERO;
	}
	return Gcf*pow(Ugk-Gco,1.5);
    }

    inline realtype Ia(realtype Ug1k, realtype Ug2k, realtype Uak)
    {
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

    inline realtype Is(realtype Ug1k, realtype Ug2k)
    {
	realtype t = Ug2k/mu+Ug1k;
	if (t < 0) {
	    return ZERO;
	}
	return exp(Ex*log(t))/Kg2;
    }

    typedef struct {
	realtype Uin;
	realtype Uc1m;
    } *UserDataGate;

    static int funcGate(N_Vector u, N_Vector f, void *user_data)
    {
	realtype *udata = NV_DATA_S(u);
	realtype *fdata = NV_DATA_S(f);

	realtype U0 = udata[0];
	realtype U1 = udata[1];
	realtype Ug = udata[2];
	realtype Uc1 = U0 - U1;

	UserDataGate data = (UserDataGate)user_data;
	realtype Uin = data->Uin;
	realtype Uc1m = data->Uc1m;

	fdata[0] = C1*(Uc1-Uc1m)*fs-(Uin-U0)*G1;
	fdata[1] = (Uin-U0)*G1-(U1-Ub)*Gb-(U1-Ug)*Gg;
	fdata[2] = (U1-Ug)*Gg-Ig(Ug);

	return(0);
    }

    void updateGate(N_Vector y, N_Vector state)
    {
	realtype *fdata = NV_DATA_S(y);
	realtype U1 = fdata[1];
	realtype Ug = fdata[2];
	realtype Uc1m = Ith(state,0);

	Uc1m = Uc1m + ((U1-Ub)*Gb+(U1-Ug)*Gg)/(C1*fs);

	Ith(state,0) = Uc1m;
    }

    int tcGate(N_Vector x, N_Vector u)
    {
	int flag;

	N_Vector s = N_VNew_Serial(NEQ_GATE);
	if (check_flag((void *)s, "N_VNew_Serial", 0)) return(1);
	N_VConst_Serial(ONE,s); /* no scaling */

	realtype fnormtol = FTOL;
	realtype scsteptol = STOL;

	void *kmem = KINCreate();
	if (check_flag((void *)kmem, "KINCreate", 0)) return(1);

	UserDataGate data = (UserDataGate)malloc(sizeof *data);
	flag = KINSetUserData(kmem, data);
	if (check_flag(&flag, "KINSetUserData", 1)) return(1);

	//N_Vector c = N_VNew_Serial(NEQ);
	//if (check_flag((void *)c, "N_VNew_Serial", 0)) return(1);
	//Ith(c,0) =  ZERO;   /* no constraint on f1 */
	//Ith(c,1) =  ZERO;   /* no constraint on f2 */
	//Ith(c,2) =  ZERO;   /* no constraint on f3 */
	//Ith(c,3) =  ONE;    /* l = Ua - Uk >= 0 */
	//Ith(c,4) = -ONE;    /* L = Ua - Un <= 0 */
	//flag = KINSetConstraints(kmem, c);
	//if (check_flag(&flag, "KINSetConstraints", 1)) return(1);
	//N_VDestroy_Serial(c);

	flag = KINSetFuncNormTol(kmem, fnormtol);
	if (check_flag(&flag, "KINSetFuncNormTol", 1)) return(1);
	flag = KINSetScaledStepTol(kmem, scsteptol);
	if (check_flag(&flag, "KINSetScaledStepTol", 1)) return(1);

	flag = KINInit(kmem, funcGate, u);
	if (check_flag(&flag, "KINInit", 1)) return(1);

	/* Call KINDense to specify the linear solver */

	flag = KINDense(kmem, NEQ_GATE);
	if (check_flag(&flag, "KINDense", 1)) return(1);

	//flag = KINSetPrintLevel(kmem, 3); 
	//if (check_flag(&flag, "KINSetPrintLevel", 1)) return(1);

	int glstr = KIN_NONE; // KIN_LINESEARCH;
	int mset = 1;
	data->Uin = Ith(x,0);
	data->Uc1m = Ith(x,1);
	flag = KINSetMaxSetupCalls(kmem, mset);
	if (check_flag(&flag, "KINSetMaxSetupCalls", 1)) return(1);
	fflush(stdout);
	flag = KINSol(kmem, u, glstr, s, s);
	if (flag > 1) {
	    printf("res = %d\n", flag);
	    return 1;
	}
	if (check_flag(&flag, "KINSol", 1)) return(1);
	//PrintFinalStats(kmem);

	N_VDestroy_Serial(s);
	KINFree(&kmem);
	free(data);
	return 0;
    }

    static Dim vtriodeGate[NDIM_GATE] = {{-200,200,41},{-70,170,8}};
    static Cube *cubeGate = 0;

    int set_range_gate(int i, double lower, double upper, int size)
    {
	if (i > NDIM_GATE) {
	    return 0;
	}
	vtriodeGate[i].lower = lower;
	vtriodeGate[i].upper = upper;
	vtriodeGate[i].size = size;
	return 1;
    }

    void init_gate(realtype u0[NEQ_GATE])
    {
	N_Vector u = N_VNew_Serial(NEQ_GATE);
	for (int i = 0; i < NEQ_GATE; i++) {
	    Ith(u,i) = u0[i];
	}
	delete cubeGate;
	int ix[NDIM_GATE] = {1,0};
	cubeGate = new Cube(NDIM_GATE, vtriodeGate, NEQ_GATE, ix, tcGate, u);
	N_VDestroy_Serial(u);
    }

    int powerampgate(N_Vector x, N_Vector u)
    {
	return cubeGate->calc(x, u);
    }

    typedef struct {
	realtype Ug1;
	realtype Ug2;
	realtype Uc2m;
    } *UserDataPlate;

    static int funcPlate(N_Vector u, N_Vector f, void *user_data)
    {
	realtype *udata = NV_DATA_S(u);
	realtype *fdata = NV_DATA_S(f);

	realtype Us1 = udata[0];
	realtype Us2 = udata[1];
	realtype Ud  = udata[2];
	realtype Ua1 = udata[3];
	realtype Ua2 = udata[4];
	realtype Uc2 = Ud;

	UserDataPlate data = (UserDataPlate)user_data;
	realtype Ug1 = data->Ug1;
	realtype Ug2 = data->Ug2;
	realtype Uc2m = data->Uc2m;

	realtype ia1 = Ia(Ug1,Us1,Ua1);
	realtype is1 = Is(Ug1,Us1);
	realtype ia2 = Ia(Ug2,Us2,Ua2);
	realtype is2 = Is(Ug2,Us2);
	fdata[0] = -ia1+(Ud-Ua1)*Ga;
	fdata[1] = -ia2+(Ud-Ua2)*Ga;
	fdata[2] = -is1+(Ud-Us1)*Gs;
	fdata[3] = -is2+(Ud-Us2)*Gs;
	fdata[4] = -ia1-ia2-is1-is2+(Un-Ud)*Gd-C2*(Uc2-Uc2m)*fs;

	return(0);
    }

    void updatePlate(N_Vector y, N_Vector state)
    {
	realtype *fdata = NV_DATA_S(y);
	realtype Us1 = fdata[0];
	realtype Us2 = fdata[1];
	//realtype Ud  = fdata[2]; // unused
	realtype Ua1 = fdata[3];
	realtype Ua2 = fdata[4];
	realtype Ug1 = Ith(state,0);
	realtype Ug2 = Ith(state,1);
	realtype Uc2m = Ith(state,2);
	realtype ia1 = Ia(Ug1,Us1,Ua1);
	realtype is1 = Is(Ug1,Us1);
	realtype ia2 = Ia(Ug2,Us2,Ua2);
	realtype is2 = Is(Ug2,Us2);

	Uc2m = Uc2m + ((Un-Uc2m)*Gd-(ia1+ia2+is1+is2))/(C2*fs);

	Ith(state,2) = Uc2m;
    }

    int tcPlate(N_Vector x, N_Vector u)
    {
	int flag;

	N_Vector s = N_VNew_Serial(NEQ_PLATE);
	if (check_flag((void *)s, "N_VNew_Serial", 0)) return(1);
	N_VConst_Serial(ONE,s); /* no scaling */

	realtype fnormtol = FTOL;
	realtype scsteptol = STOL;

	void *kmem = KINCreate();
	if (check_flag((void *)kmem, "KINCreate", 0)) return(1);

	UserDataPlate data = (UserDataPlate)malloc(sizeof *data);
	flag = KINSetUserData(kmem, data);
	if (check_flag(&flag, "KINSetUserData", 1)) return(1);

	//N_Vector c = N_VNew_Serial(NEQ);
	//if (check_flag((void *)c, "N_VNew_Serial", 0)) return(1);
	//Ith(c,0) =  ZERO;   /* no constraint on f1 */
	//Ith(c,1) =  ZERO;   /* no constraint on f2 */
	//Ith(c,2) =  ZERO;   /* no constraint on f3 */
	//Ith(c,3) =  ONE;    /* l = Ua - Uk >= 0 */
	//Ith(c,4) = -ONE;    /* L = Ua - Un <= 0 */
	//flag = KINSetConstraints(kmem, c);
	//if (check_flag(&flag, "KINSetConstraints", 1)) return(1);
	//N_VDestroy_Serial(c);

	flag = KINSetFuncNormTol(kmem, fnormtol);
	if (check_flag(&flag, "KINSetFuncNormTol", 1)) return(1);
	flag = KINSetScaledStepTol(kmem, scsteptol);
	if (check_flag(&flag, "KINSetScaledStepTol", 1)) return(1);

	flag = KINInit(kmem, funcPlate, u);
	if (check_flag(&flag, "KINInit", 1)) return(1);

	/* Call KINDense to specify the linear solver */

	flag = KINDense(kmem, NEQ_PLATE);
	if (check_flag(&flag, "KINDense", 1)) return(1);

	//flag = KINSetPrintLevel(kmem, 3); 
	//if (check_flag(&flag, "KINSetPrintLevel", 1)) return(1);

	int glstr = KIN_NONE; // KIN_LINESEARCH;
	int mset = 1;
	data->Ug1 = Ith(x,0);
	data->Ug2 = Ith(x,1);
	data->Uc2m = Ith(x,2);
	flag = KINSetMaxSetupCalls(kmem, mset);
	if (check_flag(&flag, "KINSetMaxSetupCalls", 1)) return(1);
	fflush(stdout);
	flag = KINSol(kmem, u, glstr, s, s);
	if (flag > 1) {
	    printf("res = %d\n", flag);
	    return 1;
	}
	if (check_flag(&flag, "KINSol", 1)) return(1);
	//PrintFinalStats(kmem);

	N_VDestroy_Serial(s);
	KINFree(&kmem);
	free(data);
	return 0;
    }

    static Dim vtriodePlate[NDIM_PLATE] = {{-200,200,41},{-200,200,41},{350.0,450.0,2}};
    static Cube *cubePlate = 0;

    int set_range_plate(int i, double lower, double upper, int size)
    {
	if (i > NDIM_PLATE) {
	    return 0;
	}
	vtriodePlate[i].lower = lower;
	vtriodePlate[i].upper = upper;
	vtriodePlate[i].size = size;
	return 1;
    }

    void init_plate(realtype u0[NEQ_PLATE])
    {
	N_Vector u = N_VNew_Serial(NEQ_PLATE);
	for (int i = 0; i < NEQ_PLATE; i++) {
	    Ith(u,i) = u0[i];
	}
	delete cubePlate;
	int ix[NDIM_PLATE] = {2,1,0};
	cubePlate = new Cube(NDIM_PLATE, vtriodePlate, NEQ_PLATE, ix, tcPlate, u);
	N_VDestroy_Serial(u);
    }

    int powerampplate(N_Vector x, N_Vector u)
    {
	return cubePlate->calc(x, u);
    }

} // PowerAmpCircuit

namespace PhaseSplitterCircuit {

    realtype Gco = RCONST(-0.2);
    realtype Gcf = RCONST(1e-5);
    realtype mu  = RCONST(100.0);
    realtype Ex  = RCONST(1.4);
    realtype Kg1 = RCONST(1060.0);
    realtype Kp  = RCONST(600.0);
    realtype Kvb = RCONST(300.0);

    realtype C1  = RCONST(100e-9); // corrected from 100e-6
    realtype C2  = RCONST(100e-9); // corrected from 100e-6
    realtype C3  = RCONST(100e-9); // corrected from 100e-6
    realtype Un  = RCONST(400);

    realtype G1  = 1/1e0;     // 1/R1
    realtype Gg1 = 1/1e6;     // 1/Rg1
    realtype Gg2 = 1/1e6;     // 1/Rg2
    realtype Gk  = 1/470e0;   // 1/Rk
    realtype G2  = 1/10e3;    // 1/R2
    realtype G3  = 1/100e3;   // 1/R3
    realtype G4  = 1/22e3;    // 1/R4
    realtype G5  = 1/4.7e3;   // 1/R5
    realtype Ga1 = 1/82e3;    // 1/Ra1
    realtype Ga2 = 1/100e3;   // 1/Ra2
    realtype Gl1 = 1/4e6;     // 1/Rl1
    realtype Gl2 = 1/4e6;     // 1/Rl2

    typedef struct {
	realtype Uin;
	realtype Uc1m;
	realtype Uc2m;
	realtype Uc3m;
    } *UserData;

    inline realtype Ig(realtype Ugk)
    {
	if (Ugk < Gco) {
	    return ZERO;
	}
	return Gcf*pow(Ugk-Gco,1.5);
    }

    inline realtype Ia(realtype Ugk, realtype Uak)
    {
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

    static int func(N_Vector u, N_Vector f, void *user_data)
    {
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

	UserData data = (UserData)user_data;
	realtype Uin = data->Uin;
	realtype Uc1m = data->Uc1m;
	realtype Uc2m = data->Uc2m;
	realtype Uc3m = data->Uc3m;

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

    void update(N_Vector y, N_Vector state)
    {
	realtype *fdata = NV_DATA_S(y);
	realtype Ug1 = fdata[1];
	realtype Uk  = fdata[2];
	realtype U2  = fdata[4];
	realtype U4  = fdata[6];
	realtype Ug2 = fdata[7];
	realtype Uc1m = Ith(state,0);
	realtype Uc2m = Ith(state,1);
	realtype Uc3m = Ith(state,2);
	realtype ig1 = Ig(Ug1-Uk);
	realtype ig2 = Ig(Ug2-Uk);
	Uc1m = Uc1m + ((Ug1-U2)*Gg1+ig1) / (C1*fs);
	Uc2m = Uc2m - ((Ug2-U2)*Gg2+ig2) / (C2*fs);
	Uc3m = Uc3m + (U4*G4) / (C3*fs);
	Ith(state,0) = Uc1m;
	Ith(state,1) = Uc2m;
	Ith(state,2) = Uc3m;
    }

    int tc(N_Vector x, N_Vector u)
    {
	int flag;

	N_Vector s = N_VNew_Serial(NEQ);
	if (check_flag((void *)s, "N_VNew_Serial", 0)) return(1);
	N_VConst_Serial(ONE,s); /* no scaling */

	realtype fnormtol = FTOL;
	realtype scsteptol = STOL;

	void *kmem = KINCreate();
	if (check_flag((void *)kmem, "KINCreate", 0)) return(1);

	UserData data = (UserData)malloc(sizeof *data);
	flag = KINSetUserData(kmem, data);
	if (check_flag(&flag, "KINSetUserData", 1)) return(1);

	flag = KINSetFuncNormTol(kmem, fnormtol);
	if (check_flag(&flag, "KINSetFuncNormTol", 1)) return(1);
	flag = KINSetScaledStepTol(kmem, scsteptol);
	if (check_flag(&flag, "KINSetScaledStepTol", 1)) return(1);

	flag = KINInit(kmem, func, u);
	if (check_flag(&flag, "KINInit", 1)) return(1);

	/* Call KINDense to specify the linear solver */

	flag = KINDense(kmem, NEQ);
	if (check_flag(&flag, "KINDense", 1)) return(1);

	//flag = KINSetPrintLevel(kmem, 3); 
	//if (check_flag(&flag, "KINSetPrintLevel", 1)) return(1);

	int glstr = KIN_NONE;
	//int glstr = KIN_LINESEARCH;
	int mset = 1;
	data->Uin = Ith(x,0);
	data->Uc1m = Ith(x,1);
	data->Uc2m = Ith(x,2);
	data->Uc3m = Ith(x,3);
	flag = KINSetMaxSetupCalls(kmem, mset);
	if (check_flag(&flag, "KINSetMaxSetupCalls", 1)) return(1);
	fflush(stdout);
	flag = KINSol(kmem, u, glstr, s, s);
	if (flag > 1) {
	    printf("res = %d\n", flag);
	    return 1;
	}
	if (check_flag(&flag, "KINSol", 1)) return(1);
	//PrintFinalStats(kmem);

	N_VDestroy_Serial(s);
	KINFree(&kmem);
	free(data);
	return 0;
    }

    static Dim vtriode[NDIM] = {{-40.0, 40.0, 30}, {-31.0, -30.0, 2}, {30.0, 31.0, 2}, {0.13, 0.15, 3}};
    static Cube *cube = 0;

    int set_range(int i, double lower, double upper, int size)
    {
	if (i > NDIM) {
	    return 0;
	}
	vtriode[i].lower = lower;
	vtriode[i].upper = upper;
	vtriode[i].size = size;
	return 1;
    }

    void init(realtype u0[NEQ])
    {
	N_Vector u = N_VNew_Serial(NEQ);
	for (int i = 0; i < NEQ; i++) {
	    Ith(u,i) = u0[i];
	}
	delete cube;
	int ix[NDIM] = {3,2,1,0};
	cube = new Cube(NDIM, vtriode, NEQ, ix, tc, u);
	N_VDestroy_Serial(u);
    }

    int phasesplittercircuit(N_Vector x, N_Vector u)
    {
	return cube->calc(x, u);
    }

} // PhaseSplitterCircuit

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

/*
 *--------------------------------------------------------------------
 * PRIVATE FUNCTIONS
 *--------------------------------------------------------------------
 */

/* 
 * Print final statistics contained in iopt 
 */
#if 0
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
#endif

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
