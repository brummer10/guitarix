declare name "amp";

import("stdfaust.lib");
import("guitarix.lib");

gain = vslider("in_level[name:in / level]", 0, -40, 40, 0.1) : ba.db2linear : smoothi(0.999);
process = *(gain);
