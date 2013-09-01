#ifndef _DATA_H
#define _DATA_H 1

#include "intpp.h"

namespace AmpData {
  extern real b0;
  extern real b1;
  extern real a1;
  extern int fs;

  extern real x0ps[4];
  extern real hps[4];
  extern int kps[4];
  extern int nps[4];
  extern float *tps[4];
  extern float *cps[5];

  extern real x0ppg[2];
  extern real hppg[2];
  extern int kppg[2];
  extern int nppg[2];
  extern float *tppg[2];
  extern float *cppg[2];

  extern real x0ppp[3];
  extern real hppp[3];
  extern int kppp[3];
  extern int nppp[3];
  extern float *tppp[3];
  extern float *cppp[2];

  extern real x0ct[3];
  extern real hct[3];
  extern int kct[3];
  extern int nct[3];
  extern float *tct[3];
  extern float *cct[3];
}

#endif /* !_DATA_H */
