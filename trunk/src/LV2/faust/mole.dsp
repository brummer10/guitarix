// generated automatically
// DO NOT MODIFY!
declare id "mole";
declare name "The Mole";
declare category "Tone Control";
declare shortname "The Mole";
declare description "EHX Mole";

import("stdfaust.lib");

process = pre : _<:*(dry),(*(wet) : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0))):>_ with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;
    wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
    dry = 1 - wet;

    
        Boost = vslider("Boost[name:Boost]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = -9.74268345040146e-11*Boost*pow(fs,2);

    b1 = 9.74268345040146e-11*Boost*pow(fs,2);

    b2 = 9.74268345040146e-11*Boost*pow(fs,2);

    b3 = -9.74268345040146e-11*Boost*pow(fs,2);

    a0 = fs*(fs*(8.93878454194095e-15*fs + 4.96556855945694e-12) + 2.64572840995574e-11) + 2.70404912477885e-11;

    a1 = fs*(fs*(-2.68163536258229e-14*fs - 4.96556855945694e-12) + 2.64572840995574e-11) + 8.11214737433656e-11;

    a2 = fs*(fs*(2.68163536258229e-14*fs - 4.96556855945694e-12) - 2.64572840995574e-11) + 8.11214737433656e-11;

    a3 = fs*(fs*(-8.93878454194095e-15*fs + 4.96556855945694e-12) - 2.64572840995574e-11) + 2.70404912477885e-11;
};
