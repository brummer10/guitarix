//declare name 		"distortion";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");
import("guitarix.lib");
import("maxmsp.lib");


F = nentry("split_low_freq", 250, 20, 600, 10);
F1 = nentry("split_middle_freq", 650, 600, 1250, 10);
F2 = nentry("split_high_freq", 1250, 1250, 12000, 10);

high_s(x) = highShelf(x,F1,G,Q)
with {
    G = -24.;
    Q = 1.;
};

low_s(x) = lowShelf(x,F2,G,Q)
with {
    G = -24.;
    Q = 1.;
};

middle_l_high_s(x) = highShelf(x,F1,G,Q)
with {
    G = -24.;
    Q = 1.;
};

middle_l_low_s(x) = lowShelf(x,F,G,Q)
with {
    G = -24.;
    Q = 1.;
};


middle_h_high_s(x) = highShelf(x,F2,G,Q)
with {
    G = -24.;
    Q = 1.;
};

middle_h_low_s(x) = lowShelf(x,F1,G,Q)
with {
    G = -24.;
    Q = 1.;
};

//----------distortion---------

//-speaker emulation
sbp1    		= vslider("low_freq[name:low freq][tooltip:low-freq cutoff Hz]",130,20,1000,10);
sbp2    		= vslider("high_freq[name:high freq][tooltip:high-freq cutoff Hz]",5000,1000,12000,10);
switch1 		= checkbox("on_off[name:low highcutoff]");
sbp 			= hgroup("low_highcutoff", bypass(switch1, +(anti_denormal_ac) : speakerbp(sbp1,sbp2)));

//-low and highpass
lowpassfreq  	= nentry("low_freq[name:low freq]", 5000, 20, 12000, 10);
highpassfreq 	= nentry("high_freq[name:high freq]", 130, 20, 7040, 10);
switch       	= checkbox("on_off[name:low highpass]");
passo 		 	= +(anti_denormal_ac) : lowpass1(lowpassfreq) : highpass1(highpassfreq);
pass 		 	= hgroup("low_highpass", bypass(switch, passo));

//-distortion
drivelevel      = vslider("level", 0.01, 0, 0.5, 0.01);
drivegain1      = vslider("gain", 2, -10, 10, 0.1)-10 : db2linear : smoothi(0.999);
low_gain      	= vslider("low_gain", 10, -10, 20, 0.1)-10 : db2linear : smoothi(0.999);
high_gain      	= vslider("high_gain", 10, -10, 20, 0.1)-10 : db2linear : smoothi(0.999);
middle_gain_l     = vslider("middle_l_gain", 10, -10, 20, 0.1)-10 : db2linear : smoothi(0.999);
middle_gain_h     = vslider("middle_h_gain", 10, -10, 20, 0.1)-10 : db2linear : smoothi(0.999);
drive			= vslider("drive", 0.64, 0, 1, 0.01);
drive1			= vslider("low_drive", 1, 0, 1, 0.01)*drive;
drive2			= vslider("high_drive", 1, 0, 1, 0.01)*drive;
drive3			= vslider("middle_l_drive", 1, 0, 1, 0.01)*drive;
drive4			= vslider("middle_h_drive", 1, 0, 1, 0.01)*drive;
distortion1 	= high_s : cubicnl(drive1,drivelevel): *(low_gain); 
distortion2 	= low_s : cubicnl(drive2,drivelevel) : *(high_gain);
distortion3 	= middle_h_low_s :middle_h_high_s : cubicnl(drive4,drivelevel) : *(middle_gain_h);
distortion4 	= middle_l_low_s :middle_l_high_s : cubicnl(drive3,drivelevel) : *(middle_gain_l);
distortion(x)	= distortion1(x) + distortion2(x) + distortion3(x)  + distortion4(x); 

//-resonator
resonator 		= (+ <: (delay(4096, d-1) + delay(4096, d)) / 2) ~ *(1.0-a)
with {
  d = vslider("vibrato", 1, 0, 1, 0.01);
  a = vslider("trigger", 0.12, 0, 1, 0.01);
};

switch2       	= checkbox("resonator.on_off[name:resonat]");
//reso 			= hgroup("resonator", bypass(switch2, resonator));

hs 				= component("HighShelf.dsp").hs;
process 		= bypass(switch2, resonator) : +(anti_denormal_ac) : pass  : sbp : hs : distortion : *(drivegain1) : hs : sbp;
