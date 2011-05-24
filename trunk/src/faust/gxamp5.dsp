declare name "amp";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */
 
bifilter = tf2(b0,b1,b2,a1,a2) with
{
    c = 1.059;
    R = 0.9221;
    lc0 = 0.00506158;
    lc1 = 0.06446806;
    lc2 = 0.27547621;
    lc3 = 0.43359433;
    lc4 = 1.31282248;
    lc5 = 0.07238887;
    fc = 1200 : *(2*PI/SR) : log;
    p = lc0*pow(fc,5) + lc1*pow(fc,4) + lc2*pow(fc,3) + lc3*pow(fc,2) + lc4*fc + lc5 : exp;
    //b0 = 1;
    //b1 = -1.01;
    //b2 = 0;
    //a1 = -1.84;
    //a2 = 0.846416;
    b0 = 1;
    b1 = -c;
    b2 = 0;
    a1 = -2*R*cos(p);
    a2 = R*R;
};

tubestage(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube2(int,float), "valve.h", "");
    vplus = 250.0;
    divider = 40;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

tubestage2(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube(int,float), "valve.h", "");
    vplus = 250.0;
    divider = 40;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

process = hgroup("amp2", hgroup("stage1", stage1) : 
          component("gxdistortion.dsp").dist(vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01)) : 
          hgroup("stage2", stage2) 
          ) with {
       
    preamp =  (vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1):db2linear : smoothi(0.999));     
    stage1 = *(preamp): tubestage2(0,86.0,2700.0): 
    lowpass1(6531.0) : tubestage2(1,132.0,1500.0):tubestage2(1,194.0,820.0) ; 
    stage2 = lowpass1(6531.0) : *(gain1)  <: (tubestage(1,6531.0,820.0),tubestage(0,6531.0,820.0)) :>_
    with {
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
    } ;
};
