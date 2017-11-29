declare id       "highbooster";
declare name     "Treble Boost";
declare category "Tone Control";

import("stdfaust.lib");

level = vslider("Level[name:Level]", 0.5, 0., 20., 0.5) ;
hfboost(level,fx,x) = x + (ba.db2linear(level)-1)*fi.highpass(1,fx,x);

process = hfboost(level, 1500);
