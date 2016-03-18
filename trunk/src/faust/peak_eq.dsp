declare id 		"eq";
declare name            "Peak EQ";
declare category        "Tone Control";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

import("math.lib");
import("music.lib");
import("guitarix.lib");

//------------------------- Process --------------------------------
// USAGE: _ : peak_eq(Lfx,fx,B) : _;
// where
//    Lfx = level (dB) at fx
//     fx = peak frequency (Hz)
//      B = bandwidth (B) of peak in Hz

process =   peak_eq(vslider("level1 [tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak1 [tooltip:frequency (hz)]", 110, 20, 22000, 1),vslider("bandwidth1 [name:Bandwidth][tooltip:bandwidth (hz)]", 41, 5, 20000, 1))
          : peak_eq(vslider("level2 [tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak2 [tooltip:frequency (hz)]", 440, 20, 22000, 1),vslider("bandwidth2 [name:Bandwidth][tooltip:bandwidth (hz)]", 220, 5, 20000, 1))
          : peak_eq(vslider("level3 [tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak3 [tooltip:frequency (hz)]", 1760, 20, 22000, 1),vslider("bandwidth3 [name:Bandwidth][tooltip:bandwidth (hz)]", 880, 5, 20000, 1))
          : peak_eq(vslider("level4 [tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak4 [tooltip:frequency (hz)]", 3520, 20, 22000, 1),vslider("bandwidth4 [name:Bandwidth][tooltip:bandwidth (hz)]", 1760, 5, 20000, 1))
          ;
