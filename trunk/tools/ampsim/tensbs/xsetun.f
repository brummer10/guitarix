      SUBROUTINE XSETUN(IUNIT)
C***BEGIN PROLOGUE  XSETUN
C***DATE WRITTEN   790801   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  R3B
C***KEYWORDS  ERROR,XERROR PACKAGE
C***AUTHOR  JONES, R. E., (SNLA)
C***PURPOSE  Sets output file to which error messages are to be sent.
C***DESCRIPTION
C     Abstract
C        XSETUN sets the output file to which error messages are to
C        be sent.  Only one file will be used.  See XSETUA for
C        how to declare more than one file.
C
C     Description of Parameter
C      --Input--
C        IUNIT - an input parameter giving the logical unit number
C                to which error messages are to be sent.
C
C     Written by Ron Jones, with SLATEC Common Math Library Subcommittee
C     Latest revision ---  7 June 1978
C***REFERENCES  JONES R.E., KAHANER D.K., "XERROR, THE SLATEC ERROR-
C                 HANDLING PACKAGE", SAND82-0800, SANDIA LABORATORIES,
C                 1982.
C***ROUTINES CALLED  J4SAVE
C***END PROLOGUE  XSETUN
C***FIRST EXECUTABLE STATEMENT  XSETUN
      JUNK = J4SAVE(3,IUNIT,.TRUE.)
      JUNK = J4SAVE(5,1,.TRUE.)
      RETURN
      END
