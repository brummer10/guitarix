#include <cstdio>
#include <cstdlib>
#include "intpp.h"

/****************************************************************
 ** fpbspl evaluates the k non-zero b-splines of order k
 ** at t[l] <= x < t[l+1] using the stable recurrence relation
 ** of de boor and cox.
 **
 ** t: knot array
 ** k: order (2 <= k <= 6)
 ** h[k]: output array
 */
static void fpbspl(float *t, int k, real x, int l, real *h)
{
    real hh[k-1];
    h[0] = 1;
    for (int j = 0; j < k-1; j++) {
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
 ** n: len(t)-k
 ** k: order
 ** returns index l: t[l] <= x < t[l+1]
 */
static inline int find_index(int n, int k, real *x, char* cl)
{
    if (*x < 0) {
	*cl = -1;
	*x = 0;
	return k-1;
    }
    if (*x > n-1) {
	*cl = 1;
	*x = n-1;
	return n-1;
    }
    *cl = 0;
    int m = k % 2;
    int l = static_cast<int>(*x+m/2.0) + (k-m)/2;
    if (l < k) {
	return k-1;
    } else if (l > n-1) {
	return n-1;
    } else {
	return l;
    }
}

static inline real linmap(real x, real x0, real step)
{
    return (x - x0) / step;
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
int splinedata::splev(splinedata *p, real *x, real *res)
{
    real h[p->k[0]];
    retval cl;
    cl.i = 0;
    x[0] = linmap(x[0], p->x0[0], p->step[0]);
    int l = find_index(p->n[0], p->k[0], &x[0], &cl.c[0]);
    fpbspl(p->t[0],p->k[0],x[0],l,h);
    int ll = l-p->k[0]+1;
    for (int i = 0; i < p->m; i++) {
	real sp = 0;
	for (int j = 0; j < p->k[0]; j++) {
	    sp += p->c[0][ll+j]*h[j];
	}
	res[i] = sp;
	ll += p->n[0];
    }
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
int splinedata::splev2(splinedata *p, real xi[2], real *res)
{
    real h[2][6];
    real x[2];
    retval cl;
    cl.i = 0;
    int ll = 0;
    for (int i = 0; i < 2; i++) {
	x[i] = linmap(xi[i], p->x0[i], p->step[i]);
	int l = find_index(p->n[i], p->k[i], &x[i], &cl.c[i]);
	fpbspl(p->t[i],p->k[i],x[i],l,h[i]);
	ll = ll*p->n[i] + l-p->k[i]+1;
    }
    for (int i = 0; i < p->m; i++) {
	float *cc = p->c[i];
	int lc = ll;
	int j[2];
	real sp = 0;
	for (j[0] = 0; j[0] < p->k[0]; j[0]++) {
	    for (j[1] = 0; j[1] < p->k[1]; j[1]++) {
		sp += cc[lc]*h[0][j[0]]*h[1][j[1]];
		lc += 1;
	    }
	    lc += p->n[1]-p->k[1];
	}
	res[i] = sp;
    }
    return cl.i;
}

int splinedata::splev3(splinedata *p, real xi[3], real *res)
{
    real h[3][6];
    real x[3];
    retval cl;
    cl.i = 0;
    int ll = 0;
    for (int i = 0; i < 3; i++) {
	x[i] = linmap(xi[i], p->x0[i], p->step[i]);
	int l = find_index(p->n[i], p->k[i], &x[i], &cl.c[i]);
	fpbspl(p->t[i],p->k[i],x[i],l,h[i]);
	ll = ll*p->n[i] + l-p->k[i]+1;
    }
    for (int i = 0; i < p->m; i++) {
	float *cc = p->c[i];
	int lc = ll;
	int j[3];
	real sp = 0;
	for (j[0] = 0; j[0] < p->k[0]; j[0]++) {
	    for (j[1] = 0; j[1] < p->k[1]; j[1]++) {
		for (j[2] = 0; j[2] < p->k[2]; j[2]++) {
		    sp += cc[lc]*h[0][j[0]]*h[1][j[1]]*h[2][j[2]];
		    lc += 1;
		}
		lc += p->n[2]-p->k[2];
	    }
	    lc += (p->n[1]-p->k[1])*p->n[2];
	}
	res[i] = sp;
    }
    return cl.i;
}

int splinedata::splev4(splinedata *p, real xi[4], real *res)
{
    real h[4][6];
    real x[4];
    retval cl;
    cl.i = 0;
    int ll = 0;
    for (int i = 0; i < 4; i++) {
	x[i] = linmap(xi[i], p->x0[i], p->step[i]);
	int l = find_index(p->n[i], p->k[i], &x[i], &cl.c[i]);
	fpbspl(p->t[i],p->k[i],x[i],l,h[i]);
	ll = ll*p->n[i] + l-p->k[i]+1;
    }
    for (int i = 0; i < p->m; i++) {
	float *cc = p->c[i];
	int lc = ll;
	int j[4];
	real sp = 0;
	for (j[0] = 0; j[0] < p->k[0]; j[0]++) {
	    for (j[1] = 0; j[1] < p->k[1]; j[1]++) {
		for (j[2] = 0; j[2] < p->k[2]; j[2]++) {
		    for (j[3] = 0; j[3] < p->k[3]; j[3]++) {
			sp += cc[lc]*h[0][j[0]]*h[1][j[1]]*h[2][j[2]]*h[3][j[3]];
			lc += 1;
		    }
		    lc += p->n[3]-p->k[3];
		}
		lc += (p->n[2]-p->k[2])*p->n[3];
	    }
	    lc += (p->n[1]-p->k[1])*p->n[2]*p->n[3];
	}
	res[i] = sp;
    }
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

#if 0
static void report(splinedata *sd, real *t, int i)
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

static inline void check(splinedata *sd, real *t, int i)
{
    if (i) report(sd, t, i);
}
#else
#define check(sd, t, i) i
#endif

void SplineCalc::calc(real *in, real *out)
{
    for (int i = 0; i < sd->n_input; i++) {
	temp[i] = in[i];
    }
    real t[sd->m];
    check(sd, temp, (*sd->eval)(sd, temp, t));
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
