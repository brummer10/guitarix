declare id "12AU7"; // in amp tube ba.selector
declare name "12AU7";
declare samplerate "96000";

import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

tubeax(preamp,gain1) =  hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {

    stage1 = tubestage(TB_12AU7_68k,86.0,2700.0,3.718962) : *(preamp):*(2.0):
    fi.lowpass(1,6531.0) : tubestage(TB_12AU7_250k,132.0,1500.0,2.314844) : *(preamp) :*(2.0); 
    stage2 = fi.lowpass(1,6531.0) : tubestage(TB_12AU7_250k,194.0,820.0,1.356567) : *(gain1):*(2.0); 

} ;

process = component("gxdistortion.dsp").dist(drive,wet_dry): tubeax(preamp,gain1) with {
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
