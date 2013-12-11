#include <cstdio>
#include <cstdlib>

#ifndef NO_INTPP_INCLUDES
#include "intpp.h"
#include "intpp_inst.cc"
#endif

#define always_inline inline __attribute__((always_inline))

/****************************************************************
 ** fpbspl evaluates the k non-zero b-splines of order k
 ** at t[0] <= x < t[1] using the stable recurrence relation
 ** of de boor and cox.
 **
 ** t: knot array
 ** K: order (> 0)
 ** h[K]: output array
 */
template<int K> static always_inline void fpbspl(treal *t, real x, real *h)
{
    real hh[K-1];
    h[0] = 1;
    for (int j = 0; j < K-1; j++) {
	for (int i = 0; i <= j; i++) {
	    hh[i] = h[i];
	}
	h[0] = 0;
	for (int i = 0; i <= j; i++) {
	    int li = i+1;
	    int lj = i-j;
	    real f = hh[i]/(t[li]-t[lj]);
	    h[i] = h[i]+f*(t[li]-x);
	    h[i+1] = f*(x-t[lj]);
	}
    }
}

template<> always_inline void fpbspl<2>(treal *t, real x, real *h)
{
    h[0] = (t[1]-x)/(t[1]-t[0]);
    h[1] = 1-h[0];
}


/****************************************************************
 ** search for knot interval
 ** n: len(map)
 ** k: order
 ** returns index l: t[l] <= x < t[l+1]
 */
static always_inline int find_index(int n, int k, real xi, real x0, real xe, real stepi, char* cl)
{
    int l;
    if (k % 2) {
	l = static_cast<int>((xi - x0) * stepi + 0.5);
    } else {
	l = static_cast<int>((xi - x0) * stepi);
    }
    if (l < 0) {
	*cl = -1;
	return 0;
    }
    if (l > n-2) {
	*cl = 1;
	return n-2;
    }
    return l;
}

template<int K, typename M>
static always_inline int forward(int i, splinecoeffs<M> *p, real *xi, int ll,
			  typename splinedata<M>::retval *cl, real *h)
{
    int l = p->map[i][find_index(p->nmap[i], K, xi[i], p->x0[i], p->xe[i], p->stepi[i], &cl->c[i])];
    fpbspl<K>(p->t[i]+l, xi[i], h);
    return ll*p->n[i] + l-K+1;
}

/****************************************************************
 ** evaluate the spline function at x
 **
 ** t[n+k]: knot array
 ** c[m][n]: coefficents
 ** k: order (k > 0), order = degree + 1
 ** x: function argument
 ** res: output array (size m)
 */
template<typename M>
template<int K0>
always_inline int splinedata<M>::splev(splinecoeffs<M> *p, real xi[1], real *res)
{
    real h[K0];
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, ll, &cl, h);
    treal *c = p->c[0]+ll;
    real sp = 0;
    for (int j = 0; j < K0; j++) {
	sp += c[j]*h[j];
    }
    *res = sp;
    return cl.i;
}

template<>
template<>
always_inline int splinedata<unsigned short>::splev_pp<4>(splinecoeffs<unsigned short> *p, real xi[1], real *res)
{
    retval cl;
    cl.i = 0;
    int l = p->map[0][find_index(p->nmap[0], 4, xi[0], p->x0[0], p->xe[0], p->stepi[0], &cl.c[0])];
    treal x = xi[0] - p->t[0][l];
    treal *c = p->c[0] + (l-3)*4;
    *res = ((c[0] * x + c[1]) * x + c[2]) * x + c[3];
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
template<typename M>
template<int K0, int K1>
int splinedata<M>::splev(splinecoeffs<M> *p, real xi[2], real *res)
{
    real h[2][6];
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, ll, &cl, h[0]);
    ll = forward<K1>(1, p, xi, ll, &cl, h[1]);
    treal *c = p->c[0]+ll;
    int j[2];
    real sp = 0;
    for (j[0] = 0; j[0] < K0; j[0]++) {
	for (j[1] = 0; j[1] < K1; j[1]++) {
	    sp += c[j[1]]*h[0][j[0]]*h[1][j[1]];
	}
	c += p->n[1];
    }
    *res = sp;
    return cl.i;
}

template<int K, int S>
static inline void deriv(real *t, real *wrk) {
    for (int i = 0; i < K-1; i++, wrk += S) {
	real fac = t[i+1] - t[i+1-(K-1)];
	if (fac > 0) {
	    wrk[0] = (K-1) * (wrk[S] - wrk[0]) / fac;
	}
    }
}

template<int K0, int K1, int S0, int S1>
static inline void deriv2d(real *t, real *c) {
    for (int i = 0; i < K0; i++) {
	deriv<K1, S1>(t, c);
	c += S0;
    }
}

