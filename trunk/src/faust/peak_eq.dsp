declare id 		"eq";
declare name            "Peak EQ";
declare category        "Tone control";
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

process =   peak_eq(vslider("level1 [tooltip:gain (dB)]", 0, -40, 40, 0.1),vslider("peak1 [tooltip:frequency (hz)]", 110, 41, 329, 1),vslider("bandwidth1 [tooltip:frequency (hz)]", 41, 5, 41, 1))
          : peak_eq(vslider("level2 [tooltip:gain (dB)]", 0, -40, 40, 0.1),vslider("peak2 [tooltip:frequency (hz)]", 440, 329, 1318, 1),vslider("bandwidth2 [tooltip:frequency (hz)]", 220, 5, 329, 1))
          : peak_eq(vslider("level3 [tooltip:gain (dB)]", 0, -40, 40, 0.1),vslider("peak3 [tooltip:frequency (hz)]", 1760, 1318, 2637, 1),vslider("bandwidth3 [tooltip:frequency (hz)]", 880, 5, 1318, 1))
          ;
