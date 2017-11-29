declare name        "WaveSharper";
declare category    "Distortion";
declare id          "distortion2";
declare description "A simple Wavesharper distortion";

import("stdfaust.lib");
import("guitarix.lib");

//----------distortion---------
bread     = fi.highpass(2,f) : fi.lowpass(1,6532) with {
    f     = vslider("Hfreq [log][name:Hi Pass][tooltip: Highpass Frequency]", 30, 20, 2000, 1.08);
};

boost     = vslider("gain[name:Gain][tooltip: Volume Level]", 0, -30, 10, 0.1) : ba.db2linear : smoothi(0.999);

dist(x)   = (1+k)*(x)/(1+k*abs(x)): +~_''* 0.5 with {
    k     = 2*a/(1-a);
    a     = sin(((drive+1)/102)*(ma.PI/2));
    drive = vslider("drive[name:Drive][tooltip: Distortion Level]", 50, 0, 100, 1): smoothi(0.999);
};

butter    = fi.lowpass(2,fc) with {
    fc    = vslider("freq [log][name:Lo Pass][tooltip: Lowpass Frequency]", 10000, 1000, 20000, 1.08);
};

wet = vslider("wet_dry[name:Wet/Dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;

process =_<:*(dry),(*(wet) : bread : *(boost) : dist : butter):>_;
