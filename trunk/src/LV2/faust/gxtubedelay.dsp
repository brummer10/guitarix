declare name "Tube Delay";
declare category "Echo / Delay";

import("stdfaust.lib");
import("guitarix.lib");
import("redeye.lib");

LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
level = vslider("level[style:knob]", 0, 0, 1, 0.1):LogPot(1):smoothi(0.993);
feedback = vslider("feedback[style:knob]", 0, 0.0, 1, 0.01);
dtime	= vslider("de.delay[unit:ms][style:knob]", 0.1, 0.1, 2500, 0.1)*ma.SR/1000.0;

interp = 100*ma.SR/1000.0;

// for a 2.5 sec de.delay
N = int( 2^17 ) ;
delayed = de.sdelay(N, interp, dtime) ;

// added a de.delay bypass output to get a real tape de.delay,
// and a low/fi.highpass filter section in the feedback loop
// to avoid self oscillation

process = input12au7:*(0.1):_<:((+:_<:_ ,( delayed:*(level)) :>_)~(*(feedback): fi.highpass(1,120):fi.lowpass(1,12000))):>_:output12au7;
