//declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

t = vslider("time", 1, 1, 2000, 1);
release = vslider("percent", 0, 0,  100, 0.1);

echo1  = +~(delay(131072,   int(t*millisec)-1) * (release/100.0));
process = echo1;
