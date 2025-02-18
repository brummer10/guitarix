declare id "mbd";
declare name "MultiBand Distortion";
declare shortname "MB Distortion";
declare category "Distortion";
declare description "MultiBand Distortion";
declare samplerate "96000";

import("stdfaust.lib");
import("reducemaps.lib");

anti_denormal = pow(10,-20);
anti_denormal_ac = 1 - 1' : *(anti_denormal) : + ~ *(-1);

hifr1      =hslider("crossover_b1_b2 [log][name:Crossover B1-B2 (hz)][tooltip: Crossover fi.bandpass frequency]" ,80 , 20, 20000, 1.08);
hifr2      =hslider("crossover_b2_b3 [log][name:Crossover B2-B3 (hz)][tooltip: Crossover fi.bandpass frequency]",210,20,20000,1.08);
hifr3      =hslider("crossover_b3_b4 [log][name:Crossover B3-B4 (hz)][tooltip: Crossover fi.bandpass frequency]",1700,20,20000,1.08);
hifr4      =hslider("crossover_b4_b5 [log][name:Crossover B4-B5 (hz)][tooltip: Crossover fi.bandpass frequency]",5000,20,20000,1.08);

geq = fi.filterbank(3, (hifr1,hifr2,hifr3,hifr4));

drive1     = hslider("Drive1 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset1    = hslider("Offset1 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
gain_1     = vslider("Gain1", 0, -25, 4, 0.1) : ba.db2linear : si.smooth(0.999);
drive2     = hslider("Drive2 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset2    = hslider("Offset2 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
gain_2     = vslider("Gain2", 0, -25, 4, 0.1) : ba.db2linear : si.smooth(0.999);
drive3     = hslider("Drive3 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset3    = hslider("Offset3 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
gain_3     = vslider("Gain3", 0, -25, 4, 0.1) : ba.db2linear : si.smooth(0.999);
drive4     = hslider("Drive4 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset4    = hslider("Offset4 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
gain_4     = vslider("Gain4", 0, -25, 4, 0.1) : ba.db2linear : si.smooth(0.999);
drive5     = hslider("Drive5 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset5    = hslider("Offset5 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
gain_5     = vslider("Gain5", 0, -25, 4, 0.1) : ba.db2linear : si.smooth(0.999);

gain       = vslider("Gain", 0, -40, 4, 0.1) : ba.db2linear : si.smooth(0.999);

vmeter1(x)		= attach(x, envelop(x) : vbargraph("v1[log][nomidi]", -70, +5));
vmeter2(x)		= attach(x, envelop(x) : vbargraph("v2[log][nomidi]", -70, +5));
vmeter3(x)		= attach(x, envelop(x) : vbargraph("v3[log][nomidi]", -70, +5));
vmeter4(x)		= attach(x, envelop(x) : vbargraph("v4[log][nomidi]", -70, +5));
vmeter5(x)		= attach(x, envelop(x) : vbargraph("v5[log][nomidi]", -70, +5));

envelop         = abs : max ~ (1.0/ma.SR) : mean(4096); // : max(ba.db2linear(-70)) : ba.linear2db;

process    = _: +(anti_denormal_ac): geq: ( dist5s , dist4s , dist3s, dist2s, dist1s) :> *(gain) with { 
    dist1s = ef.cubicnl(drive1,offset1: si.smooth(0.999)) : fi.dcblockerat(1.0) : *(gain_1) : vmeter1;
    dist2s = ef.cubicnl(drive2,offset2: si.smooth(0.999)) : fi.dcblockerat(1.0) : *(gain_2) : vmeter2;
    dist3s = ef.cubicnl(drive3,offset3: si.smooth(0.999)) : fi.dcblockerat(1.0) : *(gain_3) : vmeter3;
    dist4s = ef.cubicnl(drive4,offset4: si.smooth(0.999)) : fi.dcblockerat(1.0) : *(gain_4) : vmeter4;
    dist5s = ef.cubicnl(drive5,offset5: si.smooth(0.999)) : fi.dcblockerat(1.0) : *(gain_5) : vmeter5;
    
};
