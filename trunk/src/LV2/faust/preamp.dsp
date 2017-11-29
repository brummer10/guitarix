//declare name 		"preamp";

import("stdfaust.lib");
import("guitarix.lib");

fatan = vslider("atan[name:drive][tooltip:Input level for pre-amp (higher level gives more distortion)]", 1, 1, 10, 1);
moving_filter(x) = (x+x'+x'')/3;
nonlin1p(x) = (x-0.15*x*x)-(0.15*(x+anti_denormal_ac)*x*x);
nonlin2p(x) = 1.5*x - 0.5*(x+anti_denormal_ac)*x*x;
normalize(fatan) =  1/atan(fatan) * atan(_*fatan);
process =  moving_filter : nonlin1p : nonlin2p : normalize(fatan)*0.75 : moving_filter;
/*
** old definition was:
** moving_filter*0.001 : nonlin1 : nonlin2 : normalize(fatan)*750;
*/
