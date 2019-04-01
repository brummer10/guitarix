declare id "mbe";
declare name "MultiBand Echo";
declare shortname "MB Echo";
declare category "Echo / Delay";
declare description "Multi Band Echo";

import("stdfaust.lib");
import("reducemaps.lib");

hifr1      =hslider("crossover_b1_b2 [log][name:Crossover B1-B2 (hz)][tooltip: Crossover fi.bandpass frequency]" ,80 , 20, 20000, 1.08);
hifr2      =hslider("crossover_b2_b3 [log][name:Crossover B2-B3 (hz)][tooltip: Crossover fi.bandpass frequency]",210,20,20000,1.08);
hifr3      =hslider("crossover_b3_b4 [log][name:Crossover B3-B4 (hz)][tooltip: Crossover fi.bandpass frequency]",1700,20,20000,1.08);
hifr4      =hslider("crossover_b4_b5 [log][name:Crossover B4-B5 (hz)][tooltip: Crossover fi.bandpass frequency]",5000,20,20000,1.08);

geq = fi.filterbank(3, (hifr1,hifr2,hifr3,hifr4));

      
t1 = ba.tempo(hslider("time1[tooltip:Echo in Beats per Minute]",30,24,360,1));
r1 = hslider("percent1", 10, 0,  100, 0.1)/100.0 : si.smooth(0.999);
t2 = ba.tempo(hslider("time2[tooltip:Echo in Beats per Minute]",60,24,360,1));
r2 = hslider("percent2", 30, 0,  100, 0.1)/100.0 : si.smooth(0.999);
t3 = ba.tempo(hslider("time3[tooltip:Echo in Beats per Minute]",120,24,360,1));
r3 = hslider("percent3", 45, 0,  100, 0.1)/100.0 : si.smooth(0.999);
t4 = ba.tempo(hslider("time4[tooltip:Echo in Beats per Minute]",150,24,360,1));
r4 = hslider("percent4", 20, 0,  100, 0.1)/100.0 : si.smooth(0.999);
t5 = ba.tempo(hslider("time5[tooltip:Echo in Beats per Minute]",240,24,360,1));
r5 = hslider("percent5", 0, 0,  100, 0.1)/100.0 : si.smooth(0.999);

vmeter1(x)		= attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -70, +5));
vmeter2(x)		= attach(x, envelop(x) : vbargraph("v2[nomidi:no]", -70, +5));
vmeter3(x)		= attach(x, envelop(x) : vbargraph("v3[nomidi:no]", -70, +5));
vmeter4(x)		= attach(x, envelop(x) : vbargraph("v4[nomidi:no]", -70, +5));
vmeter5(x)		= attach(x, envelop(x) : vbargraph("v5[nomidi:no]", -70, +5));

envelop         = abs : max ~ (1.0/ma.SR) : mean(4096) ; // : max(ba.db2linear(-70)) : ba.linear2db;

echo1(t,r)  = +~(de.sdelay(int(2^18), 100*ma.SR/1000.0, t) * (r));

process    = geq: ( dist5s , dist4s , dist3s, dist2s, dist1s) :>_ with { 
    dist1s = echo1(t1,r1) : vmeter1 ;
    dist2s = echo1(t2,r2) : vmeter2;
    dist3s = echo1(t3,r3) : vmeter3;
    dist4s = echo1(t4,r4) : vmeter4;
    dist5s = echo1(t5,r5) : vmeter5;
    
};
