declare id "12ax7"; // in amp tube selector
declare name "12ax7";

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
    stage1 = tubestage(TB_12AX7_68k,86.0,2700.0,1.581656) : *(preamp):
    lowpass(1,6531.0) : tubestage(TB_12AX7_250k,132.0,1500.0,1.204285) : *(preamp); 
    stage2 = lowpass(1,6531.0) : tubestage(TB_12AX7_250k,194.0,820.0,0.840703) : *(gain1); 
};


process = component("gxdistortion.dsp").dist(drive,wet_dry) : tubeax(preamp,gain1) with {
    drive = ampctrl.drive;
    wet_dry = ampctrl.wet_dry;
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
};
