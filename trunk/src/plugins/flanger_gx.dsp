declare id 		"flanger_mono_gx";
declare name            "Flanger GX";
declare category        "Modulation";

import("stdfaust.lib");

h_flanger(dmax, curdel, fb, wet) = _ <: _, (dly : (+:dly)~*(fb)) : mix with {
    dly = de.fdelay(dmax/2, curdel/2);
    mix = *(2-wet), _*(wet) : +;
};

flanger(dmax, curdel, fb, wet) = _ <: _, (+:dly)~*(fb) : mix with {
    dly = de.fdelay(dmax, curdel);
    mix = *(2-wet), _*(wet) : +;
};

process = h_flanger(dmax, curdel,  fb, wet1) :
          flanger(  dmax, curdel, -fb, wet2) :
          *(0.25) with {
   // ma.SR = component("math.lib").ma.SR;
    dflange = 0.001 * ma.SR *  hslider("width[name:Width]", 5.0, 0, 10, 0.01);
    odflange = 0.001 * ma.SR *  hslider("depth[name:Depth]", 0.5, 0, 5, 0.01);
    dmax = 2048; // > max(dflange+odflange) at rate 96000
    freq = hslider("freq[log][name:Speed][unit:Hz]", 0.2, 0.05, 10, 1.06);
    fb = hslider("feedback[name:Feedback]", -0.707, -0.99, 0.99, 0.01) * (2+abs(mix))/3;
    lfo = os.oscrs;
    curdel = odflange+dflange*(1+lfo(freq))/2;
    //curdel = hslider("de.delay", 20, 0, 400, 0.1);
    wet = hslider("wet[name:Wet]", 100, 0, 100, 1)/100;
    mix = hslider("mix[name:Mix]", 0, -1, 1, 0.1);
    wet1 = wet*min(1,1+mix);
    wet2 = wet*min(1,1-mix);
};
