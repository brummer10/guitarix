declare id "mbd";
declare name "MultiBand Distortion";
declare shortname "MB Distortion";
declare category "Distortion";
declare description "MultiBand Distortion";

import("effect.lib");
import("filter.lib");
import("music.lib");
import("math.lib");

anti_denormal = pow(10,-20);
anti_denormal_ac = 1 - 1' : *(anti_denormal) : + ~ *(-1);

hifr1      =hslider("crossover_b1_b2 [log][name:Crossover B1-B2 (hz)][tooltip: Crossover bandpass frequency]" ,80 , 20, 20000, 1.08);
lowfr2     =hifr1;
hifr2      =hslider("crossover_b2_b3 [log][name:Crossover B2-B3 (hz)][tooltip: Crossover bandpass frequency]",210,20,20000,1.08);
lowfr3     =hifr2;
hifr3      =hslider("crossover_b3_b4 [log][name:Crossover B3-B4 (hz)][tooltip: Crossover bandpass frequency]",1700,20,20000,1.08);
lowfr4     =hifr3;
hifr4      =hslider("crossover_b4_b5 [log][name:Crossover B4-B5 (hz)][tooltip: Crossover bandpass frequency]",5000,20,20000,1.08);
lowfr5     =hifr4;

bandpass1  = lowpass(3,hifr1) ;
bandpass2  = lowpass(3,hifr2) : highpass(3,lowfr2);
bandpass3  = lowpass(3,hifr3) : highpass(3,lowfr3);
bandpass4  = lowpass(3,hifr4) : highpass(3,lowfr4);
bandpass5  = highpass(3,lowfr5);

drive1     = hslider("Drive1 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset1    = hslider("Offset1 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
drive2     = hslider("Drive2 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset2    = hslider("Offset2 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
drive3     = hslider("Drive3 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset3    = hslider("Offset3 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
drive4     = hslider("Drive4 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset4    = hslider("Offset4 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);
drive5     = hslider("Drive5 [tooltip: Amount of distortion]", 0, 0, 1, 0.01);
offset5    = hslider("Offset5 [tooltip: Brings in even harmonics]", 0, 0, 0.5, 0.01);

gain1      = vslider("Gain", 0, -40, 4, 0.1) : db2linear : smooth(0.999);

vmeter1(x)		= attach(x, envelop(x-offset1) : vbargraph("v1[unit:dB]", -70, +5));
vmeter2(x)		= attach(x, envelop(x-offset2) : vbargraph("v2[unit:dB]", -70, +5));
vmeter3(x)		= attach(x, envelop(x-offset3) : vbargraph("v3[unit:dB]", -70, +5));
vmeter4(x)		= attach(x, envelop(x-offset4) : vbargraph("v4[unit:dB]", -70, +5));
vmeter5(x)		= attach(x, envelop(x-offset5) : vbargraph("v5[unit:dB]", -70, +5));

envelop         = abs : max ~ (1.0/SR) ; // : max(db2linear(-70)) : linear2db;

process    = _: +(anti_denormal_ac)<: ( dist1s , dist2s , dist3s, dist4s, dist5s) :> *(gain1) with { 
    dist1s = bandpass1:cubicnl(drive1,offset1):vmeter1;
    dist2s = bandpass2:cubicnl(drive2,offset2):vmeter2;
    dist3s = bandpass3:cubicnl(drive3,offset3):vmeter3;
    dist4s = bandpass4:cubicnl(drive4,offset4):vmeter4;
    dist5s = bandpass5:cubicnl(drive5,offset5):vmeter5;
    
};
