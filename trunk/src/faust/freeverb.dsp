//declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

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

roomsizeSlider 	= vslider("RoomSize", 0.5, 0, 1, 0.025)*0.28 + 0.7;
dampslider 	= vslider("damp",0.5, 0, 1, 0.025);
combfeed 	= roomsizeSlider;
wetslider 	= 0.5 + vslider("wet_dry[name:wet/dry]", 0, -0.5, 0.5, 0.1);

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

fxctrl(g,w,Fx) =  _ <: (*(g) <: _ + Fx : *(w)), *(2*(1-w)) +> _;
process = fxctrl(0.015, wetslider, monoReverb(combfeed, 0.5, dampslider, 23));
