import("effect.lib");
import("guitarix.lib");

_crybaby(wah) = *(gs(s)) : tf2(1,-1*0.996,0,a1s(s)*0.996,a2s(s)*0.996)
with {
  s = 0.999; // smoothing parameter (one-pole pole location)
  Q  = pow(2.0,(2.0*(1.0-wah)+1.0)); // Resonance "quality factor"
  fr = 450.0*pow(2.0,2.3*wah);       // Resonance tuning
  g  = 0.1*pow(4.0,wah);             // gain (optional)

  // Biquad fit using z = exp(s T) ~ 1 + sT for low frequencies:
  frn = fr/SR; // Normalized pole frequency (cycles per sample)
  R = 1 - PI*frn/Q; // pole radius
  theta = 2*PI*frn; // pole angle
  a1 = 0-2.0*R*cos(theta); // biquad coeff
  a2 = R*R;                // biquad coeff

  // dezippering of slider-driven signals:
  a1s(s) = a1 : smooth(s);
  a2s(s) = a2 : smooth(s);
  gs(s) =  g  : smooth(s);
};

level = vslider("level[old:fslider12]", 0.1, 0, 1, 0.01);
wah = vslider("wah[old:fslider11]", 0, 0, 1, 0.01);
wet_dry = vslider("wet_dry[name:wet/dry][old:fslider13]", 0, -1, 1, 0.1);
process = wet_dry_mix(wet_dry, *(level) : _crybaby(wah));
