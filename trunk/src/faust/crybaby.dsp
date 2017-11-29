declare id "manual";
declare name "manual"; // selector crybaby / ve.autowah

import("stdfaust.lib");
import("guitarix.lib");

_crybaby(wah) = *(gs(s)) : fi.tf2(1,-1*0.996,0,a1s(s)*0.996,a2s(s)*0.996)
with {
  s = 0.999; // smoothing parameter (one-fi.pole fi.pole location)
  Q  = pow(2.0,(2.0*(1.0-wah)+1.0)); // Resonance "quality factor"
  fr = 450.0*pow(2.0,2.3*wah);       // Resonance tuning
  g  = 0.1*pow(4.0,wah);             // gain (optional)

  // Biquad fit using z = exp(s T) ~ 1 + sT for low frequencies:
  frn = fr/ma.SR; // Normalized fi.pole frequency (cycles per sample)
  R = 1 - ma.PI*frn/Q; // fi.pole radius
  theta = 2*ma.PI*frn; // fi.pole angle
  a1 = 0-2.0*R*cos(theta); // biquad coeff
  a2 = R*R;                // biquad coeff

  // dezippering of slider-driven signals:
  a1s(s) = a1 : si.smooth(s);
  a2s(s) = a2 : si.smooth(s);
  gs(s) =  g  : si.smooth(s);
};

level   = crybaby_ctrl.level;
wah     = crybaby_ctrl.wah;
wet_dry = crybaby_ctrl.wet_dry;

dry = 1 - wet_dry;

process =  _<:*(dry),(*(wet_dry): *(level) : _crybaby(wah)):>_;
