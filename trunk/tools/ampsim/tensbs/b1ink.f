      SUBROUTINE B1INK(X,NX,FCN,KX,TX,BCOEF,WORK,IFLAG)
C***BEGIN PROLOGUE  B2INK
C***DATE WRITTEN   25 MAY 1982
C***REVISION DATE  25 MAY 1982
C***CATEGORY NO.  E1A
C***KEYWORDS  INTERPOLATION, TWO-DIMENSIONS, GRIDDED DATA, SPLINES,
C             PIECEWISE POLYNOMIALS
C***AUTHOR  BOISVERT, RONALD, NBS
C             SCIENTIFIC COMPUTING DIVISION
C             NATIONAL BUREAU OF STANDARDS
C             WASHINGTON, DC 20234
C***PURPOSE  B2INK DETERMINES A PIECEWISE POLYNOMIAL FUNCTION THAT
C            INTERPOLATES TWO-DIMENSIONAL GRIDDED DATA. USERS SPECIFY
C            THE POLYNOMIAL ORDER (DEGREE+1) OF THE INTERPOLANT AND
C            (OPTIONALLY) THE KNOT SEQUENCE.
C***DESCRIPTION
C
C   B2INK determines the parameters of a function that interpolates the
C   two-dimensional gridded data (X(i),Y(j),FCN(i,j)) for i=1,..,NX and
C   j=1,..,NY. The  interpolating  function  and  its  derivatives  may
C   subsequently be evaluated by the function B2VAL.
C
C   The interpolating  function  is  a  piecewise  polynomial  function
C   represented as a tensor product of one-dimensional  B-splines.  The
C   form of this function is
C
C                          NX   NY
C              S(x,y)  =  SUM  SUM  a   U (x) V (y)
C                         i=1  j=1   ij  i     j
C
C   where the functions U(i)  and  V(j)  are  one-dimensional  B-spline
C   basis functions. The coefficients a(i,j) are chosen so that
C
C         S(X(i),Y(j)) = FCN(i,j)   for i=1,..,NX and j=1,..,NY
C
C   Note that  for  each  fixed  value  of  y  S(x,y)  is  a  piecewise
C   polynomial function of x alone, and for each fixed value of x  S(x,
C   y) is a piecewise polynomial function of y alone. In one  dimension
C   a piecewise polynomial may  be  created  by  partitioning  a  given
C   interval into subintervals and defining a distinct polynomial piece
C   on each one. The points where adjacent subintervals meet are called
C   knots. Each of the functions U(i) and V(j)  above  is  a  piecewise
C   polynomial.
C
C   Users of B2INK choose the order (degree+1) of the polynomial pieces
C   used to define the piecewise polynomial in each  of  the  x  and  y
C   directions (KX and KY).  Users  also  may  define  their  own  knot
C   sequence in x and y separately (TX and TY).  If  IFLAG=0,  however,
C   B2INK will choose sequences of knots that  result  in  a  piecewise
C   polynomial interpolant with KX-2 continuous partial derivatives  in
C   x and KY-2 continuous partial derivatives in y. (KX knots are taken
C   near each endpoint, not-a-knot end conditions  are  used,  and  the
C   remaining knots are placed at data points  if  KX  is  even  or  at
C   midpoints between data points if KX is  odd.  The  y  direction  is
C   treated similarly.)
C
C   After a call to B2INK, all  information  necessary  to  define  the
C   interpolating function are contained in the parameters NX, NY,  KX,
C   KY, TX, TY, and BCOEF. These quantities should not be altered until
C   after the last call of the evaluation routine B2VAL.
C
C
C   I N P U T
C   ---------
C
C   X       Real 1D array (size NX)
C           Array of x abcissae. Must be strictly increasing.
C
C   NX      Integer scalar (.GE. 3)
C           Number of x abcissae.
C
C   Y       Real 1D array (size NY)
C           Array of y abcissae. Must be strictly increasing.
C
C   NY      Integer scalar (.GE. 3)
C           Number of y abcissae.
C
C   FCN     Real 2D array (size LDF by NY)
C           Array of function values to interpolate. FCN(I,J) should
C           contain the function value at the point (X(I),Y(J))
C
C   LDF     Integer scalar (.GE. NX)
C           The actual leading dimension of FCN used in the calling
C           calling program.
C
C   KX      Integer scalar (.GE. 2, .LT. NX)
C           The order of spline pieces in x.
C           (Order = polynomial degree + 1)
C
C   KY      Integer scalar (.GE. 2, .LT. NY)
C           The order of spline pieces in y.
C           (Order = polynomial degree + 1)
C
C
C   I N P U T   O R   O U T P U T
C   -----------------------------
C
C   TX      Real 1D array (size NX+KX)
C           The knots in the x direction for the spline interpolant.
C           If IFLAG=0 these are chosen by B2INK.
C           If IFLAG=1 these are specified by the user.
C                      (Must be non-decreasing.)
C
C   TY      Real 1D array (size NY+KY)
C           The knots in the y direction for the spline interpolant.
C           If IFLAG=0 these are chosen by B2INK.
C           If IFLAG=1 these are specified by the user.
C                      (Must be non-decreasing.)
C
C
C   O U T P U T
C   -----------
C
C   BCOEF   Real 2D array (size NX by NY)
C           Array of coefficients of the B-spline interpolant.
C           This may be the same array as FCN.
C
C
C   M I S C E L L A N E O U S
C   -------------------------
C
C   WORK    Real 1D array (size NX*NY + max( 2*KX*(NX+1),
C                                  2*KY*(NY+1) ))
C           Array of working storage.
C
C   IFLAG   Integer scalar.
C           On input:  0 == knot sequence chosen by B2INK
C                      1 == knot sequence chosen by user.
C           On output: 1 == successful execution
C                      2 == IFLAG out of range
C                      3 == NX out of range
C                      4 == KX out of range
C                      5 == X not strictly increasing
C                      6 == TX not non-decreasing
C                      7 == NY out of range
C                      8 == KY out of range
C                      9 == Y not strictly increasing
C                     10 == TY not non-decreasing
C
C***REFERENCES  CARL DE BOOR, A PRACTICAL GUIDE TO SPLINES,
C                 SPRINGER-VERLAG, NEW YORK, 1978.
C               CARL DE BOOR, EFFICIENT COMPUTER MANIPULATION OF TENSOR
C                 PRODUCTS, ACM TRANSACTIONS ON MATHEMATICAL SOFTWARE,
C                 VOL. 5 (1979), PP. 173-182.
C***ROUTINES CALLED  BTPCF,BKNOT
C***END PROLOGUE  B2INK
C
C  ------------
C  DECLARATIONS
C  ------------
C
C  PARAMETERS
C
      INTEGER
     *        NX, KX, IFLAG
      REAL
     *     X(NX), FCN(NX), TX(NX+KX),
     *     BCOEF(NX), WORK(NX+2*KX*(NX+1))
