#ifndef _INTPP_H
#define _INTPP_H 1

//typedef double real;
typedef float real;

struct splinecoeffs {
    real *x0;
    real *xe;
    real *stepi; // 1/h
    int *n;
    int *nmap;
    unsigned char **map;
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

//#define CHECK_BOUNDS

#ifdef CHECK_BOUNDS
void report(splinedata *sd, real *t, int i);
static inline void check(splinedata *sd, real *t, int i) { if (i) report(sd, t, i); }
#else
#define check(sd, t, i) i
#endif

#endif /* !_INTPP_H */
