declare id "mbdel";
declare name "MultiBand Delay";
declare shortname "MB Delay";
declare category "Echo / Delay";
declare description "Multi Band Delay";

import("effect.lib");
import("filter.lib");
import("music.lib");
import("math.lib");
import("reduce.lib");

hifr1      =hslider("crossover_b1_b2 [log][name:Crossover B1-B2 (hz)][tooltip: Crossover bandpass frequency]" ,80 , 20, 20000, 1.08);
hifr2      =hslider("crossover_b2_b3 [log][name:Crossover B2-B3 (hz)][tooltip: Crossover bandpass frequency]",210,20,20000,1.08);
hifr3      =hslider("crossover_b3_b4 [log][name:Crossover B3-B4 (hz)][tooltip: Crossover bandpass frequency]",1700,20,20000,1.08);
hifr4      =hslider("crossover_b4_b5 [log][name:Crossover B4-B5 (hz)][tooltip: Crossover bandpass frequency]",5000,20,20000,1.08);

geq = filterbank(3, (hifr1,hifr2,hifr3,hifr4));


interp     = 100*SR/1000.0;
N          = int( 2^18);
g1         = vslider("gain1", -10, -20, 20, 0.1) : db2linear : smooth(0.999);
d1         = tempo(hslider("delay1[tooltip:Delay in Beats per Minute]",30,24,360,1));
g2         = vslider("gain2", -5, -20, 20, 0.1) : db2linear : smooth(0.999);
d2         = tempo(hslider("delay2[tooltip:Delay in Beats per Minute]",60,24,360,1));
g3         = vslider("gain3", -2, -20, 20, 0.1) : db2linear : smooth(0.999);
d3         = tempo(hslider("delay3[tooltip:Delay in Beats per Minute]",90,24,360,1));
g4         = vslider("gain4", 0, -20, 20, 0.1) : db2linear : smooth(0.999);
d4         = tempo(hslider("delay4[tooltip:Delay in Beats per Minute]",120,24,360,1));
g5         = vslider("gain5", -10, -20, 20, 0.1) : db2linear : smooth(0.999);
d5         = tempo(hslider("delay5[tooltip:Delay in Beats per Minute]",150,24,360,1));

del(g,d,f)   = *(g) : (+: sdelay(N, interp,d))~(*(f)) ;

vmeter1(x)		= attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -70, +5));
vmeter2(x)		= attach(x, envelop(x) : vbargraph("v2[nomidi:no]", -70, +5));
vmeter3(x)		= attach(x, envelop(x) : vbargraph("v3[nomidi:no]", -70, +5));
vmeter4(x)		= attach(x, envelop(x) : vbargraph("v4[nomidi:no]", -70, +5));
vmeter5(x)		= attach(x, envelop(x) : vbargraph("v5[nomidi:no]", -70, +5));

f1 = vslider("feedback1[tooltip:percentage of the feedback level in the delay loop]", 50, 1, 100, 1)/100 ;
f2 = vslider("feedback2[tooltip:percentage of the feedback level in the delay loop]", 50, 1, 100, 1)/100 ;
f3 = vslider("feedback3[tooltip:percentage of the feedback level in the delay loop]", 50, 1, 100, 1)/100 ;
f4 = vslider("feedback4[tooltip:percentage of the feedback level in the delay loop]", 50, 1, 100, 1)/100 ;
f5 = vslider("feedback5[tooltip:percentage of the feedback level in the delay loop]", 50, 1, 100, 1)/100 ;


envelop         = abs : max ~ (1.0/SR) : reduce(max,4096) ; // : max(db2linear(-70)) : linear2db;

process    = _<:(geq: ( dist5s , dist4s , dist3s, dist2s, dist1s)),_:>_  with { 
    dist1s = del(g1,d1,f1) : vmeter1;
    dist2s = del(g2,d2,f2) : vmeter2;
    dist3s = del(g3,d3,f3) : vmeter3;
    dist4s = del(g4,d4,f4) : vmeter4;
    dist5s = del(g5,d5,f5) : vmeter5;
    
};
