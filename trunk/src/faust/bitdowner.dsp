declare id        "bitdowner";
declare name      "BitDowner";
declare category  "Distortion";
declare author    "Viacheslav Lotsmanov (unclechu)";
declare license   "BSD";
declare copyright "(c) Viacheslav Lotsmanov, 2015";

import("stdfaust.lib"); 

gain =
	vslider("input_gain[name:Input][tooltip:Gain (dB)]", 0, -40, 40, 0.1)
	: ba.db2linear
	: si.smooth(0.999)
	;

bitLimit = 16;

downbit =
	vslider("bit_down[name:Bit Down]", bitLimit, 1, bitLimit, 0.1)
	: (2 ^ (_-1))
	;

downsampling =
	vslider(
		"downsampling[name:Smpl Down][tooltip:Downsampling (samples to skip ba.count)]",
		1, 1, 200, 1)
	: int
	;

volume =
	vslider("volume[name:Volume][tooltip:Volume (dB)]", 0, -90, 12, 0.1)
	: ba.db2linear
	: si.smooth(0.999)
	;

// from 0 till x (ba.if x is 5 then [0,1,2,3,4])
counter(x) = int(_)~(_ <: ba.if(_<(x-1) , _+1 , 0));

// downsampling
dsWet(s,c) = _~(ba.if(c == 0 , s , _));
ds(s) =
	// dry signal ba.if downsampling disabled
	ba.if(downsampling > 1 , dsWet(s,counter(downsampling)) , s)
	;

hardLimit(s) = ba.if(s>1, 1, ba.if(s<-1, -1, s));

// bitdowning
bd = *(downbit) : floor : /(downbit) : hardLimit;

process = *(gain) : bd : ds : *(volume);
