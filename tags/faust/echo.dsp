declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

switch		= checkbox("on/off");
mono2stereo 	=  _ <:  _,_;
dist    	= select2(switch, _, _);

echo1  = hgroup("echo", +~(delay(131072,   int(vslider("time", 0, 0,	2000, 1)*millisec)-1) * (vslider("release", 0, 0,  100, 0.1)/100.0)));
echo2  = vgroup("echo", (mono2stereo : _,echo1:>_ : dist));


process = echo2;



