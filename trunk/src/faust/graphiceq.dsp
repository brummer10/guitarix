declare id "graphiceq";
declare name "Graphic EQ";
declare category "Tone Control";
declare description "Graphic EQ";

import("stdfaust.lib");
import("reduce.lib");

//geq = fi.filterbank(3, (31.25, 62.5, 125., 250., 500., 1000., 2000., 4000., 8000., 16000.));
geq = fi.filterbank(3, (44., 88., 177., 354., 707., 1414., 2828., 5657., 11384., 18110.));

g1 = vslider("g1[tooltip:gain (dB) below 31.25 Hz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g2 = vslider("g2 [tooltip:gain (dB) at 62.5 Hz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g3 = vslider("g3  [tooltip:gain (dB) at 125 Hz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g4 = vslider("g4  [tooltip:gain (dB) at 250 Hz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g5 = vslider("g5  [tooltip:gain (dB) at 500 Hz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g6 = vslider("g6   [tooltip:gain (dB) at 1 kHz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g7 = vslider("g7   [tooltip:gain (dB) at 2 kHz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g8 = vslider("g8   [tooltip:gain (dB) at 4 kHz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g9 = vslider("g9   [tooltip:gain (dB) at 8 kHz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g10 = vslider("g10  [tooltip:gain (dB) at 16 kHz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);
g11 = vslider("g11  [tooltip:gain (dB) above 16 kHz]", 0, -30, 20, 0.1) : ba.db2linear : si.smooth(0.999);

v1(x)		= attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -70, +5));
v2(x)		= attach(x, envelop(x) : vbargraph("v2[nomidi:no]", -70, +5));
v3(x)		= attach(x, envelop(x) : vbargraph("v3[nomidi:no]", -70, +5));
v4(x)		= attach(x, envelop(x) : vbargraph("v4[nomidi:no]", -70, +5));
v5(x)		= attach(x, envelop(x) : vbargraph("v5[nomidi:no]", -70, +5));

v6(x)		= attach(x, envelop(x) : vbargraph("v6[nomidi:no]", -70, +5));
v7(x)		= attach(x, envelop(x) : vbargraph("v7[nomidi:no]", -70, +5));
v8(x)		= attach(x, envelop(x) : vbargraph("v8[nomidi:no]", -70, +5));
v9(x)		= attach(x, envelop(x) : vbargraph("v9[nomidi:no]", -70, +5));
v10(x)		= attach(x, envelop(x) : vbargraph("v10[nomidi:no]", -70, +5));
v11(x)		= attach(x, envelop(x) : vbargraph("v11[nomidi:no]", -70, +5));

envelop         = abs : max ~ (1.0/ma.SR) : reduce(max,4096) ;

process = geq :(*(g11):v11), (*(g10):v10),(*(g9):v9),(*(g8):v8),(*(g7):v7),(*(g6):v6),
               (*(g5):v5),(*(g4):v4),(*(g3):v3),(*(g2):v2),(*(g1):v1) :>_;
