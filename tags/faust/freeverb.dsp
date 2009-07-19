declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

/*-----------------------------------------------
		boxes
  -----------------------------------------------*/
switch1		= checkbox("on/off");
monomono 	=  _ <:  _,_;
verb    	= select2(switch1, _, _);


/*-----------------------------------------------
		freeverb  by "Grame"
  -----------------------------------------------*/

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


dampslider 		= vslider("damp",0.5, 0, 1, 0.025)*0.4;
roomsizeSlider 	= vslider("RoomSize", 0.5, 0, 1, 0.025)*0.28 + 0.7;
combfeed 		= roomsizeSlider;
wetslider 		= vslider("wet", 0.3333, 0, 1, 0.025);

// Comb and Allpass filters

allpass(dt,fb) = (_,_ <: (*(fb):+:@(dt)), -) ~ _ : (!,_);
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

fxctrl(g,w,Fx) =  _ <: (*(g),*(g) : Fx : *(w),*(w)), *(1-w), *(1-w) +> _;
//freeverb = fxctrl(0.015, 0.5, monoReverb(combfeed, 0.5, 0.5, 23));
freeverb = fxctrl(0.015, wetslider, monoReverb(combfeed, 0.5, dampslider, 23));


process = vgroup("freeverb", monomono : _, freeverb : verb);


