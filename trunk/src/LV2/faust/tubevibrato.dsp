declare id "tube";

import("stdfaust.lib");
import("guitarix.lib");

vibrato = vslider("vibrato", 0, 0, 2, 0.02);

process = + ~ *(vibrato/2) : sym_clip(0.7);
