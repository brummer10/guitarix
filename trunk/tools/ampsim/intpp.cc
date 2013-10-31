#include <cstdio>
#include <cstdlib>
#include "intpp.h"

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
template<int K> static void fpbspl(float *t, real x, int l, real *h)
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
    if (k % 2) {
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
    float *cc = p->c[0];
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
    float *cc = p->c[0];
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
    float *cc = p->c[0];
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
    printf("%s:", sd->func_id);
    splinedata::retval cl;
    cl.i = i;
    for (int n = 0; n < 4; n++) {
	if (cl.c[n] < 0) {
	    printf(" %d:L[%g]", n, t[n]);
	} else if (cl.c[n] > 0) {
	    printf(" %d:U[%g]", n, t[n]);
	}
    }
    printf("\n");
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
