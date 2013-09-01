      FUNCTION PPVAL(LDC,C,XI,LXI,K,IDERIV,X,INPPV)
C***BEGIN PROLOGUE  PPVAL
C***DATE WRITTEN   800901   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  E3,K6
C***KEYWORDS  B-SPLINE,DATA FITTING,INTERPOLATION,SPLINE
C***AUTHOR  AMOS, D. E., (SNLA)
C***PURPOSE  Calculates (at X) the value of the IDERIV-th derivative
C            of the B-spline from the PP-representation.
C***DESCRIPTION
C
C     Written by Carl de Boor and modified by D. E. Amos
C
C     Reference
C         SIAM J. Numerical Analysis, 14, No. 3, June, 1977, pp.441-472.
C
C     Abstract
C         PPVAL is the PPVALU function of the reference.
C
C         PPVAL calculates (at X) the value of the IDERIV-th
C         derivative of the B-spline from the PP-representation
C         (C,XI,LXI,K).  The Taylor expansion about XI(J) for X in
C         the interval XI(J) .LE. X .LT. XI(J+1) is evaluated, J=1,LXI.
C         Right limiting values at X=XI(J) are obtained.  PPVAL will
C         extrapolate beyond XI(1) and XI(LXI+1).
C
C         To obtain left limiting values (left derivatives) at XI(J),
C         replace LXI by J-1 and set X=XI(J),J=2,LXI+1.
C
C         PPVAL calls INTRV
C
C     Description of Arguments
C         Input
C          LDC     - leading dimension of C matrix, LDC .GE. K
C          C       - matrix of dimension at least (K,LXI) containing
C                    right derivatives at break points XI(*).
C          XI      - break point vector of length LXI+1
C          LXI     - number of polynomial pieces
C          K       - order of B-spline, K .GE. 1
C          IDERIV  - order of the derivative, 0 .LE. IDERIV .LE. K-1
C                    IDERIV=0 gives the B-spline value
C          X       - argument, XI(1) .LE. X .LE. XI(LXI+1)
C          INPPV   - an initialization parameter which must be set
C                    to 1 the first time PPVAL is called.
C
C         Output
C          INPPV   - INPPV contains information for efficient process-
C                    ing after the initial call and INPPV must not
C                    be changed by the user.  Distinct splines require
C                    distinct INPPV parameters.
C          PPVAL   - value of the IDERIV-th derivative at X
C
C     Error Conditions
C         Improper input is a fatal error
C***REFERENCES  C. DE BOOR, *PACKAGE FOR CALCULATING WITH B-SPLINES*,
C                 SIAM JOURNAL ON NUMERICAL ANALYSIS, VOLUME 14, NO. 3,
C                 JUNE 1977, PP. 441-472.
C***ROUTINES CALLED  INTRV,XERROR
C***END PROLOGUE  PPVAL
C
C
      INTEGER I, IDERIV, INPPV, J, K, LDC, LXI, NDUMMY
      REAL C, DX, FLTK, X, XI
      DIMENSION XI(1), C(LDC,LXI)
C***FIRST EXECUTABLE STATEMENT  PPVAL
      PPVAL = 0.0E0
      IF(K.LT.1) GO TO 90
      IF(LDC.LT.K) GO TO 80
      IF(LXI.LT.1) GO TO 85
      IF(IDERIV.LT.0 .OR. IDERIV.GE.K) GO TO 95
      I = K - IDERIV
      FLTK = FLOAT(I)
      CALL INTRV(XI, LXI, X, INPPV, I, NDUMMY)
      DX = X - XI(I)
      J = K
   10 PPVAL = (PPVAL/FLTK)*DX + C(J,I)
      J = J - 1
      FLTK = FLTK - 1.0E0
      IF (FLTK.GT.0.0E0) GO TO 10
      RETURN
C
C
   80 CONTINUE
      CALL XERROR( ' PPVAL,  LDC DOES NOT SATISFY LDC.GE.K', 38, 2, 1)
      RETURN
   85 CONTINUE
      CALL XERROR( ' PPVAL,  LXI DOES NOT SATISFY LXI.GE.1', 38, 2, 1)
      RETURN
   90 CONTINUE
      CALL XERROR( ' PPVAL,  K DOES NOT SATISFY K.GE.1', 34, 2, 1)
      RETURN
   95 CONTINUE
      CALL XERROR( ' PPVAL,  IDERIV DOES NOT SATISFY 0.LE.IDERIV.LT.K',
     1 49, 2, 1)
      RETURN
      END
