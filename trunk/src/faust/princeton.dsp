// generated automatically
// DO NOT MODIFY!
declare id "princeton";
declare name "Single ended 6V6";
declare shortname "Princeton";
declare description "Single ended 6V6";
declare samplerate "96000";

import("stdfaust.lib");
import("guitarix.lib");

p1 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) : princeton_clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(2.46383752600217e-9*fs + 1.18536469845222e-7);

    b1 = -4.92767505200435e-9*pow(fs,2);

    b2 = fs*(2.46383752600217e-9*fs - 1.18536469845222e-7);

    a0 = fs*(4.31429171140134e-10*fs + 1.24411557886099e-7) + 1.54349145985544e-5;

    a1 = -8.62858342280268e-10*pow(fs,2) + 3.08698291971088e-5;

    a2 = fs*(4.31429171140134e-10*fs - 1.24411557886099e-7) + 1.54349145985544e-5;
};

    princeton_clip = ffunction(float princetonclip(float), "princeton_table.h", "");

process =  *(poweramp_ctrl.ingain) : p1 : *(0.2) : *(poweramp_ctrl.outgain);
