      REAL FUNCTION B4VAL(XVAL,YVAL,ZVAL,VVAL,IDX,IDY,IDZ,IDV,
     *  TX,TY,TZ,TV,NX,NY,NZ,NV,KX,KY,KZ,KV,BCOEF,WORK)
C***BEGIN PROLOGUE  B4VAL
C***DATE WRITTEN   25 MAY 1982
C***REVISION DATE  25 MAY 1982
C***CATEGORY NO.  E1A
C***KEYWORDS  INTERPOLATION, THREE-DIMENSIONS, GRIDDED DATA, SPLINES,
C             PIECEWISE POLYNOMIALS
C***AUTHOR  BOISVERT, RONALD, NBS
C             SCIENTIFIC COMPUTING DIVISION
C             NATIONAL BUREAU OF STANDARDS
C             WASHINGTON, DC 20234
C***PURPOSE  B4VAL EVALUATES THE PIECEWISE POLYNOMIAL INTERPOLATING
C            FUNCTION CONSTRUCTED BY THE ROUTINE B4INK OR ONE OF ITS
C            PARTIAL DERIVATIVES.
C***DESCRIPTION
C
C   B4VAL evaluates the tensor product piecewise polynomial interpolant
C   constructed by the routine B4INK or one of its derivatives  at  the
C   point (XVAL,YVAL,ZVAL). To evaluate  the  interpolant  itself,  set
C   IDX=IDY=IDZ=0, to evaluate the first partial with respect to x, set
C   IDX=1,IDY=IDZ=0, and so on.
C
C   B4VAL returns 0.0E0 if (XVAL,YVAL,ZVAL) is out of range. That is,
C            XVAL.LT.TX(1) .OR. XVAL.GT.TX(NX+KX) .OR.
C            YVAL.LT.TY(1) .OR. YVAL.GT.TY(NY+NY) .OR.
C            ZVAL.LT.TZ(1) .OR. ZVAL.GT.TZ(NZ+KZ)
C   If the knots TX, TY, and TZ were chosen  by  B4INK,  then  this  is
C   equivalent to
C            XVAL.LT.X(1) .OR. XVAL.GT.X(NX)+EPSX .OR.
C            YVAL.LT.Y(1) .OR. YVAL.GT.Y(NY)+EPSY .OR.
C            ZVAL.LT.Z(1) .OR. ZVAL.GT.Z(NZ)+EPSZ
C   where EPSX = 0.1*(X(NX)-X(NX-1)), EPSY =  0.1*(Y(NY)-Y(NY-1)),  and
C   EPSZ = 0.1*(Z(NZ)-Z(NZ-1)).
C
C   The input quantities TX, TY, TZ, NX, NY, NZ, KX, KY, KZ, and  BCOEF
C   should remain unchanged since the last call of B4INK.
C
C
C   I N P U T
C   ---------
C
C   XVAL    Real scalar
C           X coordinate of evaluation point.
C
C   YVAL    Real scalar
C           Y coordinate of evaluation point.
C
C   ZVAL    Real scalar
C           Z coordinate of evaluation point.
C
C   IDX     Integer scalar
C           X derivative of piecewise polynomial to evaluate.
C
C   IDY     Integer scalar
C           Y derivative of piecewise polynomial to evaluate.
C
C   IDZ     Integer scalar
C           Z derivative of piecewise polynomial to evaluate.
C
C   TX      Real 1D array (size NX+KX)
C           Sequence of knots defining the piecewise polynomial in
C           the x direction.  (Same as in last call to B4INK.)
C
C   TY      Real 1D array (size NY+KY)
C           Sequence of knots defining the piecewise polynomial in
C           the y direction.  (Same as in last call to B4INK.)
C
C   TZ      Real 1D array (size NZ+KZ)
C           Sequence of knots defining the piecewise polynomial in
C           the z direction.  (Same as in last call to B4INK.)
C
C   NX      Integer scalar
C           The number of interpolation points in x.
C           (Same as in last call to B4INK.)
C
C   NY      Integer scalar
C           The number of interpolation points in y.
C           (Same as in last call to B4INK.)
C
C   NZ      Integer scalar
C           The number of interpolation points in z.
C           (Same as in last call to B4INK.)
C
C   KX      Integer scalar
C           Order of polynomial pieces in x.
C           (Same as in last call to B4INK.)
C
C   KY      Integer scalar
C           Order of polynomial pieces in y.
C           (Same as in last call to B4INK.)
C
C   KZ      Integer scalar
C           Order of polynomial pieces in z.
C           (Same as in last call to B4INK.)
C
C   BCOEF   Real 2D array (size NX by NY by NZ)
C           The B-spline coefficients computed by B4INK.
C
C   WORK    Real 1D array (size KY*KZ+3*max(KX,KY,KZ)+KZ)
C           A working storage array.
C
C***REFERENCES  CARL DE BOOR, A PRACTICAL GUIDE TO SPLINES,
C                 SPRINGER-VERLAG, NEW YORK, 1978.
C***ROUTINES CALLED  INTRV,BVALU
C***END PROLOGUE  B4VAL
C
C  ------------
C  DECLARATIONS
C  ------------
C
C  PARAMETERS
C
      INTEGER
     *        IDX, IDY, IDZ, IDV, NX, NY, NZ, NV, KX, KY, KZ, KV
      REAL
     *     XVAL, YVAL, ZVAL, VVAL, TX(1), TY(1), TZ(1), TV(1),
     *     BCOEF(NX,NY,NZ,NV), WORK(1)
