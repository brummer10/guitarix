// Alternate ampout definion for ladspa mono plugin
// This plugin is included instead of gx_ampout, and without
// the PGN_GUI flag. This means no automatic creation of
// the on_off parameter (its always on), so we can define
// it here. It will be of type float instead of bool, but
// this doesn't matter for data read from preset files.

declare groups ".amp";

import("stdfaust.lib");
import("guitarix.lib");

gain = value : ba.db2linear : smoothi(0.999) with {
    slider1 = vslider(".amp.out_amp[name:Level]", 0, -20, 4, 0.1);
    on_off =  checkbox(".amp.on_off[name:use Level]");
    slider2 = vslider(".amp.out_ladspa[name:Ladspa Level]", 0, -20, 20, 0.1);
    value = select2(on_off, slider2, slider1 + slider2);
};

process = *(gain);
