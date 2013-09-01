      REAL FUNCTION B3VAL(XVAL,YVAL,ZVAL,IDX,IDY,IDZ,TX,TY,TZ,
     *  NX,NY,NZ,KX,KY,KZ,BCOEF,WORK)
C***BEGIN PROLOGUE  B3VAL
C***DATE WRITTEN   25 MAY 1982
C***REVISION DATE  25 MAY 1982
C***CATEGORY NO.  E1A
C***KEYWORDS  INTERPOLATION, THREE-DIMENSIONS, GRIDDED DATA, SPLINES,
C             PIECEWISE POLYNOMIALS
C***AUTHOR  BOISVERT, RONALD, NBS
C             SCIENTIFIC COMPUTING DIVISION
C             NATIONAL BUREAU OF STANDARDS
C             WASHINGTON, DC 20234
C***PURPOSE  B3VAL EVALUATES THE PIECEWISE POLYNOMIAL INTERPOLATING
C            FUNCTION CONSTRUCTED BY THE ROUTINE B3INK OR ONE OF ITS
C            PARTIAL DERIVATIVES.
C***DESCRIPTION
C
C   B3VAL evaluates the tensor product piecewise polynomial interpolant
C   constructed by the routine B3INK or one of its derivatives  at  the
C   point (XVAL,YVAL,ZVAL). To evaluate  the  interpolant  itself,  set
C   IDX=IDY=IDZ=0, to evaluate the first partial with respect to x, set
C   IDX=1,IDY=IDZ=0, and so on.
C
C   B3VAL returns 0.0E0 if (XVAL,YVAL,ZVAL) is out of range. That is,
C            XVAL.LT.TX(1) .OR. XVAL.GT.TX(NX+KX) .OR.
C            YVAL.LT.TY(1) .OR. YVAL.GT.TY(NY+NY) .OR.
C            ZVAL.LT.TZ(1) .OR. ZVAL.GT.TZ(NZ+KZ)
C   If the knots TX, TY, and TZ were chosen  by  B3INK,  then  this  is
C   equivalent to
C            XVAL.LT.X(1) .OR. XVAL.GT.X(NX)+EPSX .OR.
C            YVAL.LT.Y(1) .OR. YVAL.GT.Y(NY)+EPSY .OR.
C            ZVAL.LT.Z(1) .OR. ZVAL.GT.Z(NZ)+EPSZ
C   where EPSX = 0.1*(X(NX)-X(NX-1)), EPSY =  0.1*(Y(NY)-Y(NY-1)),  and
C   EPSZ = 0.1*(Z(NZ)-Z(NZ-1)).
C
C   The input quantities TX, TY, TZ, NX, NY, NZ, KX, KY, KZ, and  BCOEF
C   should remain unchanged since the last call of B3INK.
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
C           the x direction.  (Same as in last call to B3INK.)
C
C   TY      Real 1D array (size NY+KY)
C           Sequence of knots defining the piecewise polynomial in
C           the y direction.  (Same as in last call to B3INK.)
C
C   TZ      Real 1D array (size NZ+KZ)
C           Sequence of knots defining the piecewise polynomial in
C           the z direction.  (Same as in last call to B3INK.)
C
C   NX      Integer scalar
C           The number of interpolation points in x.
C           (Same as in last call to B3INK.)
C
C   NY      Integer scalar
C           The number of interpolation points in y.
C           (Same as in last call to B3INK.)
C
C   NZ      Integer scalar
C           The number of interpolation points in z.
C           (Same as in last call to B3INK.)
C
C   KX      Integer scalar
C           Order of polynomial pieces in x.
C           (Same as in last call to B3INK.)
C
C   KY      Integer scalar
C           Order of polynomial pieces in y.
C           (Same as in last call to B3INK.)
C
C   KZ      Integer scalar
C           Order of polynomial pieces in z.
C           (Same as in last call to B3INK.)
C
C   BCOEF   Real 2D array (size NX by NY by NZ)
C           The B-spline coefficients computed by B3INK.
C
C   WORK    Real 1D array (size KY*KZ+3*max(KX,KY,KZ)+KZ)
C           A working storage array.
C
C***REFERENCES  CARL DE BOOR, A PRACTICAL GUIDE TO SPLINES,
C                 SPRINGER-VERLAG, NEW YORK, 1978.
C***ROUTINES CALLED  INTRV,BVALU
C***END PROLOGUE  B3VAL
C
C  ------------
C  DECLARATIONS
C  ------------
C
C  PARAMETERS
C
      INTEGER
     *        IDX, IDY, IDZ, NX, NY, NZ, KX, KY, KZ
      REAL
     *     XVAL, YVAL, ZVAL, TX(1), TY(1), TZ(1), BCOEF(NX,NY,NZ),
     *     WORK(1)
C
C  LOCAL VARIABLES
C
      INTEGER
     *        ILOY, ILOZ, INBVX, INBV1, INBV2, LEFTY, LEFTZ, MFLAG,
     *        KCOLY, KCOLZ, IZ, IZM1, IW, I, J, K
      REAL
     *     BVALU
C
      DATA ILOY /1/,  ILOZ /1/,  INBVX /1/
C     SAVE ILOY    ,  ILOZ    ,  INBVX
C
C
C***FIRST EXECUTABLE STATEMENT
      B3VAL = 0.0E0
      CALL INTRV(TY,NY+KY,YVAL,ILOY,LEFTY,MFLAG)
      IF (MFLAG .NE. 0)  GO TO 100
      CALL INTRV(TZ,NZ+KZ,ZVAL,ILOZ,LEFTZ,MFLAG)
      IF (MFLAG .NE. 0)  GO TO 100
         IZ = 1 + KY*KZ
         IW = IZ + KZ
         KCOLZ = LEFTZ - KZ
         I = 0
         DO 50 K=1,KZ
            KCOLZ = KCOLZ + 1
            KCOLY = LEFTY - KY
            DO 50 J=1,KY
               I = I + 1
               KCOLY = KCOLY + 1
               WORK(I) = BVALU(TX,BCOEF(1,KCOLY,KCOLZ),NX,KX,IDX,XVAL,
     *                           INBVX,WORK(IW))
   50    CONTINUE
         INBV1 = 1
         IZM1 = IZ - 1
         KCOLY = LEFTY - KY + 1
         DO 60 K=1,KZ
            I = (K-1)*KY + 1
            J = IZM1 + K
            WORK(J) = BVALU(TY(KCOLY),WORK(I),KY,KY,IDY,YVAL,
     *                           INBV1,WORK(IW))
  60     CONTINUE
         INBV2 = 1
         KCOLZ = LEFTZ - KZ + 1
         B3VAL = BVALU(TZ(KCOLZ),WORK(IZ),KZ,KZ,IDZ,ZVAL,INBV2,WORK(IW))
  100 CONTINUE
      RETURN
      END
