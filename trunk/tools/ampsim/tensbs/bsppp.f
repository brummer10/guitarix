      SUBROUTINE BSPPP(T,A,N,K,LDC,C,XI,LXI,WORK)
C***BEGIN PROLOGUE  BSPPP
C***DATE WRITTEN   800901   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  E3,K6
C***KEYWORDS  B-SPLINE,DATA FITTING,INTERPOLATION,SPLINE
C***AUTHOR  AMOS, D. E., (SNLA)
C***PURPOSE  Converts the B-representation to the piecewise
C            polynomial (PP) form for use with PPVAL.
C***DESCRIPTION
C
C     Written by Carl de Boor and modified by D. E. Amos
C
C     Reference
C         SIAM J. Numerical Analysis, 14, No. 3, June, 1977, pp.441-472.
C
C     Abstract
C         BSPPP is the BSPLPP routine of the reference.
C
C         BSPPP converts the B-representation (T,A,N,K) to the
C         piecewise polynomial (PP) form (C,XI,LXI,K) for use with
C         PPVAL.  Here XI(*), the break point array of length LXI, is
C         the knot array T(*) with multiplicities removed.  The columns
C         of the matrix C(I,J) contain the right Taylor derivatives
C         for the polynomial expansion about XI(J) for the intervals
C         XI(J) .LE. X .LE. XI(J+1), I=1,K, J=1,LXI.  Function PPVAL
C         makes this evaluation at a specified point X in
C         XI(1) .LE. X .LE. XI(LXI(1) .LE. X .LE. XI+1)
C
C         BSPPP calls BSPDR, BSPEV, INTRV, BSPVN
C
C     Description of Arguments
C         Input
C          T       - knot vector of length N+K
C          A       - B-spline coefficient vector of length N
C          N       - number of B-spline coefficients
C                    N = sum of knot multiplicities-K
C          K       - order of the B-spline, K .GE. 1
C          LDC     - leading dimension of C, LDC .GE. K
C
C         Output
C          C       - matrix of dimension at least (K,LXI) containing
C                    right derivatives at break points
C          XI      - XI break point vector of length LXI+1
C          LXI     - number of break points, LXI .LE. N-K+1
C          WORK    - work vector of length K*(N+3)
C
C     Error Conditions
C         Improper input is a fatal error
C***REFERENCES  C. DE BOOR, *PACKAGE FOR CALCULATING WITH B-SPLINES*,
C                 SIAM JOURNAL ON NUMERICAL ANALYSIS, VOLUME 14, NO. 3,
C                 JUNE 1977, PP. 441-472.
C***ROUTINES CALLED  BSPDR,BSPEV,XERROR
C***END PROLOGUE  BSPPP
C
C
      INTEGER ILEFT, INEV, K, LDC, LXI, N, NK
      REAL A, C, T, WORK, XI
C     DIMENSION T(N+K),XI(LXI+1),C(LDC,*)
C     HERE, * = THE FINAL VALUE OF THE OUTPUT PARAMETER LXI.
      DIMENSION T(1), A(N), WORK(1), XI(1), C(LDC,1)
C***FIRST EXECUTABLE STATEMENT  BSPPP
      IF(K.LT.1) GO TO 100
      IF(N.LT.K) GO TO 105
      IF(LDC.LT.K) GO TO 110
      CALL BSPDR(T, A, N, K, K, WORK)
      LXI = 0
      XI(1) = T(K)
      INEV = 1
      NK = N*K + 1
      DO 10 ILEFT=K,N
        IF (T(ILEFT+1).EQ.T(ILEFT)) GO TO 10
        LXI = LXI + 1
        XI(LXI+1) = T(ILEFT+1)
        CALL BSPEV(T,WORK(1),N,K, K,XI(LXI),INEV,C(1,LXI),WORK(NK))
   10 CONTINUE
      RETURN
  100 CONTINUE
      CALL XERROR( ' BSPPP,  K DOES NOT SATISFY K.GE.1', 34, 2, 1)
      RETURN
  105 CONTINUE
      CALL XERROR( ' BSPPP,  N DOES NOT SATISFY N.GE.K', 34, 2, 1)
      RETURN
  110 CONTINUE
      CALL XERROR( ' BSPPP,  LDC DOES NOT SATISFY LDC.GE.K', 38, 2, 1)
      RETURN
      END
