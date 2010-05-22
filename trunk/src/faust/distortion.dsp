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

//----------distortion---------

//-speaker emulation
sbp1    = vslider("low_freq[name:low freq][tooltip:low-freq cutoff Hz][old:fslider7]",130,20,1000,10);
sbp2    = vslider("high_freq[name:high freq][tooltip:high-freq cutoff Hz][old:fslider6]",5000,1000,12000,10);
switch1 = checkbox("on_off[name:low highcutoff][old:fcheckbox3]");
sbp = hgroup("low_highcutoff", bypass(switch1, +(anti_denormal_ac) : speakerbp(sbp1,sbp2)));

//-low and highpass
lowpassfreq  = nentry("low_freq[name:low freq][old:fentry0]", 5000, 20, 12000, 10);
highpassfreq = nentry("high_freq[name:high freq][old:fentry1]", 130, 20, 7040, 10);
switch       = checkbox("on_off[name:low highpass][old:fcheckbox2]");
passo = +(anti_denormal_ac) : lowpass1(lowpassfreq) : highpass1(highpassfreq);
pass = hgroup("low_highpass", bypass(switch, passo));

//-distortion
drivelevel      = vslider("level[old:fslider8]", 0.01, 0, 0.5, 0.01);
drivegain1      = vslider("gain[old:fslider10]", 2, -10, 10, 0.1)-10 : db2linear : smoothi(0.999);
drive		= vslider("drive[old:fslider9]", 0.64, 0, 1, 0.01);
distortion 	= cubicnl(drive,drivelevel); 

//-resonator
resonator = (+ <: (delay(4096, d-1) + delay(4096, d)) / 2) ~ *(1.0-a)
with {
  d = vslider("vibrato[old:fslider5]", 1, 0, 1, 0.01);
  a = vslider("trigger[old:fslider4]", 0.12, 0, 1, 0.01);
};
switch2       = checkbox("resonator.on_off[name:resonat]");
//reso = hgroup("resonator", bypass(switch2, resonator));

hs = component("HighShelf.dsp").hs;
process =  bypass(switch2, resonator) : +(anti_denormal_ac) : pass  : sbp : hs : distortion : *(drivegain1) : hs : sbp;
