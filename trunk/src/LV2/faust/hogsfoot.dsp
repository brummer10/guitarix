// generated automatically
// DO NOT MODIFY!
declare id "hogsfoot";
declare name "Hogs Foot";
declare category "Tone Control";
declare shortname "Hogs Foot";
declare description "Hogs Foot Bass Booster";

import("filter.lib");

process = pre : _<:*(dry),(*(wet) : iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0))):>_ with {
    LogPot(a, x) = if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = if(b, 1 - x, x);
    s = 0.993;
    fs = float(SR);
    pre = _;
    wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
    dry = 1 - wet;

    
        Volume = vslider("Volume[name:Volume]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(0) : smooth(s);
    
    b0 = -9.64632260709932e-11*Volume*pow(fs,2) - 9.64632260709932e-13*pow(fs,2);

    b1 = 9.64632260709932e-11*Volume*pow(fs,2) + 9.64632260709932e-13*pow(fs,2);

    b2 = 9.64632260709932e-11*Volume*pow(fs,2) + 9.64632260709932e-13*pow(fs,2);

    b3 = -9.64632260709932e-11*Volume*pow(fs,2) - 9.64632260709932e-13*pow(fs,2);

    a0 = fs*(fs*(8.93887847679127e-15*fs + 4.96106145708971e-12) + 2.63723081667839e-11) + 2.67730449581491e-11;

    a1 = fs*(fs*(-2.68166354303738e-14*fs - 4.96106145708971e-12) + 2.63723081667839e-11) + 8.03191348744474e-11;

    a2 = fs*(fs*(2.68166354303738e-14*fs - 4.96106145708971e-12) - 2.63723081667839e-11) + 8.03191348744474e-11;

    a3 = fs*(fs*(-8.93887847679127e-15*fs + 4.96106145708971e-12) - 2.63723081667839e-11) + 2.67730449581491e-11;
};
