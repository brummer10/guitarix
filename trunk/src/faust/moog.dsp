declare id      "moog";
declare name    "Moog Filter";
declare category "Tone Control";
declare license "BSD";

import("stdfaust.lib");
import("guitarix.lib");

Q 		= hslider("Q[name:Q]", 1, 0, 4, 0.1);
fr 		= hslider("fr[name:Freq]", 3000, 440, 6000, 10): smoothi(0.999);

process = ( +(anti_denormal_ac): moogvcfN(Q,fr)), (+(anti_denormal_ac): moogvcfN(Q,fr));
