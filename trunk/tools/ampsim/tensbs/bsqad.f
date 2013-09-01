      SUBROUTINE BSQAD(T,BCOEF,N,K,X1,X2,BQUAD,WORK)
C***BEGIN PROLOGUE  BSQAD
C***DATE WRITTEN   800901   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  H2A2A1,E3,K6
C***KEYWORDS  B-SPLINE,DATA FITTING,INTERPOLATION,QUADRATURE,SPLINE
C***AUTHOR  AMOS, D. E., (SNLA)
C***PURPOSE  Computes the integral on (X1,X2) of a K-th order
C            B-spline using the B-representation.
C***DESCRIPTION
C
C     Written by D. E. Amos, June, 1979.
C
C     Reference SAND 79-1825
C
C     Abstract
C         BSQAD computes the integral on (X1,X2) of a K-th order
C         B-spline using the B-representation (T,BCOEF,N,K).  Orders
C         K as high as 20 are permitted by applying a 2, 6, or 10
C         point Gauss formula on subintervals of (X1,X2) which are
C         formed by included (distinct) knots.
C
C         If orders K greater than 20 are needed, use BFQAD with
C         F(X) = 1.
C
C         BSQAD calls INTRV, BVALU, XERROR
C
C     Description of Arguments
C         Input
C           T      - knot array of length N+K
C           BCOEF  - B-spline coefficient array of length N
C           N      - length of coefficient array
C           K      - order of B-spline, 1 .LE. K .LE. 20
C           X1,X2  - end points of quadrature interval in
C                    T(K) .LE. X .LE. T(N+1)
C
C         Output
C           BQUAD  - integral of the B-spline over (X1,X2)
C           WORK   - work vector of length 3*K
C
C     Error Conditions
C         Improper input is a fatal error
C***REFERENCES  D.E. AMOS, *QUADRATURE SUBROUTINES FOR SPLINES AND
C                 B-SPLINES*, SAND79-1825, SANDIA LABORATORIES,
C                 DECEMBER 1979.
C***ROUTINES CALLED  BVALU,INTRV,XERROR
C***END PROLOGUE  BSQAD
C
C
      INTEGER I,IL1,IL2,ILO,INBV, JF,K,LEFT,M,MF,MFLAG,N, NPK, NP1
      REAL A, AA, B, BB, BCOEF, BMA, BPA, BQUAD, C1, GPTS, GWTS, GX, Q,
     1 SUM, T, TA, TB, WORK, X1, X2, Y1, Y2
      REAL BVALU
      DIMENSION T(1), BCOEF(1), GPTS(9), GWTS(9), SUM(5), WORK(1)
C
      DATA GPTS(1), GPTS(2), GPTS(3), GPTS(4), GPTS(5), GPTS(6),
     1     GPTS(7), GPTS(8), GPTS(9)/
     2     5.77350269189625764E-01,     2.38619186083196909E-01,
     3     6.61209386466264514E-01,     9.32469514203152028E-01,
     4     1.48874338981631211E-01,     4.33395394129247191E-01,
     5     6.79409568299024406E-01,     8.65063366688984511E-01,
     6     9.73906528517171720E-01/
      DATA GWTS(1), GWTS(2), GWTS(3), GWTS(4), GWTS(5), GWTS(6),
     1     GWTS(7), GWTS(8), GWTS(9)/
     2     1.00000000000000000E+00,     4.67913934572691047E-01,
     3     3.60761573048138608E-01,     1.71324492379170345E-01,
     4     2.95524224714752870E-01,     2.69266719309996355E-01,
     5     2.19086362515982044E-01,     1.49451349150580593E-01,
     6     6.66713443086881376E-02/
C
C***FIRST EXECUTABLE STATEMENT  BSQAD
      BQUAD = 0.0E0
      IF(K.LT.1 .OR. K.GT.20) GO TO 65
      IF(N.LT.K) GO TO 70
      AA = AMIN1(X1,X2)
      BB = AMAX1(X1,X2)
      IF (AA.LT.T(K)) GO TO 60
      NP1 = N + 1
      IF (BB.GT.T(NP1)) GO TO 60
      IF (AA.EQ.BB) RETURN
      NPK = N + K
C     SELECTION OF 2, 6, OR 10 POINT GAUSS FORMULA
      JF = 0
      MF = 1
      IF (K.LE.4) GO TO 10
      JF = 1
      MF = 3
      IF (K.LE.12) GO TO 10
      JF = 4
      MF = 5
   10 CONTINUE
C
      DO 20 I=1,MF
        SUM(I) = 0.0E0
   20 CONTINUE
      ILO = 1
      INBV = 1
      CALL INTRV(T, NPK, AA, ILO, IL1, MFLAG)
      CALL INTRV(T, NPK, BB, ILO, IL2, MFLAG)
      IF (IL2.GE.NP1) IL2 = N
      DO 40 LEFT=IL1,IL2
        TA = T(LEFT)
        TB = T(LEFT+1)
        IF (TA.EQ.TB) GO TO 40
        A = AMAX1(AA,TA)
        B = AMIN1(BB,TB)
        BMA = 0.5E0*(B-A)
        BPA = 0.5E0*(B+A)
        DO 30 M=1,MF
          C1 = BMA*GPTS(JF+M)
          GX = -C1 + BPA
          Y2 = BVALU(T,BCOEF,N,K,0,GX,INBV,WORK)
          GX = C1 + BPA
          Y1 = BVALU(T,BCOEF,N,K,0,GX,INBV,WORK)
          SUM(M) = SUM(M) + (Y1+Y2)*BMA
   30   CONTINUE
   40 CONTINUE
      Q = 0.0E0
      DO 50 M=1,MF
        Q = Q + GWTS(JF+M)*SUM(M)
   50 CONTINUE
      IF (X1.GT.X2) Q = -Q
      BQUAD = Q
      RETURN
C
C
   60 CONTINUE
      CALL XERROR( ' BSQAD,  X1 OR X2 OR BOTH DO NOT SATISFY T(K).LE.X.L
     1E.T(N+1)',   60, 2, 1)
      RETURN
   65 CONTINUE
      CALL XERROR( ' BSQAD,  K DOES NOT SATISFY 1.LE.K.LE.20',
     1 40, 2, 1)
      RETURN
   70 CONTINUE
      CALL XERROR( ' BSQAD,  N DOES NOT SATISFY N.GE.K', 34, 2, 1)
      RETURN
      END
