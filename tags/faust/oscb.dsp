declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");
import("osc.lib");

vol 			= hslider("volume (db)", 0, -96, 0, 0.1) : db2linear : smooth(0.999) ;


process = vgroup("Oscillator", oscb(12000));



