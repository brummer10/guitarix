declare id "6DJ8"; // in amp tube selector
declare name "6DJ8";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

tubeax(preamp,gain1) =  hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {
    stage1 = tubestage130_20(TB_6DJ8_68k,86.0,2700.0,1.863946) : *(preamp):
    lowpass1(6531.0) : tubestage130_20(TB_6DJ8_250k,132.0,1500.0,1.271609) : *(preamp) ; 
    stage2 = lowpass1(6531.0) <: ( tubestage130_20(TB_6DJ8_68k,194.0,820.0,0.799031), tubestage130_20(TB_6DJ8_250k,194.0,820.0,0.797043)) :> *(gain1); 
    
} ;

process = component("gxdistortion.dsp").dist(drive,wet_dry): tubeax(preamp,gain1) with {
    drive = ampctrl.drive;
    wet_dry = ampctrl.wet_dry;
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
/*
    drive = vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01);
    wet_dry = vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100) : smoothi(0.999);
    preamp =  vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) : db2linear : smoothi(0.999);
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
*/
};
