#ifndef _INTPP_H
#define _INTPP_H 1

//typedef double real;
typedef float real;

struct splinedata {
    real *x0;
    real *step; // h
    int *k;
    int *n;
    real **t;
    real **c;
    int m;
    int n_input;
    int n_output;
    int n_state;
    int (*eval)(splinedata *p, real *x, real *res);
    const char *func_id;
    static int splev(splinedata *p, real *x, real *res);
    static int splev2(splinedata *p, real *x, real *res);
    static int splev3(splinedata *p, real *x, real *res);
    static int splev4(splinedata *p, real *x, real *res);
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
