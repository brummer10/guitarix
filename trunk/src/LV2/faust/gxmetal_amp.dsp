declare id "metal"; // in amp tube selector
declare name "GxMetal_head";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");



tstack = component("tonestack_bm.dsp");
tone = tstack[tse=tstack.ts.fender_deville;];

overdrive(drive,x) = (x*(abs(x) + drive)/(x*x + (drive-1)*abs(x) + 1)) ;


sharp = 10.0;
press = 5 * sharp;

attack  = 0.005;
release = 10;
knee    = 10.5;
ratio   = 1.5;

env = abs : max(1);

compress(env) = level * (1-r)/r
with {
	level = env : h ~ _ : linear2db : (_ + press) : max(0)
	with {
		h(x,y)  = f*x+(1-f)*y with { f = (x<y)*ga+(x>=y)*gr; };
		ga      = exp(-1/(SR*attack));
		gr      = exp(-1/(SR*release));
	};
	p = level/(knee+eps) : max(0) : min(1) with { eps = 0.001; };
	r = 1 - p + p * ratio;
};

sharper(x) = g(x) * x
with {
	g = env : compress + sharp : db2linear;
};

guitarboost = highpass(3,80)  : peak_eq(-3,200,50): peak_eq(1.5,375,125) : peak_eq(3,2000,500) : peak_eq(-6, 4000, 1000) : peak_eq(2,8000,1000) : lowpass(3,12000) ;

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

tubeax(preamp,gain1) =  hgroup("stage1", stage1)  :
                        hgroup("stage2", stage2) : tone :
                        hgroup("stage3", stage3)
                        with {
    stage1 = tubestage(TB_12AX7_68k,86.0,2700.0,1.581656) : *(preamp):
        lowpass(1,6531.0) : tubestage(TB_12AX7_250k,132.0,1500.0,1.204285); 
    stage2 = lowpass(1,6531.0) : tubestage(TB_12AX7_250k,194.0,820.0,0.840703) : *(gain1) ; 
    stage3 = sharper<:(tubestage(TB_6V6_68k,6531.0,410.0,0.664541),
        tubestage(TB_6V6_250k,6531.0,410.0,0.659761)):> lowpass(1,6531.0) ;
};

process = guitarboost  : overdrive(drive) : tubeax(preamp,gain1) : div_drive with {
    drive = vslider("drive", 1, 1, 20, 0.1);
    div_drive = *((drive*-0.4):db2linear : smoothi(0.999));
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
};
