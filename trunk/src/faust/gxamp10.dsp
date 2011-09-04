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
    Ftube = ffunction(float Ftube4(int,float), "valve.h", "");
    vplus = 130.0;
    divider = 20;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

tubeax(preamp,gain1) =  hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {
          
    stage1 = tubestage(0,86.0,2700.0) : *(preamp):
    lowpass1(6531.0) : tubestage(1,132.0,1500.0) : *(preamp) ; 
    stage2 = lowpass1(6531.0) <: ( tubestage(0,194.0,820.0), tubestage(1,194.0,820.0)) :> *(gain1); 
    
} ;

process = component("gxdistortion.dsp").dist(vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01),vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100)): tubeax(preamp,gain1) with {
    preamp =  vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) : smoothi(0.999) : db2linear;     
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : smoothi(0.999) : db2linear;
};
