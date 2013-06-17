declare name "Delay";
declare category "Echo / Delay";

import("music.lib");
import("guitarix.lib");
msec	= SR/1000.0;
interp  = 100*msec;
N       = int( 2^18);
gain    = vslider("gain", 0, -20, 20, 0.1) : db2linear : smoothi(0.999);
d       = vslider("delay", 0, 0, 5000, 10)*msec;
process = _ <: _ + gain * sdelay(N, interp,d) :> _;
