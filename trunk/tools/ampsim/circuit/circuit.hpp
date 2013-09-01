#include <nvector/nvector_serial.h>

/* Accessor macro */
#define Ith(v,i)    NV_Ith_S(v,i)   

const int fs = 96000;

namespace TriodeCircuit {
    const int NEQ = 3+2;
    const int NDIM = 2;
    const int NVALS = 2;
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
    int set_range_gate(int i, double lower, double upper, int size);
    void init_gate(realtype u0[NEQ_GATE]);
    int tcGate(N_Vector x, N_Vector u);
    int powerampgate(N_Vector x, N_Vector u);
    void updateGate(N_Vector y, N_Vector state);
    const int NEQ_PLATE = 5;
    const int NDIM_PLATE = 3;
    const int NVALS_PLATE = 2;
    int set_range_plate(int i, double lower, double upper, int size);
    void init_plate(realtype u0[NEQ_PLATE]);
    int tcPlate(N_Vector x, N_Vector u);
    int powerampplate(N_Vector x, N_Vector u);
    void updatePlate(N_Vector y, N_Vector state);
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
