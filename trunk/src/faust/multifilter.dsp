declare name 		"MultiBandFilter";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

import("math.lib");
import("music.lib");
import("guitarix.lib");


//------------------------- Process --------------------------------

Q=100;

process =   ifilter(Q,   31.25, vslider("f31_25[tooltip:gain (dB) at 31.25 Hz][old:fslMulti9]", 0, -50, 10, 0.1))
          : ifilter(Q,   62.5,  vslider("f62_5 [tooltip:gain (dB) at 62.5 Hz] [old:fslMulti8]", 0, -50, 10, 0.1))
          : ifilter(Q,  125,    vslider("f125  [tooltip:gain (dB) at 125 Hz]  [old:fslMulti7]", 0, -50, 10, 0.1))
          : ifilter(Q,  250,    vslider("f250  [tooltip:gain (dB) at 250 Hz]  [old:fslMulti6]", 0, -50, 10, 0.1))
          : ifilter(Q,  500,    vslider("f500  [tooltip:gain (dB) at 500 Hz]  [old:fslMulti5]", 0, -50, 10, 0.1))
          : ifilter(Q, 1000,    vslider("f1k   [tooltip:gain (dB) at 1 kHz]   [old:fslMulti4]", 0, -50, 10, 0.1))
          : ifilter(Q, 2000,    vslider("f2k   [tooltip:gain (dB) at 2 kHz]   [old:fslMulti3]", 0, -50, 10, 0.1))
          : ifilter(Q, 4000,    vslider("f4k   [tooltip:gain (dB) at 4 kHz]   [old:fslMulti2]", 0, -50, 10, 0.1))
          : ifilter(Q, 8000,    vslider("f8k   [tooltip:gain (dB) at 8 kHz]   [old:fslMulti1]", 0, -50, 10, 0.1))
          : ifilter(Q,16000,    vslider("f16k  [tooltip:gain (dB) at 16 kHz]  [old:fslMulti0]", 0, -50, 10, 0.1))
          ;
