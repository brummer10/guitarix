      SUBROUTINE XGETUN(IUNIT)
C***BEGIN PROLOGUE  XGETUN
C***DATE WRITTEN   790801   (YYMMDD)
C***REVISION DATE  820801   (YYMMDD)
C***CATEGORY NO.  R3C
C***KEYWORDS  ERROR,XERROR PACKAGE
C***AUTHOR  JONES, R. E., (SNLA)
C***PURPOSE  Returns the (first) output file to which messages are being
C            sent.
C***DESCRIPTION
C     Abstract
C        XGETUN gets the (first) output file to which error messages
C        are being sent.  To find out if more than one file is being
C        used, one must use the XGETUA routine.
C
C     Description of Parameter
C      --Output--
C        IUNIT - the logical unit number of the  (first) unit to
C                which error messages are being sent.
C                A value of zero means that the default file, as
C                defined by the I1MACH routine, is being used.
C
C     Written by Ron Jones, with SLATEC Common Math Library Subcommittee
C     Latest revision --- 23 May 1979
C***REFERENCES  JONES R.E., KAHANER D.K., "XERROR, THE SLATEC ERROR-
C                 HANDLING PACKAGE", SAND82-0800, SANDIA LABORATORIES,
C                 1982.
C***ROUTINES CALLED  J4SAVE
C***END PROLOGUE  XGETUN
C***FIRST EXECUTABLE STATEMENT  XGETUN
      IUNIT = J4SAVE(3,0,.FALSE.)
      RETURN
      END
