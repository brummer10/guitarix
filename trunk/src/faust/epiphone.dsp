// generated automatically
// DO NOT MODIFY!
declare id "epiphone";
declare name "Single ended EL84";
declare shortname "Epiphone";
declare description "Single ended EL84";
declare samplerate "96000";

import("stdfaust.lib");
import("guitarix.lib");

p1 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) : epiphone_jr_outclip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(5.16589926047446e-10*fs + 5.33527722168907e-8);

    b1 = -1.03317985209489e-9*pow(fs,2);

    b2 = fs*(5.16589926047446e-10*fs - 5.33527722168907e-8);

    a0 = fs*(4.33069857761234e-10*fs + 4.59724862995143e-8) + 3.68375740341601e-7;

    a1 = -8.66139715522468e-10*pow(fs,2) + 7.36751480683202e-7;

    a2 = fs*(4.33069857761234e-10*fs - 4.59724862995143e-8) + 3.68375740341601e-7;
};

epiphone_jr_outclip = _<: ba.if(signbit(_), epiphone_jr_out_neg_clip, epiphone_jr_out_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    epiphone_jr_out_clip = ffunction(float epiphone_jr_outclip(float), "epiphone_jr_out_table.h", "");

    epiphone_jr_out_neg_clip = ffunction(float epiphone_jr_out_negclip(float), "epiphone_jr_out_neg_table.h", "");

};

process = *(poweramp_ctrl.ingain) : p1 : *(2.0) : *(poweramp_ctrl.outgain);
