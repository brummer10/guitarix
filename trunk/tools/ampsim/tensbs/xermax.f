      SUBROUTINE XERMAX(MAX)
C***BEGIN PROLOGUE  XERMAX
C***DATE WRITTEN   790801   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  R3C
C***KEYWORDS  ERROR,XERROR PACKAGE
C***AUTHOR  JONES, R. E., (SNLA)
C***PURPOSE  Sets maximum number of times any error message is to be
C            printed.
C***DESCRIPTION
C     Abstract
C        XERMAX sets the maximum number of times any message
C        is to be printed.  That is, non-fatal messages are
C        not to be printed after they have occured MAX times.
C        Such non-fatal messages may be printed less than
C        MAX times even if they occur MAX times, if error
C        suppression mode (KONTRL=0) is ever in effect.
C
C     Description of Parameter
C      --Input--
C        MAX - the maximum number of times any one message
C              is to be printed.
C
C     Written by Ron Jones, with SLATEC Common Math Library Subcommittee
C     Latest revision ---  7 June 1978
C***REFERENCES  JONES R.E., KAHANER D.K., "XERROR, THE SLATEC ERROR-
C                 HANDLING PACKAGE", SAND82-0800, SANDIA LABORATORIES,
C                 1982.
C***ROUTINES CALLED  J4SAVE
C***END PROLOGUE  XERMAX
C***FIRST EXECUTABLE STATEMENT  XERMAX
      JUNK = J4SAVE(4,MAX,.TRUE.)
      RETURN
      END
