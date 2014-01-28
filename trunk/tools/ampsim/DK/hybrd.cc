#if 0
#define real_EPSILON FLT_EPSILON
#define real_MIN FLT_MIN
#define real_MAX FLT_MAX
#else
#define real_EPSILON DBL_EPSILON
#define real_MIN DBL_MIN
#define real_MAX DBL_MAX
#endif

real inline dpmpar(int i)
{
    switch(i) {
    case 1:
	return real_EPSILON;
    case 2:
	return real_MIN;
    default:
	return real_MAX;
    }
}

template<int N>
real inline enorm(const real *fvec) {
    real s = 0;
    for (int i = 0; i < N; i++) {
	s += fvec[i] * fvec[i];
    }
    return sqrt(s);
}

real inline enorm(int n, const real *fvec) {
    real s = 0;
    for (int i = 0; i < n; i++) {
	s += fvec[i] * fvec[i];
    }
    return sqrt(s);
}

template<int N>
real enorm2(const real *fvec) {
    real s = 0;
    for (int i = 0; i < N; i++) {
	s += fvec[i] * fvec[i];
    }
    return s;
}

template<int N>
void qform(real *q, int	ldq, real *wa)
{
    /* System generated locals */
    int q_dim1, q_offset;

    /* Local variables */
    int i, j, k, l;
    real sum, temp;

    /* Parameter adjustments */
    --wa;
    q_dim1 = ldq;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;

    /* Function Body */

/*     zero out upper triangle of q in the first min(m,n) columns. */

    if (N >= 2) {
        for (j = 2; j <= N; ++j) {
            for (i = 1; i <= j-1; ++i) {
                q[i + j * q_dim1] = 0.;
            }
        }
    }

/*     accumulate q from its factored form. */

    for (l = 1; l <= N; ++l) {
	k = N - l + 1;
	for (i = k; i <= N; ++i) {
	    wa[i] = q[i + k * q_dim1];
	    q[i + k * q_dim1] = 0.;
	}
	q[k + k * q_dim1] = 1.;
	if (wa[k] != 0.) {
            for (j = k; j <= N; ++j) {
                sum = 0.;
                for (i = k; i <= N; ++i) {
                    sum += q[i + j * q_dim1] * wa[i];
                }
                temp = sum / wa[k];
                for (i = k; i <= N; ++i) {
                    q[i + j * q_dim1] -= temp * wa[i];
                }
            }
        }
    }
} /* qform_ */

