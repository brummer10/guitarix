declare id "6C16"; // in amp tube ba.selector
declare name "6C16";
declare samplerate "96000";

import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */
 
tubeax(preamp,gain1) =  hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {
    stage1 = tubestage(TB_6C16_68k,86.0,2700.0,2.921806) : *(preamp):
    fi.lowpass(1,6531.0) : tubestage(TB_6C16_250k,132.0,1500.0,2.097743) : *(preamp); 
    stage2 = fi.lowpass(1,6531.0) : tubestage(TB_6C16_250k,194.0,820.0,1.378742) : *(gain1); 
};

process = component("gxdistortion.dsp").dist(drive,wet_dry) : tubeax(preamp,gain1) with {
    drive = ampctrl.drive;
    wet_dry = ampctrl.wet_dry;
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
};
