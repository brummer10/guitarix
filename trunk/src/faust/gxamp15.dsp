declare id "pre 12AT7/ master 6V6"; // in amp tube ba.selector
declare name "pre 12AT7/ master 6V6";
declare samplerate "96000";

import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube amp Emulation stage 1 - 2 - 3
 *  12AT7 -> master 6V6
 */
 
a = 0.75;
r(x) = x-sym_clip(a*0.88);
soft_clip(x) = x:sym_clip(a*0.75) <:+(r(x)*0.333);
hard_clip = sym_clip(0.88);

gx_drive(drive) = _ <: _ + nonlin(4,4,0.125) * drive * 10 ;

process = hgroup("stage1", stage1) : component("gxdistortion.dsp").dist(drive,wet_dry) : 
          hgroup("stage2", stage2)  
          with {
    drive = ampctrl.drive;
    wet_dry = ampctrl.wet_dry;
    preamp = ampctrl.preamp;
/*
    drive = vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01);
    wet_dry = vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100) : smoothi(0.999);
    preamp =  vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) : ba.db2linear : smoothi(0.999);
*/
    stage1 = *(preamp): tubestage(TB_12AT7_68k,86.0,2700.0,2.617753) :
    fi.lowpass(1,6531.0) : tubestage(TB_12AT7_250k,132.0,1500.0,1.887332) :tubestage(TB_12AT7_250k,194.0,820.0,1.256962); 
    stage2 = fi.lowpass(1,6531.0) : *(gain1)  <: (tubestage(TB_6V6_250k,6531.0,820.0,1.130462),tubestage(TB_6V6_68k,6531.0,820.0,1.130740)) :> _ 
    with {
        gain1 = ampctrl.gain1;
    /*
        gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : ba.db2linear : smoothi(0.999);
    */
    } ;
};
