declare name 		"moog";
declare license 	"BSD";


import("effect.lib");
import("guitarix.lib");

Q 		= hslider("Q", 1, 0, 4, 0.1);
fr 		= hslider("fr", 3000, 440, 6000, 10): smoothi(0.999);

process = ( +(anti_denormal_ac): moogvcfN(Q,fr)), (+(anti_denormal_ac): moogvcfN(Q,fr));
