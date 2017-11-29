declare id "6DJ8 feedback"; // in amp tube ba.selector
declare name "6DJ8 feedback";
declare samplerate "96000";

import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */
 
val(x) = valve.vt(dist, q(x), x)
with {
    dist =  40.1;
    q(x) = lp1tm1(x) * 1 - lp2tm1(x) * 1.02 - 1.0 : clip(-1,-0.01);
    lp(a) = *(1 - a) : + ~ *(a);
    lp1tm1 = abs <: lp(0.9999), _ : max;
    avgs = lp1tm1 : avg;
    avg_size = ma.SR/9;
    avg(x) = x - de.delay1s(avg_size,x) : + ~ _ : /(avg_size);
    lp2tm1 = avgs : lp(0.999);
};

tubeax(preamp,gain1) =  hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {
          
    atten = 0.6;
    stage1 = tubestage130_20(TB_6DJ8_68k,86.0,2700.0,1.863946) : - ~ (atten*tubestage130_20(TB_6DJ8_250k,132.0,1500.0,1.271609)) : *(preamp):
    fi.lowpass(1,6531.0) : tubestage130_20(TB_6DJ8_250k,132.0,1500.0,1.271609): + ~ (atten*tubestage130_20(TB_6DJ8_250k,194.0,820.0,0.797043));
    stage2 = fi.lowpass(1,6531.0) : tubestage130_20(TB_6DJ8_250k,194.0,820.0,0.797043) : *(gain1); 
    
};

process = val : component("gxdistortion.dsp").dist1(drive,wet_dry) : tubeax(preamp,gain1) with {
    drive = ampctrl.drive;
    wet_dry = ampctrl.wet_dry;
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
/*
    drive = vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01);
    wet_dry = vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100) : smoothi(0.999);
    preamp =  vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) : ba.db2linear : smoothi(0.999);
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : ba.db2linear : smoothi(0.999);
*/
};
