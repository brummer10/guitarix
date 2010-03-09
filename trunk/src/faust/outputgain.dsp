declare name "amp";

import("music.lib");
import("guitarix.lib");

gain = vslider("out_master[name:out / master][old:fslider17]", 0, -40, 40, 0.1) : db2linear : smoothi(0.999);
process = *(gain);
