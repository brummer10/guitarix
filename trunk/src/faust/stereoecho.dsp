declare name "Stereo Echo";
declare category "Echo / Delay";

import("music.lib");
import("guitarix.lib");
msec	= SR/1000.0;


lfol = component("oscillator.lib").oscrs; // sine for left channel

freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
pingpong   = checkbox("invert[enum:linear|pingpong]");

tl = vslider("time_l", 1, 1, 2000, 1);
releasel = vslider("percent_l", 0, 0,  100, 0.1);
tr = vslider("time_r", 1, 1, 2000, 1);
releaser = vslider("percent_r", 0, 0,  100, 0.1);

echo1  = +~(sdelay(131072, 1024,  int(tl*millisec)-1) * ((releasel/100.0)*(1-(lfol(freq)*pingpong))) );
echo2  = +~(sdelay(131072, 1024,  int(tr*millisec)-1) * ((releaser/100.0)*(1-((-1*lfol(freq))*pingpong))) );
process = echo1,echo2;
