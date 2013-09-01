      SUBROUTINE B3INK(X,NX,Y,NY,Z,NZ,FCN,LDF1,LDF2,KX,KY,KZ,TX,TY,TZ,
     *  BCOEF,WORK,IFLAG)
C***BEGIN PROLOGUE  B3INK
C***DATE WRITTEN   25 MAY 1982
C***REVISION DATE  25 MAY 1982
C***CATEGORY NO.  E1A
C***KEYWORDS  INTERPOLATION, THREE-DIMENSIONS, GRIDDED DATA, SPLINES,
C             PIECEWISE POLYNOMIALS
C***AUTHOR  BOISVERT, RONALD, NBS
C             SCIENTIFIC COMPUTING DIVISION
C             NATIONAL BUREAU OF STANDARDS
C             WASHINGTON, DC 20234
C***PURPOSE  B3INK DETERMINES A PIECEWISE POLYNOMIAL FUNCTION THAT
C            INTERPOLATES THREE-DIMENSIONAL GRIDDED DATA. USERS SPECIFY
C            THE POLYNOMIAL ORDER (DEGREE+1) OF THE INTERPOLANT AND
C            (OPTIONALLY) THE KNOT SEQUENCE.
C***DESCRIPTION
C
C   B3INK determines the parameters of a function that interpolates the
C   three-dimensional gridded data (X(i),Y(j),Z(k),FCN(i,j,k)) for i=1,
C   ..,NX, j=1,..,NY, and k=1,..,NZ. The interpolating function and its
C   derivatives may subsequently be evaluated by the function B3VAL.
C
C   The interpolating  function  is  a  piecewise  polynomial  function
C   represented as a tensor product of one-dimensional  B-splines.  The
C   form of this function is
C
C                      NX   NY   NZ
C        S(x,y,z)  =  SUM  SUM  SUM  a   U (x) V (y) W (z)
C                     i=1  j=1  k=1   ij  i     j     k
C
C   where the functions U(i), V(j), and  W(k)  are  one-dimensional  B-
C   spline basis functions. The coefficients a(i,j) are chosen so that
C
C   S(X(i),Y(j),Z(k)) = FCN(i,j,k)  for i=1,..,NX, j=1,..,NY, k=1,..,NZ
C
C   Note that for fixed values of y  and  z  S(x,y,z)  is  a  piecewise
C   polynomial function of x alone, for fixed values of x and z  S(x,y,
C   z) is a piecewise polynomial function of y  alone,  and  for  fixed
C   values of x and y S(x,y,z)  is  a  function  of  z  alone.  In  one
C   dimension a piecewise polynomial may be created by  partitioning  a
C   given interval into subintervals and defining a distinct polynomial
C   piece on each one. The points where adjacent subintervals meet  are
C   called knots. Each of the functions U(i), V(j), and W(k) above is a
C   piecewise polynomial.
C
C   Users of B3INK choose the order (degree+1) of the polynomial pieces
C   used to define the piecewise polynomial in each of the x, y, and  z
C   directions (KX, KY, and KZ). Users also may define their  own  knot
C   sequence in x, y, and z separately (TX, TY, and  TZ).  If  IFLAG=0,
C   however, B3INK will choose sequences of  knots  that  result  in  a
C   piecewise  polynomial  interpolant  with  KX-2  continuous  partial
C   derivatives in x, KY-2 continuous partial derivatives in y, and KZ-
C   2 continuous partial derivatives in z. (KX  knots  are  taken  near
C   each endpoint in x, not-a-knot end conditions  are  used,  and  the
C   remaining knots are placed at data points  if  KX  is  even  or  at
C   midpoints between data points if KX is odd. The y and z  directions
C   are treated similarly.)
C
C   After a call to B3INK, all  information  necessary  to  define  the
C   interpolating function are contained in the parameters NX, NY,  NZ,
C   KX, KY, KZ, TX, TY, TZ, and BCOEF. These quantities should  not  be
C   altered until after the last call of the evaluation routine B3VAL.
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
C   Z       Real 1D array (size NZ)
C           Array of z abcissae. Must be strictly increasing.
C
C   NZ      Integer scalar (.GE. 3)
C           Number of z abcissae.
C
C   FCN     Real 3D array (size LDF1 by LDF2 by NY)
C           Array of function values to interpolate. FCN(I,J,K) should
C           contain the function value at the point (X(I),Y(J),Z(K))
C
C   LDF1    Integer scalar (.GE. NX)
C           The actual first dimension of FCN used in the
C           calling program.
C
C   LDF2    Integer scalar (.GE. NY)
C           The actual second dimension of FCN used in the calling
C           program.
C
C   KX      Integer scalar (.GE. 2, .LT. NX)
C           The order of spline pieces in x.
C           (Order = polynomial degree + 1)
C
C   KY      Integer scalar (.GE. 2, .LT. NY)
C           The order of spline pieces in y.
C           (Order = polynomial degree + 1)
C
C   KZ      Integer scalar (.GE. 2, .LT. NZ)
C           The order of spline pieces in z.
C           (Order = polynomial degree + 1)
C
C
C   I N P U T   O R   O U T P U T
C   -----------------------------
C
C   TX      Real 1D array (size NX+KX)
C           The knots in the x direction for the spline interpolant.
C           If IFLAG=0 these are chosen by B3INK.
C           If IFLAG=1 these are specified by the user.
C                      (Must be non-decreasing.)
C
C   TY      Real 1D array (size NY+KY)
C           The knots in the y direction for the spline interpolant.
C           If IFLAG=0 these are chosen by B3INK.
C           If IFLAG=1 these are specified by the user.
C                      (Must be non-decreasing.)
C
C   TZ      Real 1D array (size NZ+KZ)
C           The knots in the z direction for the spline interpolant.
C           If IFLAG=0 these are chosen by B3INK.
C           If IFLAG=1 these are specified by the user.
C                      (Must be non-decreasing.)
C
C
C   O U T P U T
C   -----------
C
C   BCOEF   Real 3D array (size NX by NY by NZ)
C           Array of coefficients of the B-spline interpolant.
C           This may be the same array as FCN.
C
C
C   M I S C E L L A N E O U S
C   -------------------------
C
C   WORK    Real 1D array (size NX*NY*NZ + max( 2*KX*(NX+1),
C                             2*KY*(NY+1), 2*KZ*(NZ+1) )
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
C                     11 == NZ out of range
C                     12 == KZ out of range
C                     13 == Z not strictly increasing
C                     14 == TY not non-decreasing
C
C***REFERENCES  CARL DE BOOR, A PRACTICAL GUIDE TO SPLINES,
C                 SPRINGER-VERLAG, NEW YORK, 1978.
C               CARL DE BOOR, EFFICIENT COMPUTER MANIPULATION OF TENSOR
C                 PRODUCTS, ACM TRANSACTIONS ON MATHEMATICAL SOFTWARE,
C                 VOL. 5 (1979), PP. 173-182.
C***ROUTINES CALLED  BTPCF,BKNOT
C***END PROLOGUE  B3INK
C
C  ------------
C  DECLARATIONS
C  ------------
C
C  PARAMETERS
C
      INTEGER
     *        NX, NY, NZ, LDF1, LDF2, KX, KY, KZ, IFLAG
      REAL
     *     X(NX), Y(NY), Z(NZ), FCN(LDF1,LDF2,NY), TX(1), TY(1), TZ(1),
     *     BCOEF(NX,NY,NZ), WORK(1)
C
C  LOCAL VARIABLES
C
      INTEGER
     *        I, J, LOC, IW, NPK
C
C  -----------------------
C  CHECK VALIDITY OF INPUT
C  -----------------------
C
C***FIRST EXECUTABLE STATEMENT
      IF ((IFLAG .LT. 0) .OR. (IFLAG .GT. 1))  GO TO 920
      IF (NX .LT. 3)  GO TO 930
      IF (NY .LT. 3)  GO TO 970
      IF (NZ .LT. 3)  GO TO 1010
      IF ((KX .LT. 2) .OR. (KX .GE. NX))  GO TO 940
      IF ((KY .LT. 2) .OR. (KY .GE. NY))  GO TO 980
      IF ((KZ .LT. 2) .OR. (KZ .GE. NZ))  GO TO 1020
      DO 10 I=2,NX
         IF (X(I) .LE. X(I-1))  GO TO 950
   10 CONTINUE
      DO 20 I=2,NY
         IF (Y(I) .LE. Y(I-1))  GO TO 990
   20 CONTINUE
      DO 30 I=2,NZ
         IF (Z(I) .LE. Z(I-1))  GO TO 1030
   30 CONTINUE
      IF (IFLAG .EQ. 0)  GO TO 70
         NPK = NX + KX
         DO 40 I=2,NPK
            IF (TX(I) .LT. TX(I-1))  GO TO 960
   40    CONTINUE
         NPK = NY + KY
         DO 50 I=2,NPK
            IF (TY(I) .LT. TY(I-1))  GO TO 1000
   50    CONTINUE
         NPK = NZ + KZ
         DO 60 I=2,NPK
            IF (TZ(I) .LT. TZ(I-1))  GO TO 1040
   60    CONTINUE
   70 CONTINUE
C
C  ------------
C  CHOOSE KNOTS
C  ------------
C
      IF (IFLAG .NE. 0)  GO TO 100
         CALL BKNOT(X,NX,KX,TX)
         CALL BKNOT(Y,NY,KY,TY)
         CALL BKNOT(Z,NZ,KZ,TZ)
  100 CONTINUE
C
C  -------------------------------
C  CONSTRUCT B-SPLINE COEFFICIENTS
C  -------------------------------
C
      IFLAG = 1
      IW = NX*NY*NZ + 1
C
C     COPY FCN TO WORK IN PACKED FOR BTPCF
      LOC = 0
      DO 510 K=1,NZ
         DO 510 J=1,NY
            DO 510 I=1,NX
               LOC = LOC + 1
               WORK(LOC) = FCN(I,J,K)
  510 CONTINUE
C
      CALL BTPCF(X,NX,WORK,NX,NY*NZ,TX,KX,BCOEF,WORK(IW))
      CALL BTPCF(Y,NY,BCOEF,NY,NX*NZ,TY,KY,WORK,WORK(IW))
      CALL BTPCF(Z,NZ,WORK,NZ,NX*NY,TZ,KZ,BCOEF,WORK(IW))
      GO TO 9999
C
C  -----
C  EXITS
C  -----
C
  920 CONTINUE
      CALL XERRWV('B3INK -   IFLAG=I1 IS OUT OF RANGE.',
     *            35,2,1,1,IFLAG,I2,0,R1,R2)
      IFLAG = 2
      GO TO 9999
C
  930 CONTINUE
      IFLAG = 3
      CALL XERRWV('B3INK -   NX=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,NX,I2,0,R1,R2)
      GO TO 9999
C
  940 CONTINUE
      IFLAG = 4
      CALL XERRWV('B3INK -   KX=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,KX,I2,0,R1,R2)
      GO TO 9999
C
  950 CONTINUE
      IFLAG = 5
      CALL XERRWV('B3INK -   X ARRAY MUST BE STRICTLY INCREASING.',
     *            46,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
  960 CONTINUE
      IFLAG = 6
      CALL XERRWV('B3INK -   TX ARRAY MUST BE NON-DECREASING.',
     *            42,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
  970 CONTINUE
      IFLAG = 7
      CALL XERRWV('B3INK -   NY=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,NY,I2,0,R1,R2)
      GO TO 9999
C
  980 CONTINUE
      IFLAG = 8
      CALL XERRWV('B3INK -   KY=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,KY,I2,0,R1,R2)
      GO TO 9999
C
  990 CONTINUE
      IFLAG = 9
      CALL XERRWV('B3INK -   Y ARRAY MUST BE STRICTLY INCREASING.',
     *            46,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
 1000 CONTINUE
      IFLAG = 10
      CALL XERRWV('B3INK -   TY ARRAY MUST BE NON-DECREASING.',
     *            42,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
 1010 CONTINUE
      IFLAG = 11
      CALL XERRWV('B3INK -   NZ=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,NZ,I2,0,R1,R2)
      GO TO 9999
C
 1020 CONTINUE
      IFLAG = 12
      CALL XERRWV('B3INK -   KZ=I1 IS OUT OF RANGE.',
     *            32,IFLAG,1,1,KZ,I2,0,R1,R2)
      GO TO 9999
C
 1030 CONTINUE
      IFLAG = 13
      CALL XERRWV('B3INK -   Z ARRAY MUST BE STRICTLY INCREASING.',
     *            46,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
 1040 CONTINUE
      IFLAG = 14
      CALL XERRWV('B3INK -   TZ ARRAY MUST BE NON-DECREASING.',
     *            42,IFLAG,1,0,I1,I2,0,R1,R2)
      GO TO 9999
C
 9999 CONTINUE
      RETURN
      END
