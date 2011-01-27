declare name "ampmodul";

import("guitarix.lib");

feedback = hslider("feedback", 0, -1, 1, 0.01);

fbackw = (- : neg ) ~ (feedback * _'''');

preamp =  (vslider("tube1",0,-20,20,0.1):db2linear : smoothi(0.999)); 
gain1 = vslider("tube2", 6, -20.0, 20.0, 0.1) : db2linear : smoothi(0.999);
gain = vslider("level", -20, -40, 4, 0.1) : db2linear : smoothi(0.999);

process = (*(gain) : component("gxamp2.dsp").tubec(preamp,gain1):fbackw), (*(gain) : component("gxamp2.dsp").tubec(preamp,gain1):fbackw);
