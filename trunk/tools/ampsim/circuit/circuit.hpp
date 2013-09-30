#include <nvector/nvector_serial.h>

/* Accessor macro */
#define Ith(v,i)    NV_Ith_S(v,i)   

const int fs = 96000;

struct Dim {
    double lower, upper;
    int size, stride;
    inline double point(int i) { return lower + ((upper-lower) / (size-1)) * i; }
    inline double point(double i) { return lower + ((upper-lower) / (size-1)) * i; }
    inline void index(double v, int& i, double& w) {
	w = (v-lower) / (upper-lower) * (size-1);
	i = static_cast<int>(w);
	if (i < 0) {
	    i = 0;
	    w = 0.0;
	} else if (i > size-2) {
	    i = size-2;
	    w = 1.0;
	} else {
	    w -= i;
	}
    }
};


class Grid {
protected:
    float *grid;		// ndim-dimensional cube
    int vals;			// size of cube cell
    int ndim;			// number of dimensions
    Dim *dim;			// dimension descriptor
    double *weight;		// coordinates inside grid cell
    int *idx;			// index of base point
    int *idx2;			// running index of neighbor nodes
    int p2dim;			// 2^ndim
    double *pts;		// size = p2dim*vals
    inline float *cell(int *ix);
    int calc_strides();
public:
    Grid(int d, Dim *v, int n);
    ~Grid();
};


class ComponentBase;

class Cube: public Grid {
private:
    ComponentBase& cb;
    int mmap_size;
    int n_in;                   // length of input vector
    int fill(int n, int *ix, N_Vector x, N_Vector u0);
public:
    Cube(int d, Dim *v, int n, int *ix, int n_in_, ComponentBase& cb, N_Vector u0, const char* fname=0);
    ~Cube();
    void startvalue(N_Vector x, N_Vector s, N_Vector u);
    int calc(N_Vector x, N_Vector s, N_Vector u);
};


class ComponentBase {
public:
    int NEQ;
    int NDIM;
    int NVALS;
    int N_IN;
    int N_OUT;
    int n_params;
    realtype *params;
    const char **param_names;
    const char **in_names;
    const char **out_names;
    const char **state_names;
    const char **var_names;
    int *ix;
    bool verbose;
    struct UserData {
	realtype *inval;
	realtype *state;
    };
private:
    Dim *ranges;
    Cube *cube;
    UserData user_data;
    static int sfunc(N_Vector x, N_Vector u, void *data);
protected:
    N_Vector constraints;
    realtype& Gco;
    realtype& Gcf;
    realtype& mu;
    realtype& Ex;
    realtype& Kg1;
    realtype& Kg2;
    realtype& Kp;
    realtype& Kvb;
    inline realtype Ig(realtype Ugk);
    inline realtype Ia(realtype Ugk, realtype Uak);
    inline realtype Iap(realtype Ug1k, realtype Ug2k, realtype Uak);
    inline realtype Is(realtype Ug1k, realtype Ug2k);
    static const int param_off = 8;
    inline void set_names(const char **pn, const char **p, int n) {
	while (*p) { *pn++ = *p++; n--; }
	assert(n == 0);
    }
public:
    virtual int func(N_Vector x, N_Vector u, UserData *data) = 0;
    virtual void update(N_Vector y, N_Vector x, N_Vector state) = 0;
    int findzero(realtype *x, realtype *s, N_Vector u);
    int set_range(int i, double lower, double upper, int size);
    void init(N_Vector u0, const char* fname=0);
    int calc(N_Vector x, N_Vector s, N_Vector u);
    void startvalue(N_Vector x, N_Vector s, N_Vector u);
    ComponentBase(int neq, int ndim, int nvals, int n_in, int n_out, int n_params_);
    virtual ~ComponentBase();
};


class TriodeCircuit: public ComponentBase {
private:
    realtype& Ck;

    realtype& G1; // 1/R1
    realtype& G2; // 1/R2
    realtype& Gg; // 1/Rg
    realtype& Gk; // 1/Rk
    realtype& Ga; // 1/Ra
    realtype& Gl; // 1/Rl

    realtype& Un;

    virtual int func(N_Vector u, N_Vector f, UserData *user_data);
    virtual void update(N_Vector y, N_Vector x, N_Vector state);
public:
    TriodeCircuit();
};


class CoupledTriodeCircuit: public ComponentBase {
private:
    realtype& Ck;
    realtype& Ca;
    realtype& Un;
    realtype& G1;
    realtype& G2;
    realtype& Gg;
    realtype& Gk;
    realtype& Ga;
    realtype& G3;
    realtype& Gg2;
    realtype& Gk2;
    realtype& Ga2;
    realtype& Gl;

    virtual int func(N_Vector u, N_Vector f, UserData *user_data);
    virtual void update(N_Vector y, N_Vector x, N_Vector state);
public:
    CoupledTriodeCircuit();
};


class PowerAmpGate: public ComponentBase {
private:
    realtype& C1;
    realtype& G1; // 1/R1
    realtype& Gb; // 1/Rb
    realtype& Gg; // 1/Rg
    realtype& Ub;

    virtual int func(N_Vector u, N_Vector f, UserData *user_data);
    virtual void update(N_Vector y, N_Vector x, N_Vector state);
public:
    PowerAmpGate();
};


class PowerAmpPlate: public ComponentBase {
private:
    realtype& C2;
    realtype& Gd; // 1/Rd
    realtype& Ga; // 1/Ra
    realtype& Gs; // 1/Rs
    realtype& Un;

    virtual int func(N_Vector u, N_Vector f, UserData *user_data);
    virtual void update(N_Vector y, N_Vector x, N_Vector state);
public:
    PowerAmpPlate();
};


class PhaseSplitter: public ComponentBase {
private:
    realtype& C1;
    realtype& C2;
    realtype& C3;
    realtype& Un;
    realtype& G1;
    realtype& Gg1;
    realtype& Gg2;
    realtype& Gk;
    realtype& G2;
    realtype& G3;
    realtype& G4;
    realtype& G5;
    realtype& Ga1;
    realtype& Ga2;
    realtype& Gl1;
    realtype& Gl2;

    virtual int func(N_Vector u, N_Vector f, UserData *user_data);
    virtual void update(N_Vector y, N_Vector x, N_Vector state);
public:
    PhaseSplitter();
    inline void feedback_coeff(realtype *b0, realtype *b1, realtype *a1, realtype pres) {
	realtype R4v = pres/G4;
	realtype B0 = 1/G5;
	realtype B1 = R4v/G5*C3;
	realtype A0 = 1/G3 + 1/G5;
	realtype A1 = C3*R4v/G5 + C3/(G3*G5) + C3/G3*R4v;
	realtype a = A0 + 2*A1*fs;
	*a1 = -(A0 - 2*A1*fs) / a;
	*b0 = (B0 + 2*B1*fs) / a;
	*b1 = (B0 - 2*B1*fs) / a;
    }
};


class Spline {
private:
    int count;
    double x0, step;
    double *c;
    double *f;
public:
    Spline(double *y, int n, double xstart, double h);
    ~Spline();
    double eval(double x);
};
