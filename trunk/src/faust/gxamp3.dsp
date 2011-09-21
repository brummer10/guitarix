declare name "amp";

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

    stage1 = tubestage(TB_12AU7_68k,86.0,2700.0,3.718962) : *(preamp):*(2.0):
    lowpass1(6531.0) : tubestage(TB_12AU7_250k,132.0,1500.0,2.314844) : *(preamp) :*(2.0); 
    stage2 = lowpass1(6531.0) : tubestage(TB_12AU7_250k,194.0,820.0,1.356567) : *(gain1):*(2.0); 

} ;

process = component("gxdistortion.dsp").dist(drive,wet_dry): tubeax(preamp,gain1) with {
    drive = vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01);
    wet_dry = vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100) : smoothi(0.999);
    preamp =  vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) : db2linear : smoothi(0.999);
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
};