template<int N>
void r1updt(real *s, int ls, const real *u, real *v, real *w, int *sing)
{
    /* Initialized data */

#define p5 .5
#define p25 .25

    /* Local variables */
    int i, j, l, jj, nm1;
    real tan;
    int nmj;
    real cos, sin, tau, temp, giant, cotan;

    /* Parameter adjustments */
    --w;
    --u;
    --v;
    --s;
    (void)ls;

    /* Function Body */

/*     giant is the largest magnitude. */

    giant = dpmpar(3);

/*     initialize the diagonal element pointer. */

    jj = N * ((N << 1) - N + 1) / 2 - (N - N);

/*     move the nontrivial part of the last column of s into w. */

    l = jj;
    for (i = N; i <= N; ++i) {
	w[i] = s[l];
	++l;
    }

/*     rotate the vector v into a multiple of the n-th unit vector */
/*     in such a way that a spike is introduced into w. */

    nm1 = N - 1;
    if (nm1 >= 1) {
        for (nmj = 1; nmj <= nm1; ++nmj) {
            j = N - nmj;
            jj -= N - j + 1;
            w[j] = 0.;
            if (v[j] != 0.) {

/*        determine a givens rotation which eliminates the */
/*        j-th element of v. */

                if (fabs(v[N]) < fabs(v[j])) {
                    cotan = v[N] / v[j];
                    sin = p5 / sqrt(p25 + p25 * (cotan * cotan));
                    cos = sin * cotan;
                    tau = 1.;
                    if (fabs(cos) * giant > 1.) {
                        tau = 1. / cos;
                    }
                } else {
                    tan = v[j] / v[N];
                    cos = p5 / sqrt(p25 + p25 * (tan * tan));
                    sin = cos * tan;
                    tau = sin;
                }

/*        apply the transformation to v and store the information */
/*        necessary to recover the givens rotation. */

                v[N] = sin * v[j] + cos * v[N];
                v[j] = tau;

/*        apply the transformation to s and extend the spike in w. */

                l = jj;
                for (i = j; i <= N; ++i) {
                    temp = cos * s[l] - sin * w[i];
                    w[i] = sin * s[l] + cos * w[i];
                    s[l] = temp;
                    ++l;
                }
            }
        }
    }

/*     add the spike from the rank 1 update to w. */

    for (i = 1; i <= N; ++i) {
	w[i] += v[N] * u[i];
    }

/*     eliminate the spike. */

    *sing = false;
    if (nm1 >= 1) {
        for (j = 1; j <= nm1; ++j) {
            if (w[j] != 0.) {

/*        determine a givens rotation which eliminates the */
/*        j-th element of the spike. */

                if (fabs(s[jj]) < fabs(w[j])) {
                    cotan = s[jj] / w[j];
                    sin = p5 / sqrt(p25 + p25 * (cotan * cotan));
                    cos = sin * cotan;
                    tau = 1.;
                    if (fabs(cos) * giant > 1.) {
                        tau = 1. / cos;
                    }
                } else {
                    tan = w[j] / s[jj];
                    cos = p5 / sqrt(p25 + p25 * (tan * tan));
                    sin = cos * tan;
                    tau = sin;
                }

/*        apply the transformation to s and reduce the spike in w. */

                l = jj;
                for (i = j; i <= N; ++i) {
                    temp = cos * s[l] + sin * w[i];
                    w[i] = -sin * s[l] + cos * w[i];
                    s[l] = temp;
                    ++l;
                }

/*        store the information necessary to recover the */
/*        givens rotation. */

                w[j] = tau;
            }

/*        test for zero diagonal elements in the output s. */

            if (s[jj] == 0.) {
                *sing = true;
            }
            jj += N - j + 1;
        }
    }

/*     move w back into the last column of the output s. */

    l = jj;
    for (i = N; i <= N; ++i) {
	s[l] = w[i];
	++l;
    }
    if (s[jj] == 0.) {
	*sing = true;
    }

/*     last card of subroutine r1updt. */

} /* __minpack_func__(r1updt) */

template<int M, int N>
void r1mpyq(real *a, int lda, const real *v, const real *w)
{
    /* System generated locals */
    int a_dim1, a_offset;

    /* Local variables */
    int i, j, nm1, nmj;
    real cos, sin, temp;

    /* Parameter adjustments */
    --w;
    --v;
    a_dim1 = lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;

    /* Function Body */

/*     apply the first set of givens rotations to a. */

    nm1 = N - 1;
    if (nm1 < 1) {
        return;
    }
    for (nmj = 1; nmj <= nm1; ++nmj) {
	j = N - nmj;
	if (fabs(v[j]) > 1.) {
	    cos = 1. / v[j];
	    sin = sqrt(1. - cos * cos);
	} else {
	    sin = v[j];
	    cos = sqrt(1. - sin * sin);
	}
	for (i = 1; i <= M; ++i) {
	    temp = cos * a[i + j * a_dim1] - sin * a[i + N * a_dim1];
	    a[i + N * a_dim1] = sin * a[i + j * a_dim1] + cos * a[
		    i + N * a_dim1];
	    a[i + j * a_dim1] = temp;
	}
    }

/*     apply the second set of givens rotations to a. */

    for (j = 1; j <= nm1; ++j) {
	if (fabs(w[j]) > 1.) {
	    cos = 1. / w[j];
	    sin = sqrt(1. - cos * cos);
	} else {
	    sin = w[j];
	    cos = sqrt(1. - sin * sin);
	}
	for (i = 1; i <= M; ++i) {
	    temp = cos * a[i + j * a_dim1] + sin * a[i + N * a_dim1];
	    a[i + N * a_dim1] = -sin * a[i + j * a_dim1] + cos * a[i + N * a_dim1];
	    a[i + j * a_dim1] = temp;
	}
    }

/*     last card of subroutine r1mpyq. */

} /* r1mpyq_ */

