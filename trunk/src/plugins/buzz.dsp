// generated automatically
// DO NOT MODIFY!
declare id "buzz";
declare name "Buzz Box";
declare category "Fuzz";
declare shortname "Buzz Box";
declare description "Buzz Box";

import("filter.lib");
import("trany.lib");

process = pre : _<:*(dry),(*(wet) : iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0)) : clip):>_ with {
    LogPot(a, x) = if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = if(b, 1 - x, x);
    s = 0.993;
    fs = float(SR);
    pre = _;
    wet = vslider("wet_dry[name:Wet/Dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
    dry = 1 - wet;
    clip = tranystageb(TB_7199P_68k,86.0,2700.0,5.571981) : tranystageb(TB_7199P_68k,86.0,2700.0,5.571981) ;

    
        Level = vslider("Level[name:Level]", 0.5, 0, 1, 0.01) : Inverted(0) : smooth(s);
    
    b0 = 3.81347663375185e-13*Level*pow(fs,3);

    b1 = -1.14404299012556e-12*Level*pow(fs,3);

    b2 = 1.14404299012556e-12*Level*pow(fs,3);

    b3 = -3.81347663375185e-13*Level*pow(fs,3);

    a0 = fs*(fs*(9.04201686922855e-15*fs + 1.0967885210812e-14) + 8.14058347559848e-15) + 2.46256378077601e-15;

    a1 = fs*(fs*(-2.71260506076857e-14*fs - 1.0967885210812e-14) + 8.14058347559848e-15) + 7.38769134232804e-15;

    a2 = fs*(fs*(2.71260506076857e-14*fs - 1.0967885210812e-14) - 8.14058347559848e-15) + 7.38769134232804e-15;

    a3 = fs*(fs*(-9.04201686922855e-15*fs + 1.0967885210812e-14) - 8.14058347559848e-15) + 2.46256378077601e-15;
};
