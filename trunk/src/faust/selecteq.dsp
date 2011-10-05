declare id 		"eqs";
declare name            "Scaleable EQ";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

import("math.lib");
import("music.lib");
import("guitarix.lib");


//------------------------- Process --------------------------------


process =   ifilter(vslider("Qs31_25", 50, 1, 100, 1),   vslider("freq31_25 [tooltip:Hz]",31, 20, 20000, 1), vslider("fs31_25[tooltip:gain (dB) at 31.25 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs62_5", 50, 1, 100, 1),   vslider("freq62_5 [tooltip:Hz]",62, 20, 20000, 1),  vslider("fs62_5 [tooltip:gain (dB) at 62.5 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs125", 50, 1, 100, 1),  vslider("freq125 [tooltip:Hz]",125., 20, 20000, 1),    vslider("fs125  [tooltip:gain (dB) at 125 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs250", 50, 1, 100, 1),  vslider("freq250 [tooltip:Hz]",250., 20, 20000, 1),    vslider("fs250  [tooltip:gain (dB) at 250 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs500", 50, 1, 100, 1),  vslider("freq500 [tooltip:Hz]",500., 20, 20000, 1),    vslider("fs500  [tooltip:gain (dB) at 500 Hz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs1k", 50, 1, 100, 1), vslider("freq1k [tooltip:Hz]",1000., 20, 20000, 1),    vslider("fs1k   [tooltip:gain (dB) at 1 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs2k", 50, 1, 100, 1), vslider("freq2k [tooltip:Hz]",2000., 20, 20000, 1),    vslider("fs2k   [tooltip:gain (dB) at 2 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs4k", 50, 1, 100, 1), vslider("freq4k [tooltip:Hz]",4000., 20, 20000, 1),    vslider("fs4k   [tooltip:gain (dB) at 4 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs8k", 50, 1, 100, 1), vslider("freq8k [tooltip:Hz]",8000., 20, 20000, 1),    vslider("fs8k   [tooltip:gain (dB) at 8 kHz]", 0, -50, 10, 0.1))
          : ifilter(vslider("Qs16k", 50, 1, 100, 1),vslider("freq16k [tooltip:Hz]",16000., 20, 20000, 1),    vslider("fs16k  [tooltip:gain (dB) at 16 kHz]", 0, -50, 10, 0.1))
          ;
