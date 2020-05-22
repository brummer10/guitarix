declare name "Tube Delay";
declare category "Echo / Delay";

import("stdfaust.lib");
import("redeye.lib");

LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
level = vslider("level[style:knob]", 0, 0, 1, 0.1):LogPot(1):si.smooth(0.993);
feedback = vslider("feedback[style:knob]", 0, 0.0, 0.7, 0.01);
dtime	= vslider("de.delay[unit:ms][style:knob]", 0.1, 0.1, 2500, 0.1)*ma.SR/1000.0;
output = vslider("output[style:knob]", 0.0, -20.0, 20.0, 0.1):ba.db2linear:si.smooth(0.993);
interp = 100*ma.SR/1000.0;

// for a 2.5 sec de.delay
N = int( 2^17 ) ;
delayed = de.sdelay(N, interp, dtime) ;

// added a de.delay bypass output to get a real tape de.delay,
// and a low/fi.highpass filter section in the feedback loop
// to avoid self oscillation

amp =  input12ax7<:((+:_<:_ ,( delayed:*(level)) :>_)~(*(feedback): fi.highpass(2,120.0):fi.lowpass(2,12000.0))):>output12ax7:*(output);
freq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));
process    = freq_split: ( amp , amp , amp, amp, amp) :>_;

