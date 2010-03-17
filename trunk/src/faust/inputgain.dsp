declare name "amp";

import("music.lib");
import("guitarix.lib");

gain = vslider("in_level[name:in / level][old:fslider3]", 0, -40, 40, 0.1) : db2linear : smoothi(0.999);
process = *(gain);
