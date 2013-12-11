#ifndef _INTPP_H
#define _INTPP_H 1

typedef double real;
typedef double treal;
//typedef float real;
//typedef float treal;

template<typename M>
struct splinecoeffs {
    real *x0;
    real *xe;
    real *stepi; // 1/h
    int *k;
    int *n;
    int *nmap;
    M **map;
    treal **t;
    treal **c;
    int (*eval)(splinecoeffs *p, real *x, real *res);
};

template<typename M>
struct splinedata {
    splinecoeffs<M> *sc;
    int m;
    int n_input;
    int n_output;
    int n_state;
    const char *func_id;
    template<int K0> static int splev(splinecoeffs<M> *p, real *x, real *res);
    template<int K0> static int splev_pp(splinecoeffs<M> *p, real *x, real *res);
    template<int K0, int K1> static int splev(splinecoeffs<M> *p, real *x, real *res);
    template<int K0, int K1> static int splevgr(splinecoeffs<M> *p, real xi[2], real res[1], real grad[2]);
    template<int K0, int K1, int K2> static int splev(splinecoeffs<M> *p, real *x, real *res);
    template<int K0, int K1, int K2, int K3> static int splev(splinecoeffs<M> *p, real *x, real *res);
    union retval {
	char c[4];
	int i;
    };
};

template<typename M>
class SplineCalc {
  protected:
    splinedata<M> *sd;
    real *s0;
    real *temp;
  public:
    SplineCalc(splinedata<M> *sd_, real *s0_);
    ~SplineCalc();
    void reset();
    void calc(real *in, real *out);
};

//#define CHECK_BOUNDS

#ifdef CHECK_BOUNDS
template<typename M>
void report(splinedata<M> *sd, real *t, int i);
template<typename M>
static inline void check(splinedata<M> *sd, creal *t, int i) { if (i) report(sd, t, i); }
#else
#define check(sd, t, i) i
#endif

#endif /* !_INTPP_H */