template<int N>
int fdjac1(root_fcn *fcn_nn, void *p, real *x, const real *fvec, real *fjac, int ldfjac, int ml, 
	int mu, real epsfcn, real *wa1, real *wa2)
{
    /* System generated locals */
    int fjac_dim1, fjac_offset;

    /* Local variables */
    real h;
    int i, j, k;
    real eps, temp;
    int msum;
    real epsmch;
    int iflag = 0;

    /* Parameter adjustments */
    --wa2;
    --wa1;
    --fvec;
    --x;
    fjac_dim1 = ldfjac;
    fjac_offset = 1 + fjac_dim1 * 1;
    fjac -= fjac_offset;

    /* Function Body */

/*     epsmch is the machine precision. */

    epsmch = dpmpar(1);

    eps = sqrt((std::max(epsfcn,epsmch)));
    msum = ml + mu + 1;
    if (msum >= N) {

/*        computation of dense approximate jacobian. */

        for (j = 1; j <= N; ++j) {
            temp = x[j];
            h = eps * fabs(temp);
            if (h == 0.) {
                h = eps;
            }
            x[j] = temp + h;
            /* the last parameter of fcn_nn() is set to 2 to tell calls
               made to compute the function from calls made to compute
               the Jacobian (see fcn() in tlmfdrv.c) */
            iflag = fcn_nn(p, &x[1], &wa1[1], 2);
            if (iflag < 0) {
                return iflag;
            }
            x[j] = temp;
            for (i = 1; i <= N; ++i) {
                fjac[i + j * fjac_dim1] = (wa1[i] - fvec[i]) / h;
            }
        }
        return 0;
    }

/*        computation of banded approximate jacobian. */

    for (k = 1; k <= msum; ++k) {
	for (j = k; msum < 0 ? j >= N : j <= N; j += msum) {
	    wa2[j] = x[j];
	    h = eps * fabs(wa2[j]);
	    if (h == 0.) {
		h = eps;
	    }
	    x[j] = wa2[j] + h;
	}
	iflag = fcn_nn(p, &x[1], &wa1[1], 1);
	if (iflag < 0) {
            return iflag;
	}
	for (j = k; msum < 0 ? j >= N : j <= N; j += msum) {
	    x[j] = wa2[j];
	    h = eps * fabs(wa2[j]);
	    if (h == 0.) {
		h = eps;
	    }
	    for (i = 1; i <= N; ++i) {
		fjac[i + j * fjac_dim1] = 0.;
		if (i >= j - mu && i <= j + ml) {
		    fjac[i + j * fjac_dim1] = (wa1[i] - fvec[i]) / h;
		}
	    }
	}
    }
    return 0;

} /* fdjac1_ */

