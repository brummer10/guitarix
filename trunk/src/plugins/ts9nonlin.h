/*
 * Copyright (C) 2012 Andreas Degert, Hermann Meyer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//typedef double real;
typedef float real;

#include "ts9nonlin.cc"

union retval {
  char c[4];
  int i;
};

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
inline int find_index(int n, int k, real *x, char* cl)
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

inline real linmap(real x, real x0, real step, int n)
{
  real f = (x - x0) / step;
  return f;
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
static int splev2(float *t[2], int n[2], float *c[], int k[2], real xi[2], real x0[2], real step[2], real *res, int m)
{
  real h[2][6];
  real x[2];
  retval cl;
  cl.i = 0;
  int ll = 0;
  for (int i = 0; i < 2; i++) {
    x[i] = linmap(xi[i], x0[i], step[i], n[i]);
    int l = find_index(n[i], k[i], &x[i], &cl.c[i]);
    fpbspl(t[i],k[i],x[i],l,h[i]);
    ll = ll*n[i] + l-k[i]+1;
  }
  for (int i = 0; i < m; i++) {
    float *cc = c[i];
    int lc = ll;
    int j[2];
    real sp = 0;
    for (j[0] = 0; j[0] < k[0]; j[0]++) {
      for (j[1] = 0; j[1] < k[1]; j[1]++) {
	sp += cc[lc]*h[0][j[0]]*h[1][j[1]];
	lc += 1;
      }
      lc += n[1]-k[1];
    }
    res[i] = sp;
  }
  return cl.i;
}


/****************************************************************
 ** ts9nonlin: function implementing ts9 nonlinear part
 */

inline real ts9nonlin(real x, real d) {
    real inp[2];
    inp[0] = fabsf(x);
    inp[0] /= 3.0 + inp[0];
    inp[1] = d;
    real out;
    splev2(tts9,nts9,cts9,kts9,inp,x0ts9,hts9,&out,1);
    return copysign(out, -x);
}
