declare name "Tube Delay";
declare category "Echo / Delay";


import("music.lib");
import("guitarix.lib");
import("redeye.lib");

LogPot(a, x) = if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
level = vslider("level[style:knob]", 0, 0, 1, 0.1):LogPot(1):smoothi(0.993);
feedback = vslider("feedback[style:knob]", 0, 0.0, 1, 0.01);
dtime	= vslider("delay[unit:ms][style:knob]", 0, 0.1, 2500, 0.1)*SR/1000.0;

interp = 100*SR/1000.0;

// for a 2.5 sec delay
N = int( 2^17 ) ;
delayed = sdelay(N, interp, dtime) ;

// added a delay bypass output to get a real tape delay,
// and a low/highpass filter section in the feedback loop
// to avoid self oscillation

process = input12au7:*(0.1):_<:((+:_<:_ ,( delayed:*(level)) :>_)~(*(feedback): highpass(1,120):lowpass(1,12000))):>_:output12au7;


