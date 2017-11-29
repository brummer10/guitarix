declare id     "amp.bass_boost";
declare name   "Bassbooster";
declare groups ".bassbooster[Bassbooster]";

import("stdfaust.lib");

//------------------------------------------------------------------
// DAFX, Digital Audio Effects (Wiley ed.)
// chapter 2 : filters
// section 2.3 : Equalizers
// page 53 : second order shelving filter design
//------------------------------------------------------------------

lfboost(F,G) = fi.tf2(b0,b1,b2,a0,a1)
with {
  V = ba.db2linear(G);
  K = tan(ma.PI*F/ma.SR);
  D = 1 + sqrt(2)*K + K*K;

  b0 = (1 + sqrt(2*V)*K + V*K*K) / D;
  b1 = 2 * (V*K*K - 1) / D;
  b2 = (1 - sqrt(2*V)*K + V*K*K) / D;
  a0 = 2 * (K*K - 1) / D;
  a1 = (1 - sqrt(2)*K + K*K) / D;
};
level = vslider(".bassbooster.Level", 10, 0.5, 20, 0.5) : si.smooth(0.9999); 
process = lfboost(120, level);
