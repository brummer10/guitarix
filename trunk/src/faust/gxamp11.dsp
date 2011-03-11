declare name "amp-t11";

import("guitarix.lib");

gx_drive(drive) = _ <: _ + nonlin(4,4,0.125) * drive * 10 ;

process = gx_drive(vslider(".gxdistortion.drive[alias]",0.35, 0, 1, 0.01)) : component("gxamp10.dsp").tubeax(preamp,gain1) with {
    preamp =  (vslider(".amp2.stage1.Pregain[alias]",0,-20,20,0.1) *1.2:db2linear : smoothi(0.999));     
    gain1 = vslider(".amp2.stage2.gain1[alias]", 6, -20.0, 20.0, 0.1)*1.2 : db2linear : smoothi(0.999);
};
