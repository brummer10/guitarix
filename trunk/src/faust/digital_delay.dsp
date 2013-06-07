declare id "dide";
declare name "Digital Delay";
declare category "Echo / Delay";
declare description "Digital Delay";


import("music.lib");
import("guitarix.lib");


dide         = _<:*(dry),(*(wet) : digd):>_ with {
  digd       = (+:_<:_ ,( delayed:*(level)) :>_)~(*(feedback): highpass(2,hifr1):lowpass(2,lofr1)) with {
    delayed  = sdelay(N, interp, dtime) with {
      dtime  = hslider("delay[tooltip:Delay Time in ms]", 2500, 0.1, 5000, 0.1)*SR/1000.0;
      interp = 100*SR/1000.0;
      N      = int( 2^18 ) ;
    };
    level    = vslider("level[tooltip:percentage of the delay gain level]", 50, 0, 100, 1)/100 ;
    feedback = vslider("feedback[tooltip:percentage of the feedback level in the delay loop]", 50, 0, 100, 1)/100 ;
    hifr1    = hslider("show_always_highpass [name:highpass (hz)][tooltip: highpass filter frequency in the feddback loop]" ,120 , 20, 20000, 1);
    lofr1    = hslider("show_always_howpass [name:lowpass (hz)][tooltip: lowpass filter frequency in the feddback loop]" ,12000 , 20, 20000, 1);
  };
  wet        = vslider("gain[tooltip:overall gain of the delay line in percent]",  100, 0, 100, 1) : /(100);
  dry        = 1 - wet;
};

process      = dide;
