declare id "metal"; // in amp tube selector
declare name "GxMetal_head";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");



tstack = component("tonestack_bm.dsp");
tone = tstack[tse=tstack.ts.sovtek;];

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

guitarboost = allpassn(4,(-0.2, 0.3, 0.4, 0.5));

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

tubeax(preamp,gain1) =  hgroup("stage1", stage1)  :
                        hgroup("stage2", stage2) 
                        with {
    stage1 = tubestage(TB_12AY7_68k,86.0,2700.0,2.775058) : *(preamp):
        lowpass(1,6531.0) : tubestage(TB_12AY7_250k,132.0,1500.0,1.954308); 
    stage2 = lowpass(1,6531.0) : tubestage(TB_12AY7_250k,194.0,820.0,1.264916) : *(gain1) : 
        tone : sharper<:( tubestageP(TB_EL34_68k,484.5,10.0,3.5e3, 680.0,230.0, 15.743945),
         tubestageP(TB_EL34_250k,484.5,10.0,3.5e3, 680.0,230.0, 15.743945)):> lowpass(1,6531.0) : *(gain1) ;
};
 //tubestageP(tb,vplus,divider,Rp,fck,Rk,Vk0)
 //tubestage(tb,fck,Rk,Vk0)
process =  overdrive(drive) : tubeax(preamp,gain1) : div_drive with {
    drive = vslider("drive", 1, 1, 20, 0.1);
    div_drive = *((drive*-0.4):db2linear : smoothi(0.999));
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
};
