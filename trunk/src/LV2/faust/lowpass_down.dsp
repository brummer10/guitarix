
import("stdfaust.lib");
import("reducemaps.lib");
import("guitarix.lib");

vmeter1(x)          = attach(x, envelop(x) : vbargraph("v1[unit:dB]", -70, +5));

envelop             = abs : max ~ (1.0/ma.SR) : mean(4096)  ; // : max(ba.db2linear(-70)) : ba.linear2db;

process =  fi.lowpass(1,5631): fi.highpass(1,80): vmeter1 ;
