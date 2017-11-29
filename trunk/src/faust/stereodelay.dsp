declare name "Stereo Delay";
declare category "Echo / Delay";

import("stdfaust.lib");
import("guitarix.lib");
msec	= ma.SR/1000.0;

lfol = os.oscrs; // sine for left channel

//freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
freq     = hslider("lfobpm[name:LFO Freq][tooltip:LFO in Beats per Minute]",24,24,360,1)/60;
pingpong   = checkbox("invert[enum:linear|pingpong]");
l_gain = vslider("l_gain[name:Gain L]", 0, -20, 20, 0.1) : ba.db2linear : smoothi(0.999);
r_gain = vslider("r_gain[name:Gain R]", 0, -20, 20, 0.1) : ba.db2linear : smoothi(0.999);
	d       = ba.tempo(hslider("lbpm[name:Delay L][tooltip:Left Delay in Beats per Minute]",120,24,360,1));
r       = ba.tempo(hslider("rbpm[name:Delay R][tooltip:Right Delay in Beats per Minute]",120,24,360,1));
//d = vslider("l_delay", 0, 0, 5000, 10)*msec;
//r = vslider("r_delay", 0, 0, 5000, 10)*msec;
process = (_ <: _ + l_gain*(1-(pingpong*lfol(freq))) * de.sdelay(262144, 1024, d) :> _),
		  (_ <: _ + r_gain*(1-(pingpong*(-1*lfol(freq)))) * de.sdelay(262144, 1024, r) :> _);
