declare id "gain";
declare name "Volume";
declare category "Tone Control";
declare description "simple volume control";

import("music.lib");
import("guitarix.lib");

gain = vslider("gain[tooltip:gain (dB)]", 0, -40, 40, 0.1) : db2linear : smoothi(0.999);
process = *(gain);
