declare name "amp2";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */
 
val(x) = valve.vt(dist, q(x), x)
with {
    dist =  40.1;
    q(x) = lp1tm1(x) * 1 - lp2tm1(x) * 1.02 - 1.0 : clip(-1,-0.01);
    lp(a) = *(1 - a) : + ~ *(a);
    lp1tm1 = abs <: lp(0.9999), _ : max;
    avgs = lp1tm1 : avg;
    avg_size = SR/9;
    avg(x) = x - delay1s(avg_size,x) : + ~ _ : /(avg_size);
    lp2tm1 = avgs : lp(0.999);
};


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
          
    stage1 = tubestage(0,86.0,2700.0) : - ~ tubestage(1,132.0,1500.0) : *(preamp):
    lowpass1(6531.0) : tubestage(1,132.0,1500.0): + ~ tubestage(1,194.0,820.0) ; 
    stage2 = lowpass1(6531.0) : tubestage(1,194.0,820.0) : *(gain1); 
    
} ;


process = val : component("gxdistortion.dsp").dist1(vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01),vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100)) : tubeax(preamp,gain1) with {
    preamp =  (vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1):db2linear : smoothi(0.999));     
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
} ;

