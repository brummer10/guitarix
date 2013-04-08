declare name "Stereo Delay";
declare category "Echo / Delay";

import("music.lib");
import("guitarix.lib");
msec	= SR/1000.0;

lfol = component("oscillator.lib").oscrs; // sine for left channel

freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
pingpong   = checkbox("invert[enum:linear|pingpong]");
l_gain = vslider("l_gain", 0, -20, 20, 0.1) : db2linear : smoothi(0.999);
r_gain = vslider("r_gain", 0, -20, 20, 0.1) : db2linear : smoothi(0.999);
d = vslider("l_delay", 0, 0, 5000, 10)*msec;
r = vslider("r_delay", 0, 0, 5000, 10)*msec;
process = (_ <: _ + l_gain*(1-(pingpong*lfol(freq))) * sdelay(262144, 1024, d) :> _),
		  (_ <: _ + r_gain*(1-(pingpong*(-1*lfol(freq)))) * sdelay(262144, 1024, r) :> _);

