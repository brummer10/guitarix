declare id        "thick_distortion";
declare name      "Thick Distortion";
declare category  "Distortion";
declare author    "Viacheslav Lotsmanov";
declare license   "BSD";
declare copyright "(c) 2018  Viacheslav Lotsmanov";

/*
	This effect was written first in Haskell as standalone JACK application.
	Can be found here: https://github.com/unclechu/haskell-audio-dsp

	There's simple idea behind this distortion effect.
	Main thing is that current sample depends on previous one, "Thickness" value
	is a coefficient of how much previous sample will be dominating on current
	one. Imagine N is a current sample and "Thickness" is set to 0.8 then N will
	be multipled by 0.2 (1-0.8) and N-1 by 0.8 so it is N*0.2 + (N-1)*0.8.

	Just turn input gain knob to extreme value to make signal clipping (it will
	be hard limited to 0dB) and then make it being smooth by big "Thickness"
	level. Even if we have square signal it will be smoothed. This effect could
	also be combined with the "BitDowner" (put "Thick Distortion" after it) to
	get interesting harmonics and reducing higher ones (because signal would be
	less sharp).
*/

import("stdfaust.lib");

gain
	= vslider("input_gain[name:Input][tooltip:Gain (dB)]", 0, 0, 120, 0.1)
	: ba.db2linear
	: si.smoo
	;

thickness
	= vslider("thickness[name:Thickness]", 0.8, 0, 1, 0.01)
	: si.smoo
	;

// coefficient for pure signal (for current sample, not previous one)
pureness = 1 - thickness;

volume
	= vslider("volume[name:Volume][tooltip:Volume (dB)]", 0, -90, 40, 0.1)
	: ba.db2linear
	: si.smoo
	;

hardLimit = min(1) : max(-1);
thick = *(pureness) : + ~(*(thickness));
process = *(gain) : hardLimit : thick : *(volume);
