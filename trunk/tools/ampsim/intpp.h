#ifndef _INTPP_H
#define _INTPP_H 1

//typedef double real;
typedef float real;

struct splinedata {
    real *x0;
    real *step; // h
    int *n;
    real **t;
    real **c;
    int m;
    int n_input;
    int n_output;
    int n_state;
    int (*eval)(splinedata *p, real *x, real *res);
    const char *func_id;
    template<int K0> static int splev(splinedata *p, real *x, real *res);
    template<int K0, int K1> static int splev(splinedata *p, real *x, real *res);
    template<int K0, int K1, int K2> static int splev(splinedata *p, real *x, real *res);
    template<int K0, int K1, int K2, int K3> static int splev(splinedata *p, real *x, real *res);
    union retval {
	char c[4];
	int i;
    };
};

class SplineCalc {
  private:
    splinedata *sd;
    real *s0;
    real *temp;
  public:
    SplineCalc(splinedata *sd_, real *s0_);
    ~SplineCalc();
    void reset();
    void calc(real *in, real *out);
};

#endif /* !_INTPP_H */
