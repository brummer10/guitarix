declare name "Delay";
declare category "Echo / Delay";

import("stdfaust.lib");
import("guitarix.lib");
msec	= ma.SR/1000.0;
gain = vslider("gain", 0, -20, 20, 0.1) : ba.db2linear : smoothi(0.999);
d = vslider("de.delay", 0, 0, 5000, 10)*msec;
process = _ <: _ + gain * de.fdelay5s(d) :> _;
