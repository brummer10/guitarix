declare id 		"eq";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

import("stdfaust.lib");
import("guitarix.lib");

//------------------------- Process --------------------------------

process =   ifilter(vslider("Q31_25", 50, 1, 100, 1),   31.25, vslider("f31_25[tooltip:gain (dB) at 31.25 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q62_5", 50, 1, 100, 1),   62.5,  vslider("f62_5 [tooltip:gain (dB) at 62.5 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q125", 50, 1, 100, 1),  125,    vslider("f125  [tooltip:gain (dB) at 125 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q250", 50, 1, 100, 1),  250,    vslider("f250  [tooltip:gain (dB) at 250 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q500", 50, 1, 100, 1),  500,    vslider("f500  [tooltip:gain (dB) at 500 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q1k", 50, 1, 100, 1), 1000,    vslider("f1k   [tooltip:gain (dB) at 1 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q2k", 50, 1, 100, 1), 2000,    vslider("f2k   [tooltip:gain (dB) at 2 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q4k", 50, 1, 100, 1), 4000,    vslider("f4k   [tooltip:gain (dB) at 4 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q8k", 50, 1, 100, 1), 8000,    vslider("f8k   [tooltip:gain (dB) at 8 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Q16k", 50, 1, 100, 1),16000,    vslider("f16k  [tooltip:gain (dB) at 16 kHz]", 0, -50, 10, 0.1))
          ;