template<int N>
void qrfac(real *a, int lda, int pivot, int *ipvt, int lipvt, real *rdiag,
	 real *acnorm, real *wa)
{
#ifdef USE_LAPACK
    int i, j, k;
    double t;
    double* tau = wa;
    const int ltau = N;
    int lwork = -1;
    int info = 0;
    double* work;

    if (pivot) {
        assert( lipvt >= N );
        /* set all columns free */
        memset(ipvt, 0, sizeof(int)*N);
    }
    
    /* query optimal size of work */
    lwork = -1;
    if (pivot) {
        dgeqp3_(&m,&n,a,&lda,ipvt,tau,tau,&lwork,&info);
        lwork = (int)tau[0];
        assert( lwork >= 3*n+1  );
    } else {
        dgeqrf_(&m,&n,a,&lda,tau,tau,&lwork,&info);
        lwork = (int)tau[0];
        assert( lwork >= 1 && lwork >= n );
    }
    
    assert( info == 0 );
    
    /* alloc work area */
    work = (double *)malloc(sizeof(double)*lwork);
    assert(work != NULL);
    
    /* set acnorm first (from the doc of qrfac, acnorm may point to the same area as rdiag) */
    if (acnorm != rdiag) {
        for (j = 0; j < n; ++j) {
            acnorm[j] = enorm<N>(&a[j * lda]);
        }
    }
    
    /* QR decomposition */
    if (pivot) {
        dgeqp3_(&m,&n,a,&lda,ipvt,tau,work,&lwork,&info);
    } else {
        dgeqrf_(&m,&n,a,&lda,tau,work,&lwork,&info);
    }
    assert(info == 0);
    
    /* set rdiag, before the diagonal is replaced */
    memset(rdiag, 0, sizeof(double)*n);
    for(i=0 ; i<n ; ++i) {
        rdiag[i] = a[i*lda+i];
    }
    
    /* modify lower trinagular part to look like qrfac's output */
    for(i=0 ; i<ltau ; ++i) {
        k = i*lda+i;
        t = tau[i];
        a[k] = t;
        for(j=i+1 ; j<m ; j++) {
            k++;
            a[k] *= t;
        }
    }
    
    free(work);
#else /* !USE_LAPACK */
    /* Initialized data */

#define p05 .05

    /* System generated locals */
    real d1;

    /* Local variables */
    int i, j, k, jp1;
    real sum;
    real temp;
    real epsmch;
    real ajnorm;

/*     ********** */

/*     subroutine qrfac */

/*     this subroutine uses householder transformations with column */
/*     pivoting (optional) to compute a qr factorization of the */
/*     m by n matrix a. that is, qrfac determines an orthogonal */
/*     matrix q, a permutation matrix p, and an upper trapezoidal */
/*     matrix r with diagonal elements of nonincreasing magnitude, */
/*     such that a*p = q*r. the householder transformation for */
/*     column k, k = 1,2,...,min(m,n), is of the form */

/*                           t */
/*           i - (1/u(k))*u*u */

/*     where u has zeros in the first k-1 positions. the form of */
/*     this transformation and the method of pivoting first */
/*     appeared in the corresponding linpack subroutine. */

/*     the subroutine statement is */

/*       subroutine qrfac(m,n,a,lda,pivot,ipvt,lipvt,rdiag,acnorm,wa) */

/*     where */

/*       m is a positive integer input variable set to the number */
/*         of rows of a. */

/*       n is a positive integer input variable set to the number */
/*         of columns of a. */

/*       a is an m by n array. on input a contains the matrix for */
/*         which the qr factorization is to be computed. on output */
/*         the strict upper trapezoidal part of a contains the strict */
/*         upper trapezoidal part of r, and the lower trapezoidal */
/*         part of a contains a factored form of q (the non-trivial */
/*         elements of the u vectors described above). */

/*       lda is a positive integer input variable not less than m */
/*         which specifies the leading dimension of the array a. */

/*       pivot is a logical input variable. if pivot is set true, */
/*         then column pivoting is enforced. if pivot is set false, */
/*         then no column pivoting is done. */

/*       ipvt is an integer output array of length lipvt. ipvt */
/*         defines the permutation matrix p such that a*p = q*r. */
/*         column j of p is column ipvt(j) of the identity matrix. */
/*         if pivot is false, ipvt is not referenced. */

/*       lipvt is a positive integer input variable. if pivot is false, */
/*         then lipvt may be as small as 1. if pivot is true, then */
/*         lipvt must be at least n. */

/*       rdiag is an output array of length n which contains the */
/*         diagonal elements of r. */

/*       acnorm is an output array of length n which contains the */
/*         norms of the corresponding columns of the input matrix a. */
/*         if this information is not needed, then acnorm can coincide */
/*         with rdiag. */

/*       wa is a work array of length n. if pivot is false, then wa */
/*         can coincide with rdiag. */

/*     subprograms called */

/*       minpack-supplied ... dpmpar,enorm */

/*       fortran-supplied ... dmax1,dsqrt,min0 */

/*     argonne national laboratory. minpack project. march 1980. */
/*     burton s. garbow, kenneth e. hillstrom, jorge j. more */

/*     ********** */
    (void)lipvt;

/*     epsmch is the machine precision. */

    epsmch = dpmpar(1);

/*     compute the initial column norms and initialize several arrays. */

    for (j = 0; j < N; ++j) {
	acnorm[j] = enorm<N>(&a[j * lda + 0]);
	rdiag[j] = acnorm[j];
	wa[j] = rdiag[j];
	if (pivot) {
	    ipvt[j] = j+1;
	}
    }

/*     reduce a to r with householder transformations. */

    for (j = 0; j < N; ++j) {
	if (pivot) {

/*        bring the column of largest norm into the pivot position. */

            int kmax = j;
            for (k = j; k < N; ++k) {
                if (rdiag[k] > rdiag[kmax]) {
                    kmax = k;
                }
            }
            if (kmax != j) {
                for (i = 0; i < N; ++i) {
                    temp = a[i + j * lda];
                    a[i + j * lda] = a[i + kmax * lda];
                    a[i + kmax * lda] = temp;
                }
                rdiag[kmax] = rdiag[j];
                wa[kmax] = wa[j];
                k = ipvt[j];
                ipvt[j] = ipvt[kmax];
                ipvt[kmax] = k;
            }
        }

/*        compute the householder transformation to reduce the */
/*        j-th column of a to a multiple of the j-th unit vector. */

	ajnorm = enorm(N - (j+1) + 1, &a[j + j * lda]);
	if (ajnorm != 0.) {
            if (a[j + j * lda] < 0.) {
                ajnorm = -ajnorm;
            }
            for (i = j; i < N; ++i) {
                a[i + j * lda] /= ajnorm;
            }
            a[j + j * lda] += 1.;

/*        apply the transformation to the remaining columns */
/*        and update the norms. */

            jp1 = j + 1;
            if (N > jp1) {
                for (k = jp1; k < N; ++k) {
                    sum = 0.;
                    for (i = j; i < N; ++i) {
                        sum += a[i + j * lda] * a[i + k * lda];
                    }
                    temp = sum / a[j + j * lda];
                    for (i = j; i < N; ++i) {
                        a[i + k * lda] -= temp * a[i + j * lda];
                    }
                    if (pivot && rdiag[k] != 0.) {
                        temp = a[j + k * lda] / rdiag[k];
                        /* Computing MAX */
                        d1 = 1. - temp * temp;
                        rdiag[k] *= sqrt((std::max((real)0.,d1)));
                        /* Computing 2nd power */
                        d1 = rdiag[k] / wa[k];
                        if (p05 * (d1 * d1) <= epsmch) {
                            rdiag[k] = enorm(N - (j+1), &a[jp1 + k * lda]);
                            wa[k] = rdiag[k];
                        }
                    }
                }
            }
        }
	rdiag[j] = -ajnorm;
    }

/*     last card of subroutine qrfac. */
#endif /* !USE_LAPACK */
} /* qrfac_ */

