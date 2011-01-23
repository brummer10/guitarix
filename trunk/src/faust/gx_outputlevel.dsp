declare name "amp";

import("music.lib");
import("guitarix.lib");

gain = vslider("out_master[name:Level]", 0, -50, 4, 0.1) : db2linear : smoothi(0.999);
process = *(gain), *(gain);
