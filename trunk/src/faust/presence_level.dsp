declare id "con";

import("music.lib");
import("guitarix.lib");

gain = vslider("Level[alias]", 1, 0.5, 5, 0.5) ;

process =  *(gain);
