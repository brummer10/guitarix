declare id "metal"; // in amp tube selector
declare name "GxMetal_head";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");


t = vslider("tone", 0.5, 0, 1, 0.01);
m = 0.5;
l = 1-t : (_-1)*3.4 : exp;

tstack = component("tonestack.dsp").ts.fender_deville;

tonestack_bm = 1/A0*iir((B0,B1,B2,B3),(A1/A0,A2/A0,A3/A0)) with {
    C1 = tstack.C1;
    C2 = tstack.C2;
    C3 = tstack.C3;
    R1 = tstack.R1;
    R2 = tstack.R2;
    R3 = tstack.R3;
    R4 = tstack.R4;

    b1 = t*C1*R1 + m*C3*R3 + l*(C1*R2 + C2*R2) + (C1*R3 + C2*R3);

    b2 = t*(C1*C2*R1*R4 + C1*C3*R1*R4) - m*m*(C1*C3*R3*R3 + C2*C3*R3*R3)
         + m*(C1*C3*R1*R3 + C1*C3*R3*R3 + C2*C3*R3*R3)
         + l*(C1*C2*R1*R2 + C1*C2*R2*R4 + C1*C3*R2*R4)
         + l*m*(C1*C3*R2*R3 + C2*C3*R2*R3)
         + (C1*C2*R1*R3 + C1*C2*R3*R4 + C1*C3*R3*R4);

    b3 = l*m*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4)
         - m*m*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
         + m*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
         + t*C1*C2*C3*R1*R3*R4 - t*m*C1*C2*C3*R1*R3*R4
         + t*l*C1*C2*C3*R1*R2*R4;

    a0 = 1;

    a1 = (C1*R1 + C1*R3 + C2*R3 + C2*R4 + C3*R4)
         + m*C3*R3 + l*(C1*R2 + C2*R2);

    a2 = m*(C1*C3*R1*R3 - C2*C3*R3*R4 + C1*C3*R3*R3 + C2*C3*R3*R3)
         + l*m*(C1*C3*R2*R3 + C2*C3*R2*R3)
         - m*m*(C1*C3*R3*R3 + C2*C3*R3*R3)
         + l*(C1*C2*R2*R4 + C1*C2*R1*R2 + C1*C3*R2*R4 + C2*C3*R2*R4)
         + (C1*C2*R1*R4 + C1*C3*R1*R4 + C1*C2*R3*R4 + C1*C2*R1*R3 + C1*C3*R3*R4 + C2*C3*R3*R4);

    a3 = l*m*(C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4)
         - m*m*(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4)
         + m*(C1*C2*C3*R3*R3*R4 + C1*C2*C3*R1*R3*R3 - C1*C2*C3*R1*R3*R4)
         + l*C1*C2*C3*R1*R2*R4
         + C1*C2*C3*R1*R3*R4;

    c = 2*float(SR);

    B0 = -b1*c - b2*pow(c,2) - b3*pow(c,3);
    B1 = -b1*c + b2*pow(c,2) + 3*b3*pow(c,3);
    B2 = b1*c + b2*pow(c,2) - 3*b3*pow(c,3);
    B3 = b1*c - b2*pow(c,2) + b3*pow(c,3);
    A0 = -a0 - a1*c - a2*pow(c,2) - a3*pow(c,3);
    A1 = -3*a0 - a1*c + a2*pow(c,2) + 3*a3*pow(c,3);
    A2 = -3*a0 + a1*c + a2*pow(c,2) - 3*a3*pow(c,3);
    A3 = -a0 + a1*c - a2*pow(c,2) + a3*pow(c,3);
};



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

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

tubeax(preamp,gain1) =  hgroup("stage1", stage1)  :
                        hgroup("stage2", stage2) : tonestack_bm :
                        hgroup("stage3", stage3)
                        with {
    stage1 = tubestage(TB_12AX7_68k,86.0,2700.0,1.581656) : *(preamp):
        lowpass(1,6531.0) : tubestage(TB_12AX7_250k,132.0,1500.0,1.204285); 
    stage2 = lowpass(1,6531.0) : tubestage(TB_12AX7_250k,194.0,820.0,0.840703) : *(gain1) ; 
    stage3 = sharper<:(tubestage(TB_6V6_68k,6531.0,410.0,0.664541),
        tubestage(TB_6V6_250k,6531.0,410.0,0.659761)):> lowpass(1,6531.0) ;
};

process = lowpass(1,6531.0) : overdrive(drive) : tubeax(preamp,gain1) : div_drive with {
    drive = vslider("drive", 1, 1, 20, 0.1);
    div_drive = *((drive*-0.4):db2linear : smoothi(0.999));
    preamp = ampctrl.preamp;
    gain1 = ampctrl.gain1;
};
