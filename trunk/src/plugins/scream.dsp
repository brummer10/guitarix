// generated automatically
// DO NOT MODIFY!
declare id "scream";
declare name "Screaming Bird";
declare category "Fuzz";
declare shortname "Scream Bird";
declare description "Screaming Bird";
declare samplerate "96000";

import("stdfaust.lib");

process = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) : clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;
    //clip(x) = min(0.4514,max(-0.2514,x));
    asymclip = ffunction(float asymclip(float), "clipping.h", "");
    clip = asymclip(_);

    
        Scream = vslider("Scream[name:Scream]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = -6.82076449438528e-9*Scream*pow(fs,2) - 6.82076449438528e-10*pow(fs,2);

    b1 = 1.36415289887706e-8*Scream*pow(fs,2) + 1.36415289887706e-9*pow(fs,2);

    b2 = -6.82076449438528e-9*Scream*pow(fs,2) - 6.82076449438528e-10*pow(fs,2);

    a0 = fs*(3.64434266110822e-10*fs + 3.23311541086178e-6) + 0.00515391115930048;

    a1 = -7.28868532221644e-10*pow(fs,2) + 0.010307822318601;

    a2 = fs*(3.64434266110822e-10*fs - 3.23311541086178e-6) + 0.00515391115930048;
};
