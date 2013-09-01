      SUBROUTINE XSETUA(IUNITA,N)
C***BEGIN PROLOGUE  XSETUA
C***DATE WRITTEN   790801   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  R3B
C***KEYWORDS  ERROR,XERROR PACKAGE
C***AUTHOR  JONES, R. E., (SNLA)
C***PURPOSE  Sets up to 5 unit numbers to which messages are to be sent.
C***DESCRIPTION
C     Abstract
C        XSETUA may be called to declare a list of up to five
C        logical units, each of which is to receive a copy of
C        each error message processed by this package.
C        The purpose of XSETUA is to allow simultaneous printing
C        of each error message on, say, a main output file,
C        an interactive terminal, and other files such as graphics
C        communication files.
C
C     Description of Parameters
C      --Input--
C        IUNIT - an array of up to five unit numbers.
C                Normally these numbers should all be different
C                (but duplicates are not prohibited.)
C        N     - the number of unit numbers provided in IUNIT
C                must have 1 .LE. N .LE. 5.
C
C     Written by Ron Jones, with SLATEC Common Math Library Subcommittee
C     Latest revision ---  19 MAR 1980
C***REFERENCES  JONES R.E., KAHANER D.K., "XERROR, THE SLATEC ERROR-
C                 HANDLING PACKAGE", SAND82-0800, SANDIA LABORATORIES,
C                 1982.
C***ROUTINES CALLED  J4SAVE,XERRWV
C***END PROLOGUE  XSETUA
      DIMENSION IUNITA(5)
C***FIRST EXECUTABLE STATEMENT  XSETUA
      IF ((N.GE.1).AND.(N.LE.5)) GO TO 10
         CALL XERRWV('XSETUA -- INVALID VALUE OF N (I1).',34,1,2,
     1  1,N,0,0,0.,0.)
         RETURN
   10 CONTINUE
      DO 20 I=1,N
         INDEX = I+4
         IF (I.EQ.1) INDEX = 3
         JUNK = J4SAVE(INDEX,IUNITA(I),.TRUE.)
   20 CONTINUE
      JUNK = J4SAVE(5,N,.TRUE.)
      RETURN
      END
