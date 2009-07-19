declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

switch1		= checkbox("on/off");
verb2    	= select2(switch1, _, _);
mono2i 	=  _ <:  _,_;
mono2 	=  _ <:  _,_;


  g3  = hslider("peak gain", 1, 0, 10, 0.2);
 fr = hslider("frequency (Hz)", 440, 20, 2200, 10);
feedbackcontroll = firpart : + ~ feedback 
with {
  bw = hslider("bandwidth (Hz)", 100, 20, 20000, 10);
  //bw = 100; //fr = 440; //g = 1; // parameters - see caption
  SR = fconstant(int fSamplingFreq, <math.h>); // Faust fn
  pi = 4*atan(1.0);    // circumference over diameter
  R = exp(0-pi*bw/SR); // pole radius [0 required]
  A = 2*pi*fr/SR;      // pole angle (radians pole = 2)
  RR = R*R;
  firpart(x) = (x - x'') * g3 * ((1-RR)/2);  // radius = 2
  // time-domain coefficients ASSUMING ONE PIPELINE DELAY:
  feedback(v) = 0 + 2*R*cos(A)*v - RR*v';
};
ir =  hgroup("IR", (mono2i : _,feedbackcontroll:>_ ));
 ImpulseResponse = vgroup("IR", (mono2 : _,ir:>_ : verb2));

process = ImpulseResponse;



