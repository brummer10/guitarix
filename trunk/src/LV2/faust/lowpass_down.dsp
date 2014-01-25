import("filter.lib");
import("reduce.lib");
import("guitarix.lib");

vmeter1(x)          = attach(x, envelop(x) : vbargraph("v1[unit:dB]", -70, +5));

envelop             = abs : max ~ (1.0/SR) : reduce(max,4096)  ; // : max(db2linear(-70)) : linear2db;

process =  lowpass(1,5631): highpass(1,80): vmeter1 ;
