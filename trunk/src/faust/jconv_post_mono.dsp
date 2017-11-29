declare id "jconv_mono";

import("stdfaust.lib");
import("guitarix.lib");

wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;
gain = vslider("gain[name:Gain][tooltip:gain trim for processed signal (unit: dB)]", 0, -20, 20, 0.1) : ba.db2linear : smoothi(0.999);

process = *(dry), (*(wet): *(gain)) :>_ ;
