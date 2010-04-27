declare name 		"moog";
declare license 	"BSD";


import("effect.lib");

Q 		= hslider("Q", 1, 0, 4, 0.1);
fr 		= hslider("fr", 3000, 1200, 6000, 10);

process = moogvcf(Q,fr),moogvcf(Q,fr);
