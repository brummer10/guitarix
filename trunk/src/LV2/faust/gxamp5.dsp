declare id "pre 12ax7/ master 6V6"; // in amp tube ba.selector
declare name "pre 12ax7/ master 6V6";

import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */
 
bifilter = fi.tf2(b0,b1,b2,a1,a2) with
{
    c = 1.059;
    R = 0.9221;
    lc0 = 0.00506158;
    lc1 = 0.06446806;
    lc2 = 0.27547621;
    lc3 = 0.43359433;
    lc4 = 1.31282248;
    lc5 = 0.07238887;
    fc = 1200 : *(2*ma.PI/ma.SR) : log;
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

process = hgroup("stage1", stage1) : 
          component("gxdistortion.dsp").dist(drive,wet_dry) : 
          hgroup("stage2", stage2) 
          with {
    drive = ampctrl.drive;
    wet_dry = ampctrl.wet_dry;
    preamp = ampctrl.preamp;
/*
    drive = vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01);
    wet_dry = vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100) : smoothi(0.999);
    preamp =  vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) : ba.db2linear : smoothi(0.999);
*/
    stage1 = *(preamp): tubestage(TB_12AX7_68k,86.0,2700.0,1.581656):
    fi.lowpass(1,6531.0) : tubestage(TB_12AX7_250k,132.0,1500.0,1.204285):tubestage(TB_12AX7_250k,194.0,820.0,0.840703); 
    stage2 = fi.lowpass(1,6531.0) : *(gain1)  <: (tubestage(TB_6V6_250k,6531.0,820.0,1.130462),tubestage(TB_6V6_68k,6531.0,820.0,1.130740)) :>_
    with {
        gain1 = ampctrl.gain1;
    /*
        gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : ba.db2linear : smoothi(0.999);
    */
    };
};
