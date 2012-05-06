declare name "Stereo Echo";
declare category "Echo / Delay";

import("music.lib");
import("guitarix.lib");
msec	= SR/1000.0;



d = vslider("l_delay", 0, 0, 5000, 10)*msec;
r = vslider("r_delay", 0, 0, 5000, 10)*msec;

tl = vslider("time_l", 1, 1, 2000, 1);
releasel = vslider("percent_l", 0, 0,  100, 0.1);
tr = vslider("time_r", 1, 1, 2000, 1);
releaser = vslider("percent_r", 0, 0,  100, 0.1);

echo1  = +~(delay(131072,   int(tl*millisec)-1) * (releasel/100.0) );
echo2  = +~(delay(131072,   int(tr*millisec)-1) * (releaser/100.0) );
process = echo1,echo2;
