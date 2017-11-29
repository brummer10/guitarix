declare id "amp";
declare name "Amplifier";

import("stdfaust.lib");
import("guitarix.lib");

gain = vslider(".amp.out_amp[name:Level]", 0, -20, 4, 0.1) : ba.db2linear : smoothi(0.999);
process = *(gain);