C
C  LOCAL VARIABLES
C
      INTEGER
     *        ILOY, ILOZ, ILOV, INBVX, INBV1,
     *        LEFTY, LEFTZ, LEFTV, MFLAG, KCOLY, KCOLZ, KCOLV,
     *        IV, IZ, IZM1, IW, I, J, K, L
      REAL
     *     BVALU
C
      DATA ILOY /1/,  ILOZ /1/,  ILOV /1/, INBVX /1/
C     SAVE ILOY    ,  ILOZ    ,  ILOV    , INBVX
C
C
C***FIRST EXECUTABLE STATEMENT
      B4VAL = 0.0E0
      CALL INTRV(TY,NY+KY,YVAL,ILOY,LEFTY,MFLAG)
      IF (MFLAG .NE. 0)  GO TO 100
      CALL INTRV(TZ,NZ+KZ,ZVAL,ILOZ,LEFTZ,MFLAG)
      IF (MFLAG .NE. 0)  GO TO 100
      CALL INTRV(TV,NV+KV,VVAL,ILOV,LEFTV,MFLAG)
      IF (MFLAG .NE. 0)  GO TO 100
         IV = 1 + KY*KZ*KV
         IW = IV + KZ*KV
         KCOLV = LEFTV - KV
         I = 1
         DO 40 L=1,KV
            KCOLV = KCOLV + 1
            KCOLZ = LEFTZ - KZ
            DO 40 K=1,KZ
               KCOLZ = KCOLZ + 1
               KCOLY = LEFTY - KY
               DO 40 J=1,KY
                  KCOLY = KCOLY + 1
                  WORK(I) = BVALU(TX,BCOEF(1,KCOLY,KCOLZ,KCOLV),NX,KX,
     *                            IDX,XVAL,INBVX,WORK(IW))
                  WRITE (*,'(A, I10, E20.10)') 'I=', I, WORK(I)
                  I = I + 1
 40      CONTINUE
         INBV1 = 1
         KCOLY = LEFTY - KY + 1
         I = 1
         J = IV
         DO 50 L=1,KV
            DO 50 K=1,KZ
               WORK(J) = BVALU(TY(KCOLY),WORK(I),KY,KY,IDY,YVAL,
     *                         INBV1,WORK(IW))
               WRITE (*,'(A, I10, E20.10)') 'J=', J, WORK(J)
               J = J + 1
               I = I + KY
   50    CONTINUE
         INBV1 = 1
         KCOLZ = LEFTZ - KZ + 1
         J = IV
         K = 1
         DO 60 L=1,KV
            WORK(K) = BVALU(TZ(KCOLZ),WORK(J),KZ,KZ,IDZ,ZVAL,
     *                      INBV1,WORK(IW))
            WRITE (*,'(A, I10, E20.10)') 'K=', K, WORK(K)
            K = K + 1
            J = J + KZ
  60     CONTINUE
         INBV1 = 1
         KCOLV = LEFTV - KV + 1
         B4VAL = BVALU(TV(KCOLV),WORK(1),KV,KV,IDV,VVAL,INBV1,WORK(IW))
         WRITE (*,'(A, I10, E20.10)') 'R=', 0, B4VAL
  100 CONTINUE
      RETURN
      END
