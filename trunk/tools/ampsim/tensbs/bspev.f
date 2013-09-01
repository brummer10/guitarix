      SUBROUTINE BSPEV(T,AD,N,K,NDERIV,X,INEV,SVALUE,WORK)
C***BEGIN PROLOGUE  BSPEV
C***DATE WRITTEN   800901   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  E3,K6
C***KEYWORDS  B-SPLINE,DATA FITTING,INTERPOLATION,SPLINE
C***AUTHOR  AMOS, D. E., (SNLA)
C***PURPOSE  Calculates the value of the spline and its derivatives at X
C            from the B-representation .
C***DESCRIPTION
C
C     Written by Carl de Boor and modified by D. E. Amos
C
C     Reference
C         SIAM J. Numerical Analysis, 14, No. 3, June, 1977, pp.441-472.
C
C     Abstract
C         BSPEV is the BSPLEV routine of the reference.
C
C         BSPEV calculates the value of the spline and its derivatives
C         at X from the B-representation (T,A,N,K) and returns them
C         in SVALUE(I),I=1,NDERIV, T(K) .LE. X .LE. T(N+1).  AD(I) can
C         be the B-spline coefficients A(I), I=1,N if NDERIV=1.  Other-
C         wise AD must be computed before hand by a call to BSPDR (T,A,
C         N,K,NDERIV,AD).  If X=T(I),I=K,N, right limiting values are
C         obtained.
C
C         To compute left derivatives or left limiting values at a
C         knot T(I), replace N by I-1 and set X=T(I), I=K+1,N+1.
C
C         BSPEV calls INTRV, BSPVN
C
C     Description of Arguments
C         Input
C          T       - knot vector of length N+K
C          AD      - vector of length (2*N-NDERIV+1)*NDERIV/2 containing
C                    the difference table from BSPDR.
C          N       - number of B-spline coefficients
C                    N = sum of knot multiplicities-K
C          K       - order of the B-spline, K .GE. 1
C          NDERIV  - number of derivatives, 1 .LE. NDERIV .LE. K.
C                    NDERIV=1 gives the zero-th derivative = function
C                    value
C          X       - argument, T(K) .LE. X .LE. T(N+1)
C          INEV    - an initialization parameter which must be set
C                    to 1 the first time BSPEV is called.
C
C         Output
C          INEV    - INEV contains information for efficient process-
C                    ing after the initial call and INEV must not
C                    be changed by the user.  Distinct splines require
C                    distinct INEV parameters.
C          SVALUE  - vector of length NDERIV containing the spline
C                    value in SVALUE(1) and the NDERIV-1 derivatives
C                    in the remaining components.
C          WORK    - work vector of length 3*K
C
C     Error Conditions
C         Improper input is a fatal error.
C***REFERENCES  C. DE BOOR, *PACKAGE FOR CALCULATING WITH B-SPLINES*,
C                 SIAM JOURNAL ON NUMERICAL ANALYSIS, VOLUME 14, NO. 3,
C                 JUNE 1977, PP. 441-472.
C***ROUTINES CALLED  BSPVN,INTRV,XERROR
C***END PROLOGUE  BSPEV
C
C
      INTEGER I,ID,INEV,IWORK,JJ,K,KP1,KP1MN,L,LEFT,LL,MFLAG,
     1 N, NDERIV
      REAL AD, SVALUE, SUM, T, WORK, X
C     DIMENSION T(N+K)
      DIMENSION T(1), AD(1), SVALUE(NDERIV), WORK(1)
C***FIRST EXECUTABLE STATEMENT  BSPEV
      IF(K.LT.1) GO TO 100
      IF(N.LT.K) GO TO 105
      IF(NDERIV.LT.1 .OR. NDERIV.GT.K) GO TO 115
      ID = NDERIV
      CALL INTRV(T, N+1, X, INEV, I, MFLAG)
      IF (X.LT.T(K)) GO TO 110
      IF (MFLAG.EQ.0) GO TO 30
      IF (X.GT.T(I)) GO TO 110
   20 IF (I.EQ.K) GO TO 120
      I = I - 1
      IF (X.EQ.T(I)) GO TO 20
C
C *I* HAS BEEN FOUND IN (K,N) SO THAT T(I) .LE. X .LT. T(I+1)
C     (OR .LE. T(I+1), IF T(I) .LT. T(I+1) = T(N+1) ).
   30 KP1MN = K + 1 - ID
      KP1 = K + 1
      CALL BSPVN(T, KP1MN, K, 1, X, I, WORK(1),WORK(KP1),IWORK)
      JJ = (N+N-ID+2)*(ID-1)/2
C     ADIF(LEFTPL,ID) = AD(LEFTPL-ID+1 + (2*N-ID+2)*(ID-1)/2)
C     LEFTPL = LEFT + L
   40 LEFT = I - KP1MN
      SUM = 0.0E0
      LL = LEFT + JJ + 2 - ID
      DO 50 L=1,KP1MN
        SUM = SUM + WORK(L)*AD(LL)
        LL = LL + 1
   50 CONTINUE
      SVALUE(ID) = SUM
      ID = ID - 1
      IF (ID.EQ.0) GO TO 60
      JJ = JJ-(N-ID+1)
      KP1MN = KP1MN + 1
      CALL BSPVN(T, KP1MN, K, 2, X, I, WORK(1), WORK(KP1),IWORK)
      GO TO 40
C
   60 RETURN
C
C
  100 CONTINUE
      CALL XERROR( ' BSPEV,  K DOES NOT SATISFY K.GE.1',34,2,1)
      RETURN
  105 CONTINUE
      CALL XERROR( ' BSPEV,  N DOES NOT SATISFY N.GE.K',34,2,1)
      RETURN
  110 CONTINUE
      CALL XERROR( ' BSPEV,  X IS NOT IN T(K).LE.X.LE.T(N+1)',40,2,1)
      RETURN
  115 CONTINUE
      CALL XERROR( ' BSPEV,  NDERIV DOES NOT SATISFY 1.LE.NDERIV.LE.K',
     1 49, 2, 1)
      RETURN
  120 CONTINUE
      CALL XERROR( ' BSPEV,  A LEFT LIMITING VALUE CANNOT BE OBTAINED AT
     1 T(K)',57,2,1)
      RETURN
      END
