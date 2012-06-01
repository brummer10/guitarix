declare id 		"flanger_mono_t2"; // need a name...
declare name            "Flanger Mono T2";
declare category        "Modulation";

h_flanger(dmax, curdel, fb, wet) = _ <: _, (dly : (+:dly)~*(fb)) : mix with {
    dly = component("music.lib").fdelay(dmax/2, curdel/2);
    mix = *(2-wet), _*(wet) : + : *(0.5);
};

flanger(dmax, curdel, fb, wet) = _ <: _, (+:dly)~*(fb) : mix with {
    dly = component("music.lib").fdelay(dmax, curdel);
    mix = *(2-wet), _*(wet) : + : *(0.5);
};

process = h_flanger(dmax, curdel,  fb, wet1) :
          flanger(  dmax, curdel, -fb, wet2) with {
    SR = component("math.lib").SR;
    dflange = 0.001 * SR *  hslider("width", 5.0, 0, 10, 0.01);
    odflange = 0.001 * SR *  hslider("depth", 0.5, 0, 5, 0.01);
    dmax = 2048; // > max(dflange+odflange) at rate 96000
    freq = hslider("freq [log][unit:Hz]", 0.2, 0.05, 10, 1.06);
    fb = hslider("feedback", -0.707, -0.99, 0.99, 0.01) * (2+abs(mix))/3;
    lfo = component("oscillator.lib").oscrs;
    curdel = odflange+dflange*(1+lfo(freq))/2;
    //curdel = hslider("delay", 20, 0, 400, 0.1);
    wet = hslider("wet", 1, 0, 1, 0.1);
    mix = hslider("mix", 0, -1, 1, 0.1);
    wet1 = wet*min(1,1+mix);
    wet2 = wet*min(1,1-mix);
};
