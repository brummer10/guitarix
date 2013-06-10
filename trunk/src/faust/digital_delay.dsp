declare id "dide";
declare name "Digital Delay";
declare category "Echo / Delay";
declare description "Digital Delay";


import("music.lib");
import("guitarix.lib");
import("math.lib");


tempo2note = ffunction(float B2N(int,float), "beat.h", "");

dide         = _<:*(dry),(*(wet) : digd):>_ with {
  digd       = (+:_<:_ ,( delayed:*(level)) :>_)~(*(feedback): highpass(2,hifr1):lowpass(2,lofr1)) with {
    delayed  = sdelay(N, interp, min(2^19,(tempo2note(tact,dbpm)))) with {
      dtime  = hslider("delay[tooltip:Delay Time in ms]", 2500, 0.1, 5000, 0.1)*SR/1000.0;
      dbpm   = tempo(hslider("bpm[name:delay (bpm)][tooltip:Delay in Beats per Minute]",120,24,360,1));
      tact   = hslider("notes[name:tact][enum:Dotted 1/2 note|1/2 note|1/2 note triplets|
Dotted 1/4 note|1/4 note|1/4 note triplets|Dotted 1/8 note|1/8 note|1/8 note triplets|
Dotted 1/16 note|1/16 note|1/16 note triplets|Dotted 1/32 note|1/32 note|1/32 note triplets|
Dotted 1/64 note|1/64 note|1/64 note triplets][tooltip:note setting for bpm]",5,1,18,1);

      interp = 100*SR/1000.0;
      N      = int( 2^19 ) ;
    };
    level    = vslider("level[tooltip:percentage of the delay gain level]", 50, 0, 100, 1)/100 ;
    feedback = vslider("feedback[tooltip:percentage of the feedback level in the delay loop]", 50, 0, 100, 1)/100 ;
    hifr1    = hslider("highpass [name:highpass (hz)][tooltip: highpass filter frequency in the feddback loop]" ,120 , 20, 20000, 1);
    lofr1    = hslider("howpass [name:lowpass (hz)][tooltip: lowpass filter frequency in the feddback loop]" ,12000 , 20, 20000, 1);
  };
  wet        = vslider("gain[tooltip:overall gain of the delay line in percent]",  100, 0, 120, 1) : /(100);
  dry        = 1 - wet;
};

process      = dide;