C
C  LOCAL VARIABLES
C
      INTEGER
     *        I, IW, NPK
C
C  -----------------------
C  CHECK VALIDITY OF INPUT
C  -----------------------
C
C***FIRST EXECUTABLE STATEMENT
      IF ((IFLAG .LT. 0) .OR. (IFLAG .GT. 1))  GO TO 920
      IF (NX .LT. 3)  GO TO 930
      IF ((KX .LT. 2) .OR. (KX .GE. NX))  GO TO 940
      DO 10 I=2,NX
         IF (X(I) .LE. X(I-1))  GO TO 950
   10 CONTINUE
      IF (IFLAG .EQ. 0)  GO TO 50
         NPK = NX + KX
         DO 30 I=2,NPK
            IF (TX(I) .LT. TX(I-1))  GO TO 960
   30    CONTINUE
   50 CONTINUE
C
C  ------------
C  CHOOSE KNOTS
C  ------------
C
      IF (IFLAG .NE. 0)  GO TO 100
         CALL BKNOT(X,NX,KX,TX)
  100 CONTINUE
C
C  -------------------------------
C  CONSTRUCT B-SPLINE COEFFICIENTS
C  -------------------------------
C
      IFLAG = 1
      IW = (2*KX-1)*NX+1
      CALL BINTK(X,FCN,TX,NX,KX,BCOEF,WORK,WORK(IW))
      GO TO 9999
C
C  -----
C  EXITS
C  -----
C
  920 CONTINUE
      CALL XERRWV('B2INK -   IFLAG=I1 IS OUT OF RANGE.',
     *            35,2,1,1,IFLAG,I2,0,R1,R2)
      IFLAG = 2
      GO TO 9999
C
  930 CONTINUE
      IFLAG = 3
      CALL XERRWV('B2INK -   NX=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,NX,I2,0,R1,R2)
      GO TO 9999
C
  940 CONTINUE
      IFLAG = 4
      CALL XERRWV('B2INK -   KX=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,KX,I2,0,R1,R2)
      GO TO 9999
C
  950 CONTINUE
      IFLAG = 5
      CALL XERRWV('B2INK -   X ARRAY MUST BE STRICTLY INCREASING.',
     *            46,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
  960 CONTINUE
      IFLAG = 6
      CALL XERRWV('B2INK -   TX ARRAY MUST BE NON-DECREASING.',
     *            42,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
 9999 CONTINUE
      RETURN
      END
