declare id 		"IR";
declare name            "ImpulseResponse";
declare category        "Tone Control";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("stdfaust.lib");
import("guitarix.lib");

g3  = hslider("peak[name:Peak][tooltip:peak gain]", 1, 0, 10, 0.2);
fr = hslider("freq[name:Freq][tooltip:frequency (Hz)]", 440, 20, 12000, 10);
auto_ir = checkbox("auto_freq[name:auto freq][enum:manual|auto]") : clip(0, 1);

check_auto_ir(v) = select2(auto_ir, v, sym_clip(0.6));

feedbackcontroll(x) = firpart : + ~ feedback 
with {
  bw = hslider("bandwidth[name:Bandwidth][tooltip:bandwidth (Hz)]", 100, 20, 20000, 10);
  R = exp(0-ma.PI*bw/ma.SR); // fi.pole radius [0 required]
  A = 2*ma.PI*fr/ma.SR;      // fi.pole angle (radians fi.pole = 2)
  RR = R*R;
  firpart = (x - x'') * g3 * ((1-RR)/2);  // radius = 2
  // time-domain coefficients ASSUMING ONE PIPELINE DELAY:
  feedback(v) = 0 + R*check_auto_ir(2*cos(A),x)*v - RR*v';
};

process(x) = x + feedbackcontroll(x);
