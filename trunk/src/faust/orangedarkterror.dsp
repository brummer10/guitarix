// generated automatically
// DO NOT MODIFY!
declare id "orangedarkterror";
declare name "Push Pull EL84";
declare shortname "OrangeDarkTerror";
declare description "Push Pull EL84";
declare samplerate "96000";

import("stdfaust.lib");
import("guitarix.lib");

p1 = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0,b4/a0),(a1/a0,a2/a0,a3/a0,a4/a0)) : orangedarkterrorp3clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(fs*(fs*(-6.57377333665727e-19*fs - 4.01607201070155e-17) - 4.37865590304316e-21) + 1.22291757237028e-24);

    b1 = fs*(pow(fs,2)*(2.62950933466291e-18*fs + 8.03214402140309e-17) + 2.44583514474056e-24);

    b2 = pow(fs,2)*(-3.94426400199436e-18*pow(fs,2) + 8.75731180608631e-21);

    b3 = fs*(pow(fs,2)*(2.62950933466291e-18*fs - 8.03214402140309e-17) - 2.44583514474056e-24);

    b4 = fs*(fs*(fs*(-6.57377333665727e-19*fs + 4.01607201070155e-17) - 4.37865590304316e-21) - 1.22291757237028e-24);

    a0 = fs*(fs*(fs*(1.86957288162412e-19*fs + 6.82010407286301e-17) + 4.53454013961264e-15) + 6.51104139918237e-14) + 4.73642640396319e-17;

    a1 = fs*(pow(fs,2)*(-7.47829152649647e-19*fs - 1.3640208145726e-16) + 1.30220827983647e-13) + 1.89457056158527e-16;

    a2 = pow(fs,2)*(1.12174372897447e-18*pow(fs,2) - 9.06908027922528e-15) + 2.84185584237791e-16;

    a3 = fs*(pow(fs,2)*(-7.47829152649647e-19*fs + 1.3640208145726e-16) - 1.30220827983647e-13) + 1.89457056158527e-16;

    a4 = fs*(fs*(fs*(1.86957288162412e-19*fs - 6.82010407286301e-17) + 4.53454013961264e-15) - 6.51104139918237e-14) + 4.73642640396319e-17;
};

orangedarkterrorp3clip = _<: ba.if(signbit(_), orangedarkterrorp3_neg_clip, orangedarkterrorp3_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    orangedarkterrorp3_clip = ffunction(float orangedarkterrorp3clip(float), "orangedarkterrorp3_table.h", "");

    orangedarkterrorp3_neg_clip = ffunction(float orangedarkterrorp3_negclip(float), "orangedarkterrorp3_neg_table.h", "");

};

process =  *(poweramp_ctrl.ingain) : p1 : *(0.6) : *(poweramp_ctrl.outgain);
