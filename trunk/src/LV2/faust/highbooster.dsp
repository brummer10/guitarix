declare name   "Treble boost";
declare category "Tone Control";

import("filter.lib");

level = vslider("Level", 0, 0.5, 20, 0.5) ;
hfboost(level,fx,x) = x + (db2linear(level)-1)*highpass(1,fx,x);

process = hfboost(level, 1500);
