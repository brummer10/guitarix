// Alternate gx_outputlevel definion for ladspa stereo plugin

declare groups ".amp";

import("stdfaust.lib");
import("guitarix.lib");

gain = (slider1 + slider2) : ba.db2linear : smoothi(0.999) with {
    slider1 = vslider(".amp.out_master[name:Level]", 0, -50, 4, 0.1);
    slider2 = vslider(".amp.out_master_ladspa[name:Ladspa Level]", 0, -20, 20, 0.1);
};

process = *(gain), *(gain);
