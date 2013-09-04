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
    void fill(int n, int *ix, N_Vector x, N_Vector u0);
public:
    Grid(int d, Dim *v, int n);
    ~Grid();
};

class ComponentBase;
typedef int (*vfunc)(N_Vector x, N_Vector u);

class Cube: public Grid {
private:
    vfunc func;//ComponentBase& cb;
    int mmap_size;
    void fill(int n, int *ix, N_Vector x, N_Vector u0);
public:
    Cube(int d, Dim *v, int n, int *ix, vfunc func/*ComponentBase& cb*/, N_Vector u0, const char* fname=0);
    ~Cube();
    int calc(N_Vector x, N_Vector u);
};

class ComponentBase {
public:
    int NEQ;
    int NDIM;
    int NVALS;
    int N_IN;
    int N_OUT;
    int n_params;
    realtype **params;
    const char **param_names;
    const char **in_names;
    const char **out_names;
    const char **state_names;
    int *ix;
private:
    Dim *ranges;
    Cube *cube;
    realtype *user_data;
    static int sfunc(N_Vector x, N_Vector u, void *data);
public:
    virtual int func(N_Vector x, N_Vector u, realtype *user_data) = 0;
    virtual void update(N_Vector y, N_Vector state) = 0;
    int findzero(N_Vector x, N_Vector u);
    int set_range(int i, double lower, double upper, int size);
    void init(realtype *u0);
    int operator()(N_Vector x, N_Vector u);
    ComponentBase(int neq, int ndim, int nvals, int n_in, int n_out, int n_params_);
    ~ComponentBase();
};

class TriodeCircuit_: ComponentBase {
    virtual int func(N_Vector x, N_Vector u);
    virtual void update(N_Vector y, N_Vector state);
public:
    TriodeCircuit_();
    ~TriodeCircuit_();
};

namespace TriodeCircuit {
    const int NEQ = 3+2;
    const int NDIM = 2;
    const int NVALS = 2;
    const int N_IN = 1;
    const int N_OUT = 1;
    const realtype Un = 350;
    extern realtype Gco;
    extern realtype Gcf;
    extern realtype mu;
    extern realtype Ex;
    extern realtype Kg1;
    extern realtype Kp;
    extern realtype Kvb;
    extern realtype Ck;
    extern realtype G1;
    extern realtype G2;
    extern realtype Gg;
    extern realtype Gk;
    extern realtype Ga;
    extern realtype Gl;

    int set_range(int i, double lower, double upper, int size);
    void init(realtype u0[NEQ]);
    int tc(N_Vector x, N_Vector u);
    int triodecircuit(N_Vector x, N_Vector u);
    void update(N_Vector y, N_Vector state);
}

namespace CoupledTriodeCircuit {
    const int NEQ = 7;
    const int NDIM = 3;
    const int NVALS = 3;
    const int N_IN = 1;
    const int N_OUT = 1;
    extern realtype Gco;
    extern realtype Gcf;
    extern realtype mu;
    extern realtype Ex;
    extern realtype Kg1;
    extern realtype Kp;
    extern realtype Kvb;
    extern realtype Ck;
    extern realtype Ca;
    extern realtype Un;
    extern realtype G1;
    extern realtype G2;
    extern realtype Gg;
    extern realtype Gk;
    extern realtype Ga;
    extern realtype G3;
    extern realtype Gg2;
    extern realtype Gk2;
    extern realtype Ga2;
    extern realtype Gl;

    int set_range(int i, double lower, double upper, int size);
    void init(realtype u0[NEQ]);
    int tc(N_Vector x, N_Vector u);
    int coupledtriodecircuit(N_Vector x, N_Vector u);
    void update(N_Vector y, N_Vector state);
}

namespace PowerAmpCircuit {
    const int NEQ_GATE = 3;
    const int NDIM_GATE = 2;
    const int NVALS_GATE = 2;
    const int N_IN_GATE = 1;
    const int N_OUT_GATE = 1;
    int set_range_gate(int i, double lower, double upper, int size);
    void init_gate(realtype u0[NEQ_GATE]);
    int tcGate(N_Vector x, N_Vector u);
    int powerampgate(N_Vector x, N_Vector u);
    void updateGate(N_Vector y, N_Vector state);
    const int NEQ_PLATE = 5;
    const int NDIM_PLATE = 3;
    const int NVALS_PLATE = 2;
    const int N_IN_PLATE = 2;
    const int N_OUT_PLATE = 1;
    int set_range_plate(int i, double lower, double upper, int size);
    void init_plate(realtype u0[NEQ_PLATE]);
    int tcPlate(N_Vector x, N_Vector u);
    int powerampplate(N_Vector x, N_Vector u);
    void updatePlate(N_Vector y, N_Vector state);

    extern realtype Gco;
    extern realtype Gcf;
    extern realtype mu;
    extern realtype Ex;
    extern realtype Kg1;
    extern realtype Kg2;
    extern realtype Kp;
    extern realtype Kvb;

    extern realtype C1;
    extern realtype C2;
    extern realtype Ub;
    extern realtype Un;

    extern realtype G1; // 1/R1
    extern realtype Gb; // 1/Rb
    extern realtype Gg; // 1/Rg
    extern realtype Ga; // 1/Ra
    extern realtype Gs; // 1/Rs
    extern realtype Gd; // 1/Rd
}

namespace PhaseSplitterCircuit {
    extern realtype Gco;
    extern realtype Gcf;
    extern realtype mu;
    extern realtype Ex;
    extern realtype Kg1;
    extern realtype Kp;
    extern realtype Kvb;
    extern realtype C1;
    extern realtype C2;
    extern realtype C3;
    extern realtype Un;
    extern realtype G1;
    extern realtype Gg1;
    extern realtype Gg2;
    extern realtype Gk;
    extern realtype G2;
    extern realtype G3;
    extern realtype G4;
    extern realtype G5;
    extern realtype Ga1;
    extern realtype Ga2;
    extern realtype Gl1;
    extern realtype Gl2;

    const int NEQ = 9;
    const int NDIM = 4;
    const int NVALS = 5;
    const int N_IN = 1;
    const int N_OUT = 2;
    int set_range(int i, double lower, double upper, int size);
    void init(realtype u0[NEQ]);
    int tc(N_Vector x, N_Vector u);
    int phasesplittercircuit(N_Vector x, N_Vector u);
    void update(N_Vector y, N_Vector state);
    inline void feedback_coeff(realtype *b0, realtype *b1, realtype *a1, realtype pres)
    {
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

}

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
