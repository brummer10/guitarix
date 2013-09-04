declare id "mbe";
declare name "MultiBand Echo";
declare shortname "MB Echo";
declare category "Echo / Delay";
declare description "Multi Band Echo";

import("effect.lib");
import("filter.lib");
import("music.lib");
import("math.lib");

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

      
t1 = tempo(hslider("time1[tooltip:Echo in Beats per Minute]",30,24,360,1));
r1 = hslider("percent1", 10, 0,  100, 0.1)/100.0 : smooth(0.999);
t2 = tempo(hslider("time2[tooltip:Echo in Beats per Minute]",60,24,360,1));
r2 = hslider("percent2", 30, 0,  100, 0.1)/100.0 : smooth(0.999);
t3 = tempo(hslider("time3[tooltip:Echo in Beats per Minute]",120,24,360,1));
r3 = hslider("percent3", 45, 0,  100, 0.1)/100.0 : smooth(0.999);
t4 = tempo(hslider("time4[tooltip:Echo in Beats per Minute]",150,24,360,1));
r4 = hslider("percent4", 20, 0,  100, 0.1)/100.0 : smooth(0.999);
t5 = tempo(hslider("time5[tooltip:Echo in Beats per Minute]",240,24,360,1));
r5 = hslider("percent5", 0, 0,  100, 0.1)/100.0 : smooth(0.999);

echo1(t,r)  = +~(sdelay(int(2^18), 100*SR/1000.0, t) * (r));

process    = _<: ( dist1s , dist2s , dist3s, dist4s, dist5s) :>_ with { 
    dist1s = bandpass1:echo1(t1,r1);
    dist2s = bandpass2:echo1(t2,r2);
    dist3s = bandpass3:echo1(t3,r3);
    dist4s = bandpass4:echo1(t4,r4);
    dist5s = bandpass5:echo1(t5,r5);
    
};
