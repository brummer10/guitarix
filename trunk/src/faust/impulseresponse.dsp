declare name 		"IR";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");
import("guitarix.lib");

g3  = hslider("peak[tooltip:peak gain][old:fslider22]", 1, 0, 10, 0.2);
fr = hslider("freq[tooltip:frequency (Hz)][old:fslider21]", 440, 20, 12000, 10);
auto_ir = checkbox("auto_freq[name:auto freq][old:auto_ir]") : clip(0, 1);

check_auto_ir(v) = select2(auto_ir, v, sym_clip(0.6));

feedbackcontroll(x) = firpart : + ~ feedback 
with {
  bw = hslider("bandwidth[tooltip:bandwidth (Hz)][old:fslider20]", 100, 20, 20000, 10);
  R = exp(0-PI*bw/SR); // pole radius [0 required]
  A = 2*PI*fr/SR;      // pole angle (radians pole = 2)
  RR = R*R;
  firpart = (x - x'') * g3 * ((1-RR)/2);  // radius = 2
  // time-domain coefficients ASSUMING ONE PIPELINE DELAY:
  feedback(v) = 0 + R*check_auto_ir(2*cos(A),x)*v - RR*v';
};

process(x) = x + feedbackcontroll(x);