template<int K0, int K1>
static inline void copy2d(real *c, real *wrk, int n)  {
    int j[2];
    for (j[0] = 0; j[0] < K0; j[0]++) {
	for (j[1] = 0; j[1] < K1; j[1]++) {
	    *wrk++ = *c++;
	}
	c += n - K1;
    }
}

template<int K0, int K1, int S>
static inline real eval2d(real *c, real *h0, real *h1) {
    int j[2];
    real sp = 0;
    for (j[0] = 0; j[0] < K0; j[0]++) {
	for (j[1] = 0; j[1] < K1; j[1]++) {
	    sp += *c++ * h0[j[0]] * h1[j[1]];
	}
	c += S;
    }
    return sp;
}

template<typename M>
template<int K0, int K1>
int splinedata<M>::splevgr(splinecoeffs<M> *p, real xi[2], real res[1], real grad[2])
{
    real h0[K0];
    real h1[K1];
    retval cl;
    cl.i = 0;
    int ll = 0;
//  ll = forward<K0>(0, p, xi, ll, &cl, h0);
    int l[2];
    l[0] = p->map[0][find_index(p->nmap[0], K0, xi[0], p->x0[0], p->xe[0], p->stepi[0], &cl.c[0])];
    fpbspl<K0>(p->t[0]+l[0], xi[0], h0);
    ll = l[0]-(K0-1);
//  ll = forward<K1>(1, p, xi, ll, &cl, h1);
    l[1] = p->map[1][find_index(p->nmap[1], K1, xi[1], p->x0[1], p->xe[1], p->stepi[1], &cl.c[1])];
    fpbspl<K1>(p->t[1]+l[1], xi[1], h1);
    ll = ll*p->n[1] + l[1]-(K1-1);
//    
    treal wrk[K0*K1];
    copy2d<K0, K1>(p->c[0]+ll, wrk, p->n[1]);
    res[0] = eval2d<K0, K1, 0>(wrk, h0, h1);

    deriv2d<K1, K0, 1, K1>(p->t[0]+l[0], wrk);
    real hx[6];
    fpbspl<K0-1>(p->t[0]+l[0], xi[0], hx);
    grad[0] = eval2d<K0-1, K1, 0>(wrk, hx, h1);

    copy2d<K0, K1>(p->c[0]+ll, wrk, p->n[1]);
    deriv2d<K0, K1, K1, 1>(p->t[1]+l[1], wrk);
    fpbspl<K1-1>(p->t[1]+l[1], xi[1], hx);
    grad[1] = eval2d<K0, K1-1, 1>(wrk, h0, hx);
    return cl.i;
}

template<typename M>
template<int K0, int K1, int K2>
int splinedata<M>::splev(splinecoeffs<M> *p, real xi[3], real *res)
{
    real h[3][6];
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, ll, &cl, h[0]);
    ll = forward<K1>(1, p, xi, ll, &cl, h[1]);
    ll = forward<K2>(2, p, xi, ll, &cl, h[2]);
    treal *cc = p->c[0];
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

template<typename M>
template<int K0, int K1, int K2, int K3>
int splinedata<M>::splev(splinecoeffs<M> *p, real xi[4], real *res)
{
    real h[4][6];
    retval cl;
    cl.i = 0;
    int ll = 0;
    ll = forward<K0>(0, p, xi, ll, &cl, h[0]);
    ll = forward<K1>(1, p, xi, ll, &cl, h[1]);
    ll = forward<K2>(2, p, xi, ll, &cl, h[2]);
    ll = forward<K3>(3, p, xi, ll, &cl, h[3]);
    treal *cc = p->c[0];
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

template<typename M>
SplineCalc<M>::SplineCalc(splinedata<M> *sd_, real *s0_)
    : sd(sd_),
      s0(s0_),
      temp(new real[sd->n_input+sd->n_state]) {
}

template<typename M>
SplineCalc<M>::~SplineCalc() {
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

template<typename M>
void SplineCalc<M>::calc(real *in, real *out)
{
    for (int i = 0; i < sd->n_input; i++) {
	temp[i] = in[i];
    }
    real t[sd->m];
    for (int i = 0; i < sd->m; i++) {
	splinecoeffs<M> *p = &sd->sc[i];
	check(sd, temp, (*p->eval)(p, temp, &t[i]));
    }
    for (int i = 0; i < sd->n_output; i++) {
	out[i] = t[i];
    }
    for (int i = 0; i < sd->n_state; i++) {
	temp[i+sd->n_input] = t[i+sd->n_output];
    }
}

template<typename M>
void SplineCalc<M>::reset()
{
    for (int i = 0; i < sd->n_state; i++) {
	temp[i+sd->n_input] = s0[i];
    }
}
