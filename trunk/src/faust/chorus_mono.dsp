/* mono chorus. */


declare author "Albert Graef";
declare version "1.0";

import("music.lib");

level	= hslider("level", 0.5, 0, 1, 0.01);
freq	= hslider("freq", 2, 0, 10, 0.01);
dtime	= 0.02 ;//hslider("delay", 0.02, 0, 0.2, 0.01);

depth	= 0.02 ;//hslider("depth", 0.02, 0, 1, 0.01);

process			= component("chorus.dsp").chorus(dtime,freq,depth,0);
