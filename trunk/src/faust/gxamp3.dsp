declare name "amp";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */


tubestage(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube3(int,float), "valve.h", "");
    vplus = 250.0;
    divider = 40;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

tubeax(preamp,gain1) =  hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {
          
    stage1 = tubestage(0,86.0,2700.0) : *(preamp):*(2.0):
    lowpass1(6531.0) : tubestage(1,132.0,1500.0) : *(preamp) :*(2.0); 
    stage2 = lowpass1(6531.0) : tubestage(1,194.0,820.0) : *(gain1):*(2.0); 
    
} ;

process = component("gxdistortion.dsp").dist(vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01),vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100)): tubeax(preamp,gain1) with {
    preamp =  (vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1):db2linear : smoothi(0.999));     
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
};
