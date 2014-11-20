declare id "mbe";
declare name "MultiBand Reverb";
declare shortname "MB Reverb";
declare category "Reverb";
declare description "Multi Band Reverb";

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

vmeter1(x)		= attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -70, +5));
vmeter2(x)		= attach(x, envelop(x) : vbargraph("v2[nomidi:no]", -70, +5));
vmeter3(x)		= attach(x, envelop(x) : vbargraph("v3[nomidi:no]", -70, +5));
vmeter4(x)		= attach(x, envelop(x) : vbargraph("v4[nomidi:no]", -70, +5));
vmeter5(x)		= attach(x, envelop(x) : vbargraph("v5[nomidi:no]", -70, +5));

envelop         = abs : max ~ (1.0/SR) : reduce(max,4096) ; // : max(db2linear(-70)) : linear2db;

/*-----------------------------------------------
		freeverb  by "Grame"
  -----------------------------------------------*/

c1 	= vslider("RoomSize1", 0.5, 0, 1, 0.025)*0.28 + 0.7;
d1 	= vslider("damp1",0.5, 0, 1, 0.025);
wet1 = vslider("wet_dry1[name:wet/dry]",  50, 0, 100, 1) : /(100);
dry1 = 1 - wet1;

c2 	= vslider("RoomSize2", 0.5, 0, 1, 0.025)*0.28 + 0.7;
d2 	= vslider("damp2",0.5, 0, 1, 0.025);
wet2 = vslider("wet_dry2[name:wet/dry]",  50, 0, 100, 1) : /(100);
dry2 = 1 - wet2;

c3 	= vslider("RoomSize3", 0.5, 0, 1, 0.025)*0.28 + 0.7;
d3 	= vslider("damp3",0.5, 0, 1, 0.025);
wet3 = vslider("wet_dry3[name:wet/dry]",  50, 0, 100, 1) : /(100);
dry3 = 1 - wet3;

c4 	= vslider("RoomSize4", 0.5, 0, 1, 0.025)*0.28 + 0.7;
d4 	= vslider("damp4",0.5, 0, 1, 0.025);
wet4 = vslider("wet_dry4[name:wet/dry]",  50, 0, 100, 1) : /(100);
dry4 = 1 - wet4;

c5 	= vslider("RoomSize5", 0.5, 0, 1, 0.025)*0.28 + 0.7;
d5 	= vslider("damp5",0.5, 0, 1, 0.025);
wet5 = vslider("wet_dry5[name:wet/dry]",  50, 0, 100, 1) : /(100);
dry5 = 1 - wet5;

// Filter Parameters

combtuningL1	= 1116;
combtuningL2	= 1188;
combtuningL3	= 1277;
combtuningL4	= 1356;
combtuningL5	= 1422;
combtuningL6	= 1491;
combtuningL7	= 1557;
combtuningL8	= 1617;

allpasstuningL1	= 556;
allpasstuningL2	= 441;
allpasstuningL3	= 341;
allpasstuningL4	= 225;


// Comb and Allpass filters

allpass(dt,fb) = (_,_ <: (*(fb),_:+:@(dt)), -) ~ _ : (!,_);
comb(dt, fb, damp) = (+:@(dt)) ~ (*(1-damp) : (+ ~ *(damp)) : *(fb));

// Reverb components

monoReverb(fb1, fb2, damp, spread)
	= _ <:	comb(combtuningL1+spread, fb1, damp),
			comb(combtuningL2+spread, fb1, damp),
			comb(combtuningL3+spread, fb1, damp),
			comb(combtuningL4+spread, fb1, damp),
			comb(combtuningL5+spread, fb1, damp),
			comb(combtuningL6+spread, fb1, damp),
			comb(combtuningL7+spread, fb1, damp),
			comb(combtuningL8+spread, fb1, damp)
		+>
		 	allpass (allpasstuningL1+spread, fb2)
		:	allpass (allpasstuningL2+spread, fb2)
		:	allpass (allpasstuningL3+spread, fb2)
		:	allpass (allpasstuningL4+spread, fb2)
		;

//----------------------------------------------------------------

fxctrl(g,w,Fx) =  _ <: (*(g) <: _ + Fx ), *(1-w) +> _;
reverb(dry, wet_dry, combfeed, dampslider) = _<:*(dry),(*(wet_dry):fxctrl(0.015,wet_dry, monoReverb(combfeed, 0.5, dampslider, 23))):>_;

process    = geq: ( dist5s , dist4s , dist3s, dist2s, dist1s) :>_ with { 
    dist1s = reverb(dry1,wet1,c1,d1) : vmeter1 ;
    dist2s = reverb(dry2,wet2,c2,d2) : vmeter2;
    dist3s = reverb(dry3,wet3,c3,d3) : vmeter3;
    dist4s = reverb(dry4,wet4,c4,d4) : vmeter4;
    dist5s = reverb(dry5,wet5,c5,d5) : vmeter5;
    
};
