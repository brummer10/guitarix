declare name "amp-t12";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */
 
a = 0.75;
r(x) = x-sym_clip(a*0.88);
soft_clip(x) = x:sym_clip(a*0.75) <:+(r(x)*0.333);
hard_clip = sym_clip(0.88);

tubestage(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube4(int,float), "valve.h", "");
    vplus = 130.0;
    divider = 20;
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

process = hgroup("amp2", hgroup("stage1", stage1) : component("gxdistortion.dsp").dist(vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01)) : 
          hgroup("stage2", stage2)  
          ) with {
       
    preamp =  (vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1):db2linear : smoothi(0.999));     
    stage1 = *(preamp): tubestage(0,86.0,2700.0) :
    lowpass1(6531.0) : tubestage(1,132.0,1500.0) :tubestage(1,194.0,820.0) ; 
    stage2 = lowpass1(6531.0) : *(gain1)  <: (tubestage2(1,6531.0,820.0),tubestage2(0,6531.0,820.0)) :> _ 
    with {
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
    } ;
};

