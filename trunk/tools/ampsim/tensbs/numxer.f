      FUNCTION NUMXER(NERR)
C***BEGIN PROLOGUE  NUMXER
C***REFER TO  XERROR
C     Abstract
C        NUMXER returns the most recent error number,
C        in both NUMXER and the parameter NERR.
C
C     Written by Ron Jones, with SLATEC Common Math Library Subcommittee
C     Latest revision ---  7 JUNE 1978
C***REFERENCES  JONES R.E., KAHANER D.K., "XERROR, THE SLATEC ERROR-
C                 HANDLING PACKAGE", SAND82-0800, SANDIA LABORATORIES,
C                 1982.
C***ROUTINES CALLED  J4SAVE
C***END PROLOGUE  NUMXER
C***FIRST EXECUTABLE STATEMENT  NUMXER
      NERR = J4SAVE(1,0,.FALSE.)
      NUMXER = NERR
      RETURN
      END
