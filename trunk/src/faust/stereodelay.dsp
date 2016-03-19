declare name "Stereo Delay";
declare category "Echo / Delay";

import("music.lib");
import("guitarix.lib");
msec	= SR/1000.0;

lfol = component("oscillator.lib").oscrs; // sine for left channel

//freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
freq     = hslider("lfobpm[name:LFO Freq (bpm)][tooltip:LFO in Beats per Minute]",24,24,360,1)/60;
pingpong   = checkbox("invert[enum:linear|pingpong]");
l_gain = vslider("l_gain[name:Left Gain]", 0, -20, 20, 0.1) : db2linear : smoothi(0.999);
r_gain = vslider("r_gain[name:Right Gain]", 0, -20, 20, 0.1) : db2linear : smoothi(0.999);
d       = tempo(hslider("lbpm[name:Left Delay (bpm)][tooltip:Delay in Beats per Minute]",120,24,360,1));
r       = tempo(hslider("rbpm[name:Right Delay (bpm)][tooltip:Delay in Beats per Minute]",120,24,360,1));
//d = vslider("l_delay", 0, 0, 5000, 10)*msec;
//r = vslider("r_delay", 0, 0, 5000, 10)*msec;
process = (_ <: _ + l_gain*(1-(pingpong*lfol(freq))) * sdelay(262144, 1024, d) :> _),
		  (_ <: _ + r_gain*(1-(pingpong*(-1*lfol(freq)))) * sdelay(262144, 1024, r) :> _);

