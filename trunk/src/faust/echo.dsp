declare name "Echo";
declare category "Echo / Delay";

declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

t = vslider("time", 1, 1, 2000, 1);
release = vslider("percent", 0, 0,  100, 0.1)/100.0 : smooth(0.999);
interp  = 100*millisec;
echo1  = +~(sdelay(131072, interp, int(t*millisec)-1) * (release));
process = echo1;
