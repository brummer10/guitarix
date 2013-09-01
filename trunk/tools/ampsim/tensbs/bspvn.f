      SUBROUTINE BSPVN(T,JHIGH,K,INDEX,X,ILEFT,VNIKX,WORK,IWORK)
C***BEGIN PROLOGUE  BSPVN
C***DATE WRITTEN   800901   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  E3,K6
C***KEYWORDS  B-SPLINE,DATA FITTING,INTERPOLATION,SPLINE
C***AUTHOR  AMOS, D. E., (SNLA)
C***PURPOSE  Calculates the value of all (possibly) nonzero basis
C            functions at X.
C***DESCRIPTION
C
C     Written by Carl de Boor and modified by D. E. Amos
C
C     Reference
C         SIAM J. Numerical Analysis, 14, No. 3, June, 1977, pp.441-472.
C
C     Abstract
C         BSPVN is the BSPLVN routine of the reference.
C
C         BSPVN calculates the value of all (possibly) nonzero basis
C         functions at X of order MAX(JHIGH,(J+1)*(INDEX-1)), where
C         T(K) .LE. X .LE. T(N+1) and J=IWORK is set inside the routine
C         on the first call when INDEX=1.  ILEFT is such that T(ILEFT)
C         .LE. X .LT. T(ILEFT+1).  A call to INTRV(T,N+1,X,ILO,ILEFT,
C         MFLAG) produces the proper ILEFT.  BSPVN calculates using the
C         basic algorithm needed in BSPVD.  If only basis functions are
C         desired, setting JHIGH=K and INDEX=1 can be faster than
C         calling BSPVD, but extra coding is required for derivatives
C         (INDEX=2) and BSPVD is set up for this purpose.
C
C         Left limiting values are set up as described in BSPVD.
C
C     Description of Arguments
C         Input
C          T       - knot vector of length N+K, where
C                    N = number of B-spline basis functions
C                    N = sum of knot multiplicities-K
C          JHIGH   - order of B-spline, 1 .LE. JHIGH .LE. K
C          K       - highest possible order
C          INDEX   - INDEX = 1 gives basis functions of order JHIGH
C                          = 2 denotes previous entry with WORK, IWORK
C                              values saved for subsequent calls to
C                              BSPVN.
C          X       - argument of basis functions,
C                    T(K) .LE. X .LE. T(N+1)
C          ILEFT   - largest integer such that
C                    T(ILEFT) .LE. X .LT. T(ILEFT+1)
C
C         Output
C          VNIKX   - vector of length K for spline values.
C          WORK    - a work vector of length 2*K
C          IWORK   - a work parameter.  Both WORK and IWORK contain
C                    information necessary to continue for INDEX = 2.
C                    When INDEX = 1 exclusively, these are scratch
C                    variables and can be used for other purposes.
C
C     Error Conditions
C         Improper input is a fatal error.
C***REFERENCES  C. DE BOOR, *PACKAGE FOR CALCULATING WITH B-SPLINES*,
C                 SIAM JOURNAL ON NUMERICAL ANALYSIS, VOLUME 14, NO. 3,
C                 JUNE 1977, PP. 441-472.
C***ROUTINES CALLED  XERROR
C***END PROLOGUE  BSPVN
C
C
      INTEGER ILEFT, IMJP1, INDEX, IPJ, IWORK, JHIGH, JP1, JP1ML, K, L
      REAL T, VM, VMPREV, VNIKX, WORK, X
C     DIMENSION T(ILEFT+JHIGH)
      DIMENSION T(1), VNIKX(K), WORK(1)
C     CONTENT OF J, DELTAM, DELTAP IS EXPECTED UNCHANGED BETWEEN CALLS.
C     WORK(I) = DELTAP(I), WORK(K+I) = DELTAM(I), I = 1,K
C***FIRST EXECUTABLE STATEMENT  BSPVN
      IF(K.LT.1) GO TO 90
      IF(JHIGH.GT.K .OR. JHIGH.LT.1) GO TO 100
      IF(INDEX.LT.1 .OR. INDEX.GT.2) GO TO 105
      IF(X.LT.T(ILEFT) .OR. X.GT.T(ILEFT+1)) GO TO 110
      GO TO (10, 20), INDEX
   10 IWORK = 1
      VNIKX(1) = 1.0E0
      IF (IWORK.GE.JHIGH) GO TO 40
C
   20 IPJ = ILEFT + IWORK
      WORK(IWORK) = T(IPJ) - X
      IMJP1 = ILEFT - IWORK + 1
      WORK(K+IWORK) = X - T(IMJP1)
      VMPREV = 0.0E0
      JP1 = IWORK + 1
      DO 30 L=1,IWORK
        JP1ML = JP1 - L
        VM = VNIKX(L)/(WORK(L)+WORK(K+JP1ML))
        VNIKX(L) = VM*WORK(L) + VMPREV
        VMPREV = VM*WORK(K+JP1ML)
   30 CONTINUE
      VNIKX(JP1) = VMPREV
      IWORK = JP1
      IF (IWORK.LT.JHIGH) GO TO 20
C
   40 RETURN
C
C
   90 CONTINUE
      CALL XERROR( ' BSPVN,  K DOES NOT SATISFY K.GE.1', 34, 2, 1)
      RETURN
  100 CONTINUE
      CALL XERROR( ' BSPVN,  JHIGH DOES NOT SATISFY 1.LE.JHIGH.LE.K',
     1 47, 2, 1)
      RETURN
  105 CONTINUE
      CALL XERROR( ' BSPVN,  INDEX IS NOT 1 OR 2',28,2,1)
      RETURN
  110 CONTINUE
      CALL XERROR( ' BSPVN,  X DOES NOT SATISFY T(ILEFT).LE.X.LE.T(ILEFT
     1+1)', 55, 2, 1)
      RETURN
      END
