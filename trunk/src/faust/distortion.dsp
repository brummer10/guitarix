declare name 		"distortion";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

//----------distortion---------

//-boxes-
switch		= checkbox("on/off");
switch1		= checkbox("on/off");
dist    	= select2(switch, _, _);
echo = _ ;
smoothi(c)	= *(1-c) : +~*(c);

//-speaker emulation
sbp1  = vslider("low-freq cutoff Hz",130,20,1000,1);
sbp2  = vslider("high-freq cutoff Hz",5000,1000,10000,1);
sbpon =  select2(switch1, _, _);
sbp = hgroup("sp",_<:(_, speakerbp(sbp1,sbp2)) : sbpon);

//-low and highpass
lowpassfreq = nentry("freqlow", 723, 20, 7040, 1);  // Hz723.431
highpassfreq = nentry("freqhigh", 720, 20, 7040, 1);  // Hz720.484
passon =  select2(switch1, _, _);
passo = vgroup("",lowpass1(lowpassfreq) : highpass1(highpassfreq ));
pass = hgroup("low/highpass",_<:(_, passo) : passon);

//-distortion
drivelevel = vslider("drivelevel", 0.01, 0, 1, 0.01);
drivegain1		= vslider("gain", 2, 0, 10, 0.1)-10 : db2linear : smoothi(0.999);
//drivegain		= (-8.0) : db2linear : smoothi(0.999);
drive		= vslider("drive[old:fslider9]", 0.64, 0, 1, 0.01);
distortion 	= cubicnl(drive,drivelevel); 

//-resonator
resonator(d,a) 	= (+ <: (delay(4096, d-1) + delay(4096, d))/2.0)~*(1.0-a) ;
d 		= vslider("vibrato[old:fslider5", 1, 0, 1, 0.01);
a 		= vslider("trigger[old:fslider4]", 0.12, 0, 1, 0.01);
reso = vgroup("resonans", resonator(d,a));
pregain		= vslider("pregain", 2, 0, 10, 0.1)-10 : db2linear : smoothi(0.999);

showme		= hgroup("distortion", (_<:*(pregain), (reso :pass : sbp  : distortion : *(drivegain1, echo) : sbp)) : >:_);


process = showme;


//process = _<:_,_;