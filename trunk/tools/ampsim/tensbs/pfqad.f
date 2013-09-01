      SUBROUTINE PFQAD(F,LDC,C,XI,LXI,K,ID,X1,X2,TOL,QUAD,IERR)
C***BEGIN PROLOGUE  PFQAD
C***DATE WRITTEN   800901   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  H2A2A1,E3,K6
C***KEYWORDS  B-SPLINE,DATA FITTING,INTERPOLATION,QUADRATURE,SPLINE
C***AUTHOR  AMOS, D. E., (SNLA)
C***PURPOSE  Computes the integral on (X1,X2) of a product of a function
C            F and the ID-th derivative of a B-spline,
C            (PP-representation).
C***DESCRIPTION
C
C     Written by D. E. Amos, June, 1979.
C
C     Reference SAND-79-1825
C
C     Abstract
C         PFQAD computes the integral on (X1,X2) of a product of a
C         function F and the ID-th derivative of a B-spline, using the
C         PP-representation (C,XI,LXI,K). (X1,X2) is normally a sub-
C         interval of XI(1) .LE. X .LE. XI(LXI+1).  An integration rou-
C         tine, PPGQ8(a modification of GAUS8), integrates the product
C         on sub-intervals of (X1,X2) formed by the included break
C         points.  Integration outside of (XI(1),XI(LXI+1)) is permitted
C         provided F is defined.
C
C         PFQAD calls INTRV, PPVAL, PPGQ8, R1MACH, XERROR
C
C     Description of Arguments
C         Input
C           F      - external function of one argument for the
C                    integrand PF(X)=F(X)*PPVAL(LDC,C,XI,LXI,K,ID,X,
C                    INPPV)
C           LDC    - leading dimension of matrix C, LDC .GE. K
C           C(I,J) - right Taylor derivatives at XI(J), I=1,K , J=1,LXI
C           XI(*)  - break point array of length LXI+1
C           LXI    - number of polynomial pieces
C           K      - order of B-spline, K .GE. 1
C           ID     - order of the spline derivative, 0 .LE. ID .LE. K-1
C                    ID=0 gives the spline function
C           X1,X2  - end points of quadrature interval, normally in
C                    XI(1) .LE. X .LE. XI(LXI+1)
C           TOL    - desired accuracy for the quadrature, suggest
C                    10.*STOL .LT. TOL .LE. 0.1 where STOL is the single
C                    precision unit roundoff for the machine = R1MACH(4)
C
C         Output
C           QUAD   - integral of PF(X) on (X1,X2)
C           IERR   - a status code
C                    IERR=1 normal return
C                         2 some quadrature does not meet the
C                           requested tolerance
C
C     Error Conditions
C         TOL not greater than the single precision unit roundoff or
C         less than 0.1 is a fatal error.
C         Some quadrature does not meet the requested tolerance.
C***REFERENCES  D.E. AMOS, *QUADRATURE SUBROUTINES FOR SPLINES AND
C                 B-SPLINES*, SAND79-1825, SANDIA LABORATORIES,
C                 DECEMBER 1979.
C***ROUTINES CALLED  INTRV,PPGQ8,R1MACH,XERROR
C***END PROLOGUE  PFQAD
C
C
      INTEGER ID,IERR,IFLG,ILO,IL1,IL2,INPPV,K,LDC,LEFT,LXI,MF1,MF2
      REAL A, AA, ANS, B, BB, C, Q, QUAD, TA, TB, TOL, WTOL, XI, X1, X2
      REAL R1MACH, F
      DIMENSION XI(1), C(LDC,1)
      EXTERNAL F
C
C***FIRST EXECUTABLE STATEMENT  PFQAD
      IERR = 1
      QUAD = 0.0E0
      IF(K.LT.1) GO TO 100
      IF(LDC.LT.K) GO TO 105
      IF(ID.LT.0 .OR. ID.GE.K) GO TO 110
      IF(LXI.LT.1) GO TO 115
      WTOL = R1MACH(4)
      IF (TOL.LT.WTOL .OR. TOL.GT.0.1E0) GO TO 20
      AA = AMIN1(X1,X2)
      BB = AMAX1(X1,X2)
      IF (AA.EQ.BB) RETURN
      ILO = 1
      CALL INTRV(XI, LXI, AA, ILO, IL1, MF1)
      CALL INTRV(XI, LXI, BB, ILO, IL2, MF2)
      Q = 0.0E0
      INPPV = 1
      DO 10 LEFT=IL1,IL2
        TA = XI(LEFT)
        A = AMAX1(AA,TA)
        IF (LEFT.EQ.1) A = AA
        TB = BB
        IF (LEFT.LT.LXI) TB = XI(LEFT+1)
        B = AMIN1(BB,TB)
        CALL PPGQ8(F,LDC,C,XI,LXI,K,ID,A,B,INPPV,TOL,ANS,IFLG)
        IF (IFLG.GT.1) IERR = 2
        Q = Q + ANS
   10 CONTINUE
      IF (X1.GT.X2) Q = -Q
      QUAD = Q
      RETURN
C
   20 CONTINUE
      CALL XERROR( ' PFQAD,  TOL IS LESS THAN THE SINGLE PRECISION TOLER
     1ANCE OR GREATER THAN 0.1', 76, 2, 1)
      RETURN
  100 CONTINUE
      CALL XERROR( ' PFQAD,  K DOES NOT SATISFY K.GE.1', 34, 2, 1)
      RETURN
  105 CONTINUE
      CALL XERROR( ' PFQAD,  LDC DOES NOT SATISFY LDC.GE.K', 38, 2, 1)
      RETURN
  110 CONTINUE
      CALL XERROR( ' PFQAD,  ID DOES NOT SATISFY 0.LE.ID.LT.K', 41,
     1 2, 1)
      RETURN
  115 CONTINUE
      CALL XERROR( ' PFQAD,  LXI DOES NOT SATISFY LXI.GE.1', 38, 2, 1)
      RETURN
      END
