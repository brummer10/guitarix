declare name "amp";

import("stdfaust.lib");
import("guitarix.lib");

gain = vslider("out_master[name:out / master]", 0, -40, 40, 0.1) : ba.db2linear : smoothi(0.999);
process = *(gain);