template<int N>
void dogleg(const real *r, int lr, const real *diag, const real *qtb, real delta, real *x, 
	    real *wa1, real *wa2)
{
    /* System generated locals */
    real d1, d2, d3, d4;

    /* Local variables */
    int i, j, k, l, jj, jp1;
    real sum, temp, alpha, bnorm;
    real gnorm, qnorm, epsmch;
    real sgnorm;

    /* Parameter adjustments */
    --wa2;
    --wa1;
    --x;
    --qtb;
    --diag;
    --r;
    (void)lr;

    /* Function Body */

/*     epsmch is the machine precision. */

    epsmch = dpmpar(1);

/*     first, calculate the gauss-newton direction. */

    jj = N * (N + 1) / 2 + 1;
    for (k = 1; k <= N; ++k) {
	j = N - k + 1;
	jp1 = j + 1;
	jj -= k;
	l = jj + 1;
	sum = 0.;
	if (N >= jp1) {
            for (i = jp1; i <= N; ++i) {
                sum += r[l] * x[i];
                ++l;
            }
        }
	temp = r[jj];
	if (temp == 0.) {
            l = j;
            for (i = 1; i <= j; ++i) {
                /* Computing MAX */
                d2 = fabs(r[l]);
                temp = std::max(temp,d2);
                l = l + N - i;
            }
            temp = epsmch * temp;
            if (temp == 0.) {
                temp = epsmch;
            }
        }
	x[j] = (qtb[j] - sum) / temp;
    }

/*     test whether the gauss-newton direction is acceptable. */

    for (j = 1; j <= N; ++j) {
	wa1[j] = 0.;
	wa2[j] = diag[j] * x[j];
    }
    qnorm = enorm<N>(&wa2[1]);
    if (qnorm <= delta) {
        return;
    }

/*     the gauss-newton direction is not acceptable. */
/*     next, calculate the scaled gradient direction. */

    l = 1;
    for (j = 1; j <= N; ++j) {
	temp = qtb[j];
	for (i = j; i <= N; ++i) {
	    wa1[i] += r[l] * temp;
	    ++l;
	}
	wa1[j] /= diag[j];
    }

/*     calculate the norm of the scaled gradient and test for */
/*     the special case in which the scaled gradient is zero. */

    gnorm = enorm<N>(&wa1[1]);
    sgnorm = 0.;
    alpha = delta / qnorm;
    if (gnorm != 0.) {

/*     calculate the point along the scaled gradient */
/*     at which the quadratic is minimized. */

        for (j = 1; j <= N; ++j) {
            wa1[j] = wa1[j] / gnorm / diag[j];
        }
        l = 1;
        for (j = 1; j <= N; ++j) {
            sum = 0.;
            for (i = j; i <= N; ++i) {
                sum += r[l] * wa1[i];
                ++l;
            }
            wa2[j] = sum;
        }
        temp = enorm<N>(&wa2[1]);
        sgnorm = gnorm / temp / temp;

/*     test whether the scaled gradient direction is acceptable. */

        alpha = 0.;
        if (sgnorm < delta) {

/*     the scaled gradient direction is not acceptable. */
/*     finally, calculate the point along the dogleg */
/*     at which the quadratic is minimized. */

            bnorm = enorm<N>(&qtb[1]);
            temp = bnorm / gnorm * (bnorm / qnorm) * (sgnorm / delta);
            /* Computing 2nd power */
            d1 = sgnorm / delta;
            /* Computing 2nd power */
            d2 = temp - delta / qnorm;
            /* Computing 2nd power */
            d3 = delta / qnorm;
            /* Computing 2nd power */
            d4 = sgnorm / delta;
            temp = temp - delta / qnorm * (d1 * d1)
                   + sqrt(d2 * d2
                          + (1. - d3 * d3) * (1. - d4 * d4));
            /* Computing 2nd power */
            d1 = sgnorm / delta;
            alpha = delta / qnorm * (1. - d1 * d1) / temp;
        }
    }

/*     form appropriate convex combination of the gauss-newton */
/*     direction and the scaled gradient direction. */

    temp = (1. - alpha) * std::min(sgnorm,delta);
    for (j = 1; j <= N; ++j) {
	x[j] = temp * wa1[j] + alpha * x[j];
    }

} /* dogleg_ */

