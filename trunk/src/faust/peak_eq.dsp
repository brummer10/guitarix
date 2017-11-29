declare id 		"eq";
declare name            "Peak EQ";
declare category        "Tone Control";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

import("stdfaust.lib");
import("guitarix.lib");

//------------------------- Process --------------------------------
// USAGE: _ : fi.peak_eq(Lfx,fx,B) : _;
// where
//    Lfx = level (dB) at fx
//     fx = peak frequency (Hz)
//      B = bandwidth (B) of peak in Hz

process =   fi.peak_eq(vslider("level1 [name:Sub][tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak1 [tooltip:frequency (hz)]", 110, 20, 22000, 1),vslider("bandwidth1 [name:Q][tooltip:bandwidth (hz)]", 41, 5, 20000, 1))
          : fi.peak_eq(vslider("level2 [name:Low][tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak2 [tooltip:frequency (hz)]", 440, 20, 22000, 1),vslider("bandwidth2 [name:Q][tooltip:bandwidth (hz)]", 220, 5, 20000, 1))
          : fi.peak_eq(vslider("level3 [name:Mid][tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak3 [tooltip:frequency (hz)]", 1760, 20, 22000, 1),vslider("bandwidth3 [name:Q][tooltip:bandwidth (hz)]", 880, 5, 20000, 1))
          : fi.peak_eq(vslider("level4 [name:High][tooltip:gain (dB)]", 0, -50, 50, 0.1),vslider("peak4 [tooltip:frequency (hz)]", 3520, 20, 22000, 1),vslider("bandwidth4 [name:Q][tooltip:bandwidth (hz)]", 1760, 5, 20000, 1))
          ;
