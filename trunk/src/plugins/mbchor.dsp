declare id "mbchor";
declare name "Multi Band Chorus";
declare shortname "MB Chorus";
declare category "Modulation";
declare description "Multi Band Chorus";

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



l1	= hslider("level1", 0.5, 0, 1, 0.01);
f1	= hslider("freq1[tooltip:Beats per Minute]",30,24,360,1)/60;
d1	= hslider("delay1", 0.02, 0, 0.2, 0.01): smooth(0.999);
de1	= hslider("depth1", 0.02, 0.01, 1, 0.01)/10;
l2	= hslider("level2", 0.5, 0, 1, 0.01);
f2	= hslider("freq2[tooltip:Beats per Minute]",60,24,360,1)/60;
d2	= hslider("delay2", 0.04, 0, 0.2, 0.01): smooth(0.999);
de2	= hslider("depth2", 0.04, 0.01, 1, 0.01)/10;
l3	= hslider("level3", 0.5, 0, 1, 0.01);
f3	= hslider("freq3[tooltip:Beats per Minute]",90,24,360,1)/60;
d3	= hslider("delay3", 0.06, 0, 0.2, 0.01): smooth(0.999);
de3	= hslider("depth3", 0.06, 0.01, 1, 0.01)/10;
l4	= hslider("level4", 0.5, 0, 1, 0.01);
f4	= hslider("freq4[tooltip:Beats per Minute]",120,24,360,1)/60;
d4	= hslider("delay4", 0.08, 0, 0.2, 0.01): smooth(0.999);
de4	= hslider("depth4", 0.08, 0.01, 1, 0.01)/10;
l5	= hslider("level5", 0.5, 0, 1, 0.01);
f5	= hslider("freq5[tooltip:Beats per Minute]",150,24,360,1)/60;
d5	= hslider("delay5", 0.10, 0, 0.2, 0.01): smooth(0.999);
de5	= hslider("depth5", 0.10, 0.01, 1, 0.01)/10;

tblosc(n,f,freq,mod)	= (1-d)*rdtable(n,wform,i&(n-1)) +
			  d*rdtable(n,wform,(i+1)&(n-1))
with {
	wform 	= time*(2.0*PI)/n : f;
	phase		= freq/SR : (+ : decimal) ~ _;
	modphase	= decimal(phase+mod/(2*PI))*n;
	i		= int(floor(modphase));
	d		= decimal(modphase);
};

chor(dtime,freq,depth,lev)  = chorus(dtime,freq,depth,lev,0) : *(lev)
with {
chorus(dtime,freq,depth,lev,phase,x)
			= x+lev*fdelay(1<<16, t, x)
with {
	t		= SR*dtime/2*(1+depth*tblosc(1<<16, sin, freq, phase));
};
};

vmeter1(x)		= attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -0, +1));
vmeter2(x)		= attach(x, envelop(x) : vbargraph("v2[nomidi:no]", -0, +1));
vmeter3(x)		= attach(x, envelop(x) : vbargraph("v3[nomidi:no]", -0, +1));
vmeter4(x)		= attach(x, envelop(x) : vbargraph("v4[nomidi:no]", -0, +1));
vmeter5(x)		= attach(x, envelop(x) : vbargraph("v5[nomidi:no]", -0, +1));

envelop         = abs : max ~ (1.0/SR) : reduce(max,4096) ; // : max(db2linear(-70)) : linear2db;

process    = _<:(geq:( dist5s , dist4s , dist3s, dist2s, dist1s)),_ :>_ with { 
    dist1s = chor(d1,f1,de1,l1) : vmeter1;
    dist2s = chor(d2,f2,de2,l2) : vmeter2;
    dist3s = chor(d3,f3,de3,l3) : vmeter3;
    dist4s = chor(d4,f4,de4,l4) : vmeter4;
    dist5s = chor(d5,f5,de5,l5) : vmeter5;
    
};
