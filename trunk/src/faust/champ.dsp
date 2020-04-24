// generated automatically
// DO NOT MODIFY!
declare id "camp";
declare name "Single ended 6V6GT";
declare shortname "Champ";
declare description "Single ended 6V6GT";
declare samplerate "96000";

import("stdfaust.lib");

p1 = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0)) : tweedchampclip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(fs*(1.34550628657417e-13*fs + 6.51622383244889e-12) + 2.15398655450798e-14);

    b1 = fs*(fs*(-4.0365188597225e-13*fs - 6.51622383244889e-12) + 2.15398655450798e-14);

    b2 = fs*(fs*(4.0365188597225e-13*fs - 6.51622383244889e-12) - 2.15398655450798e-14);

    b3 = fs*(fs*(-1.34550628657417e-13*fs + 6.51622383244889e-12) - 2.15398655450798e-14);

    a0 = fs*(fs*(9.02998098452965e-15*fs + 5.88367790860307e-13) + 1.54838623349919e-11) + 3.43362590256886e-10;

    a1 = fs*(fs*(-2.7089942953589e-14*fs - 5.88367790860307e-13) + 1.54838623349919e-11) + 1.03008777077066e-9;

    a2 = fs*(fs*(2.7089942953589e-14*fs - 5.88367790860307e-13) - 1.54838623349919e-11) + 1.03008777077066e-9;

    a3 = fs*(fs*(-9.02998098452965e-15*fs + 5.88367790860307e-13) - 1.54838623349919e-11) + 3.43362590256886e-10;
};

tweedchampclip = _<: ba.if(signbit(_), tweedchamp_neg_clip, tweedchamp_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    tweedchamp_clip = ffunction(float tweedchampclip(float), "tweedchamp_table.h", "");

    tweedchamp_neg_clip = ffunction(float tweedchamp_negclip(float), "tweedchamp_neg_table.h", "");

};

process =  p1 : *(0.2);
