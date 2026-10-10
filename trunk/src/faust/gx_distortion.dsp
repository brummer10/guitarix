declare id          "gx_distortion";
declare name        "Multi Band Distortion";
declare shortname       "Distortion";
declare category        "Distortion";
declare groups "resonator[Distortion resonator]";

declare gladefile       "gx_distortion_ui.glade";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";


import("stdfaust.lib");
import("guitarix.lib");

F = nentry("split_low_freq[name:Split Lo]", 250, 20, 600, 10);
F1 = nentry("split_middle_freq[name:Split Mid]", 650, 600, 1250, 10);
F2 = nentry("split_high_freq[name:Split Hi]", 1250, 1250, 12000, 10);

//-distortion
offset      = vslider("level[name:Offset][tooltip: Brings in even harmonics]", 0.0, 0, 0.5, 0.01) : smoothi(0.999);
drivegain1      = vslider("gain[name:Gain]", 2, -10, 10, 0.1)-10 : ba.db2linear : smoothi(0.999);
low_gain      	= vslider("low_gain[name:Lo]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
high_gain      	= vslider("high_gain[name:Hi]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
middle_gain_l     = vslider("middle_l_gain[name:LoMid]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
middle_gain_h     = vslider("middle_h_gain[name:HiMid]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
drive			= vslider("drive[name:Drive]", 0.64, 0, 1, 0.01);
drive1			= vslider("low_drive[name:Lo]", 1, 0, 1, 0.01)*drive;
drive2			= vslider("high_drive[name:Hi]", 1, 0, 1, 0.01)*drive;
drive3			= vslider("middle_l_drive[name:LoMid]", 1, 0, 1, 0.01)*drive;
drive4			= vslider("middle_h_drive[name:HiMid]", 1, 0, 1, 0.01)*drive;
distortion1 	=  _:ef.cubicnl_nodc(drive1,offset): *(low_gain);
distortion2 	=  _:ef.cubicnl_nodc(drive2,offset) : *(high_gain);
distortion3 	=  _:ef.cubicnl_nodc(drive3,offset) : *(middle_gain_l);
distortion4 	=  _:ef.cubicnl_nodc(drive4,offset) : *(middle_gain_h);
distortion	= fi.lowpass(2,15000.0): fi.highpass(1,31.0)  : fi.filterbank(3, (F,(F1,F2))) : distortion2,distortion4 ,distortion3,distortion1 :>fi.lowpass(1,6531.0);

//-resonator
resonator 		= (+ <: (de.delay(4096, d-1) + de.delay(4096, d)) / 2) ~ *(1.0-a)
with {
  d = vslider("vibrato[name:Vibrato]", 1, 0, 1, 0.01);
  a = vslider("trigger[name:Trigger]", 0.12, 0, 1, 0.01);
};

switch2       	= checkbox("resonator.on_off[name:resonat]");
//reso 			= hgroup("resonator", bypass(switch2, resonator));
moving_filter(x) = (x+x'+x'')/3;

wet = vslider("wet_dry[name:Wet/Dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;

process_dist 		= bypass(switch2, resonator) : +(anti_denormal_ac) : distortion : *(drivegain1) ;

process = _<:*(dry),(*(wet): process_dist):>_;
