declare name "amp";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");
import("maxmsp.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */


notch1(x) = notch(x,9645.,-12.,14.1);
notch2(x) = notch(x,7890.,-17.,7.1);
notch3(x) = notch(x,5046.,-12.,19.1);

tubestage(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube(int,float), "valve.h", "");
    vplus = 250.0;
    divider = 40;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

tubestage2(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube2(int,float), "valve.h", "");
    vplus = 250.0;
    divider = 40;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

gx_drive(drive) = _ <: _ + nonlin(4,4,0.125) * drive * 10 ;

process = hgroup("amp2", hgroup("stage1", stage1) : 
          component("gxdistortion.dsp").dist2(vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01),vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100)) : 
          hgroup("stage2", stage2)  
          ) with {
       
    preamp =  (vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1):db2linear : smoothi(0.999));     
    stage1 = speakerbp(310.0, 12000.0) :
     *(preamp): (tubestage(0,86.0,2700.0) : + ~ tubestage(1,132.0,1500.0)):
    lowpass1(6531.0) : (tubestage(1,132.0,1500.0) : + ~ tubestage(1,194.0,820.0)) : tubestage(1,194.0,820.0) ; 
    stage2 = lowpass1(6531.0) : *(gain1)  <: ((min(0.7,tubestage2(1,6531.0,410.0))),(max(-0.75,tubestage2(0,6531.0,410.0)))) :> 
    notch1 : notch2 : notch3
    with {
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
    } ;
};

