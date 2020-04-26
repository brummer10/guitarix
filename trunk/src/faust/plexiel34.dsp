// generated automatically
// DO NOT MODIFY!
declare id "plexiel34";
declare name "Push Pull EL34";
declare shortname "PlexiEL34";
declare description "PlexiEL34";
declare samplerate "96000";

import("stdfaust.lib");

p1 = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0,b4/a0),(a1/a0,a2/a0,a3/a0,a4/a0)) : plexipowerampel34clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(fs*(fs*(3.87560926163844e-19*fs + 4.30800903120125e-16) + 3.17509705609174e-17) + 5.3495467261267e-19);

    b1 = fs*(pow(fs,2)*(-1.55024370465538e-18*fs - 8.61601806240251e-16) + 1.06990934522534e-18);

    b2 = pow(fs,2)*(2.32536555698307e-18*pow(fs,2) - 6.35019411218347e-17);

    b3 = fs*(pow(fs,2)*(-1.55024370465538e-18*fs + 8.61601806240251e-16) - 1.06990934522534e-18);

    b4 = fs*(fs*(fs*(3.87560926163844e-19*fs - 4.30800903120125e-16) + 3.17509705609174e-17) - 5.3495467261267e-19);

    a0 = fs*(fs*(fs*(1.82693733893894e-19*fs + 2.71243523616587e-16) + 8.16290535602033e-14) + 4.64147298174261e-12) + 4.00158102875003e-12;

    a1 = fs*(pow(fs,2)*(-7.30774935575574e-19*fs - 5.42487047233173e-16) + 9.28294596348523e-12) + 1.60063241150001e-11;

    a2 = pow(fs,2)*(1.09616240336336e-18*pow(fs,2) - 1.63258107120407e-13) + 2.40094861725002e-11;

    a3 = fs*(pow(fs,2)*(-7.30774935575574e-19*fs + 5.42487047233173e-16) - 9.28294596348523e-12) + 1.60063241150001e-11;

    a4 = fs*(fs*(fs*(1.82693733893894e-19*fs - 2.71243523616587e-16) + 8.16290535602033e-14) - 4.64147298174261e-12) + 4.00158102875003e-12;
};

plexipowerampel34clip = _<: ba.if(signbit(_), plexipowerampel34_neg_clip, plexipowerampel34_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    plexipowerampel34_clip = ffunction(float plexipowerampel34clip(float), "plexipowerampel34_table.h", "");

    plexipowerampel34_neg_clip = ffunction(float plexipowerampel34_negclip(float), "plexipowerampel34_neg_table.h", "");

};

process =  p1 ;
