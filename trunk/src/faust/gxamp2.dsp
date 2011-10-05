declare id "6V6"; // in amp tube selector
declare name "6V6";

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

tubec(preamp,gain1) = hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {
          
    stage1 =  tubestage(TB_6V6_68k,86.0,2700.0,2.296150):
    lowpass1(6531.0) : *(preamp) : tubestage(TB_6V6_250k,132.0,1500.0,1.675587); 
    stage2 = lowpass1(6531.0) : *(gain1) : tubestage(TB_6V6_250k,194.0,820.0,1.130462);
    
};

tubeax(preamp,gain1) = hgroup("stage1", stage1) :
          hgroup("stage2", stage2) 
          with {
          
    stage1 = *(preamp): tubestage(TB_6V6_68k,86.0,2700.0,2.296150): *(0.77) :
    lowpass1(6531.0) : *(preamp) : tubestage(TB_6V6_250k,132.0,1500.0,1.675587): *(0.77); 
    stage2 = lowpass1(6531.0) : *(gain1) : bifilter : tubestage(TB_6V6_250k,194.0,820.0,1.130462) : *(0.77);
    
} ;

process = component("gxdistortion.dsp").dist(drive,wet_dry) : tubeax(preamp,gain1) with {
    drive = ampctrl.drive;
    wet_dry = ampctrl.wet_dry;
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
/*
    drive = vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01);
    wet_dry = vslider(".gxdistortion.wet_dry[alias]",  100, 0, 100, 1) : /(100) : smoothi(0.999);
    preamp =  vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) : db2linear : smoothi(0.999);
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
*/
};