template<int N>
int hybrdX(root_fcn *fcn_nn, void *p, real *x, real *
	fvec, real xtol, int maxfev, int ml, int mu, 
	real epsfcn, real *diag, int mode, real
	factor, int nprint, int *nfev, real *
	fjac, int ldfjac, real *r, int lr, real *qtf, 
	real *wa1, real *wa2, real *wa3, real *wa4)
{
    /* Initialized data */

#define p1 .1
#define p5 .5
#define p001 .001
#define p0001 1e-4

    /* System generated locals */
    int fjac_dim1, fjac_offset, i1;
    real d1, d2;

    /* Local variables */
    int i, j, l, jm1, iwa[1];
    real sum;
    int sing;
    int iter;
    real temp;
    int msum, iflag;
    real delta = 0.;
    int jeval;
    int ncsuc;
    real ratio;
    real fnorm;
    real pnorm, xnorm = 0., fnorm1;
    int nslow1, nslow2;
    int ncfail;
    real actred, epsmch, prered;
    int info;

    /* Parameter adjustments */
    --wa4;
    --wa3;
    --wa2;
    --wa1;
    --qtf;
    --diag;
    --fvec;
    --x;
    fjac_dim1 = ldfjac;
    fjac_offset = 1 + fjac_dim1 * 1;
    fjac -= fjac_offset;
    --r;

    /* Function Body */

/*     epsmch is the machine precision. */

    epsmch = dpmpar(1);

    info = 0;
    iflag = 0;
    *nfev = 0;

/*     check the input parameters for errors. */

    if (N <= 0 || xtol < 0. || maxfev <= 0 || ml < 0 || mu < 0 ||
	    factor <= 0. || ldfjac < N || lr < N * (N + 1) / 2) {
	goto TERMINATE;
    }
    if (mode == 2) {
        for (j = 1; j <= N; ++j) {
            if (diag[j] <= 0.) {
                goto TERMINATE;
            }
        }
    }

/*     evaluate the function at the starting point */
/*     and calculate its norm. */

    iflag = fcn_nn(p, &x[1], &fvec[1], 1);
    *nfev = 1;
    if (iflag < 0) {
	goto TERMINATE;
    }
    fnorm = enorm2<N>(&fvec[1]);

/*     determine the number of calls to fcn needed to compute */
/*     the jacobian matrix. */

/* Computing MIN */
    i1 = ml + mu + 1;
    msum = std::min(i1,N);

/*     initialize iteration counter and monitors. */

    iter = 1;
    ncsuc = 0;
    ncfail = 0;
    nslow1 = 0;
    nslow2 = 0;

/*     beginning of the outer loop. */

    for (;;) {
        jeval = true;

/*        calculate the jacobian matrix. */

        iflag = fdjac1<N>(fcn_nn, p, &x[1], &fvec[1], &fjac[fjac_offset], ldfjac,
			  ml, mu, epsfcn, &wa1[1], &wa2[1]);
        *nfev += msum;
        if (iflag < 0) {
            goto TERMINATE;
        }

/*        compute the qr factorization of the jacobian. */

        qrfac<N>(&fjac[fjac_offset], ldfjac, false, iwa, 1, &wa1[1], &wa2[1], &wa3[1]);

/*        on the first iteration and if mode is 1, scale according */
/*        to the norms of the columns of the initial jacobian. */

        if (iter == 1) {
            if (mode != 2) {
                for (j = 1; j <= N; ++j) {
                    diag[j] = wa2[j];
                    if (wa2[j] == 0.) {
                        diag[j] = 1.;
                    }
                }
            }

/*        on the first iteration, calculate the norm of the scaled x */
/*        and initialize the step bound delta. */

            for (j = 1; j <= N; ++j) {
                wa3[j] = diag[j] * x[j];
            }
            xnorm = enorm<N>(&wa3[1]);
            delta = factor * xnorm;
            if (delta == 0.) {
                delta = factor;
            }
        }

/*        form (q transpose)*fvec and store in qtf. */

        for (i = 1; i <= N; ++i) {
            qtf[i] = fvec[i];
        }
        for (j = 1; j <= N; ++j) {
            if (fjac[j + j * fjac_dim1] != 0.) {
                sum = 0.;
                for (i = j; i <= N; ++i) {
                    sum += fjac[i + j * fjac_dim1] * qtf[i];
                }
                temp = -sum / fjac[j + j * fjac_dim1];
                for (i = j; i <= N; ++i) {
                    qtf[i] += fjac[i + j * fjac_dim1] * temp;
                }
            }
        }

/*        copy the triangular factor of the qr factorization into r. */

        sing = false;
        for (j = 1; j <= N; ++j) {
            l = j;
            jm1 = j - 1;
            if (jm1 >= 1) {
                for (i = 1; i <= jm1; ++i) {
                    r[l] = fjac[i + j * fjac_dim1];
                    l = l + N - i;
                }
            }
            r[l] = wa1[j];
            if (wa1[j] == 0.) {
                sing = true;
            }
        }

/*        accumulate the orthogonal factor in fjac. */

        qform<N>(&fjac[fjac_offset], ldfjac, &wa1[1]);

/*        rescale if necessary. */

        if (mode != 2) {
            for (j = 1; j <= N; ++j) {
                /* Computing MAX */
                d1 = diag[j], d2 = wa2[j];
                diag[j] = std::max(d1,d2);
            }
        }

/*        beginning of the inner loop. */

        for (;;) {

/*           if requested, call fcn to enable printing of iterates. */

            if (nprint > 0) {
                iflag = 0;
                if ((iter - 1) % nprint == 0) {
                    iflag = fcn_nn(p, &x[1], &fvec[1], 0);
                }
                if (iflag < 0) {
                    goto TERMINATE;
                }
            }

/*           determine the direction p. */

            dogleg<N>(&r[1], lr, &diag[1], &qtf[1], delta, &wa1[1], &wa2[1], &wa3[1]);

/*           store the direction p and x + p. calculate the norm of p. */

            for (j = 1; j <= N; ++j) {
                wa1[j] = -wa1[j];
                wa2[j] = x[j] + wa1[j];
                wa3[j] = diag[j] * wa1[j];
            }
            pnorm = enorm<N>(&wa3[1]);

/*           on the first iteration, adjust the initial step bound. */

            if (iter == 1) {
                delta = std::min(delta,pnorm);
            }

/*           evaluate the function at x + p and calculate its norm. */

            iflag = fcn_nn(p, &wa2[1], &wa4[1], 1);
            ++(*nfev);
            if (iflag < 0) {
                goto TERMINATE;
            }
            fnorm1 = enorm2<N>(&wa4[1]);

/*           compute the scaled actual reduction. */

            actred = -1.;
            if (fnorm1 < fnorm) {
                /* already 2nd power */
                actred = 1. - fnorm1 / fnorm;
            }

/*           compute the scaled predicted reduction. */

            l = 1;
            for (i = 1; i <= N; ++i) {
                sum = 0.;
                for (j = i; j <= N; ++j) {
                    sum += r[l] * wa1[j];
                    ++l;
                }
                wa3[i] = qtf[i] + sum;
            }
            temp = enorm2<N>(&wa3[1]);
            prered = 0.;
            if (temp < fnorm) {
                /* already 2nd power */
                prered = 1. - temp / fnorm;
            }

/*           compute the ratio of the actual to the predicted */
/*           reduction. */

            ratio = 0.;
            if (prered > 0.) {
                ratio = actred / prered;
            }

/*           update the step bound. */

            if (ratio < p1) {
                ncsuc = 0;
                ++ncfail;
                delta = p5 * delta;
            } else {
                ncfail = 0;
                ++ncsuc;
                if (ratio >= p5 || ncsuc > 1) {
                    /* Computing MAX */
                    d1 = pnorm / p5;
                    delta = std::max(delta,d1);
                }
                if (fabs(ratio - 1.) <= p1) {
                    delta = pnorm / p5;
                }
            }

/*           test for successful iteration. */

            if (ratio >= p0001) {

/*           successful iteration. update x, fvec, and their norms. */

                for (j = 1; j <= N; ++j) {
                    x[j] = wa2[j];
                    wa2[j] = diag[j] * x[j];
                    fvec[j] = wa4[j];
                }
                xnorm = enorm<N>(&wa2[1]);
                fnorm = fnorm1;
                ++iter;
            }

/*           determine the progress of the iteration. */

            ++nslow1;
            if (actred >= p001) {
                nslow1 = 0;
            }
            if (jeval) {
                ++nslow2;
            }
            if (actred >= p1) {
                nslow2 = 0;
            }

/*           test for convergence. */

            if (delta <= xtol * xnorm || fnorm == 0.) {
                info = 1;
            }
            if (info != 0) {
                goto TERMINATE;
            }

/*           tests for termination and stringent tolerances. */

            if (*nfev >= maxfev) {
                info = 2;
            }
            /* Computing MAX */
            d1 = p1 * delta;
            if (p1 * std::max(d1,pnorm) <= epsmch * xnorm) {
                info = 3;
            }
            if (nslow2 == 5) {
                info = 4;
            }
            if (nslow1 == 10) {
                info = 5;
            }
            if (info != 0) {
                goto TERMINATE;
            }

/*           criterion for recalculating jacobian approximation */
/*           by forward differences. */

            if (ncfail == 2) {
                goto TERMINATE_INNER_LOOP;
            }

/*           calculate the rank one modification to the jacobian */
/*           and update qtf if necessary. */

            for (j = 1; j <= N; ++j) {
                sum = 0.;
                for (i = 1; i <= N; ++i) {
                    sum += fjac[i + j * fjac_dim1] * wa4[i];
                }
                wa2[j] = (sum - wa3[j]) / pnorm;
                wa1[j] = diag[j] * (diag[j] * wa1[j] / pnorm);
                if (ratio >= p0001) {
                    qtf[j] = sum;
                }
            }

/*           compute the qr factorization of the updated jacobian. */

            r1updt<N>(&r[1], lr, &wa1[1], &wa2[1], &wa3[1], &sing);
            r1mpyq<N, N>(&fjac[fjac_offset], ldfjac, &wa2[1], &wa3[1]);
            r1mpyq<1, N>(&qtf[1], 1, &wa2[1], &wa3[1]);

/*           end of the inner loop. */

            jeval = false;
        }
TERMINATE_INNER_LOOP:
        ;
/*        end of the outer loop. */

    }
TERMINATE:

/*     termination, either normal or user imposed. */

    if (iflag < 0) {
	info = iflag;
    }
    if (nprint > 0) {
	fcn_nn(p, &x[1], &fvec[1], 0);
    }
    return info;

/*     last card of subroutine hybrd. */

} /* hybrd_ */
