// generated automatically
// DO NOT MODIFY!
declare id "trbuff";
declare name "Transistor Buffer";
declare category "Guitar Effects";
declare shortname "Transistor Buffer";
declare description "Transistor Buffer";

import("stdfaust.lib");

process = pre : _<:*(dry),(*(wet) : fi.iir((b0/a0,b1/a0),(a1/a0))):>_ with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;
    wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
    dry = 1 - wet;

    
    b0 = 2.06312564351033e-5*fs;

    b1 = -2.06312564351033e-5*fs;

    a0 = 2.08132601776102e-5*fs + 0.000963511474709834;

    a1 = -2.08132601776102e-5*fs + 0.000963511474709834;
};
