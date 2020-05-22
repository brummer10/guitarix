// generated automatically
// DO NOT MODIFY!
declare id "w20";
declare name "Westbury W-20";
declare category "External";

import("stdfaust.lib");

p1 = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0)) : w20_1clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    Gain = vslider("Gain[name:Gain]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(3) : si.smooth(s);

    b0 = Gain*(Gain*pow(fs,2)*(1.44375296887024e-12*fs + 2.1875044982882e-11) + fs*(fs*(-1.44375296887024e-12*fs - 7.24063988933406e-9) - 1.0937522491441e-7));

    b1 = Gain*(Gain*pow(fs,2)*(-4.33125890661071e-12*fs - 2.1875044982882e-11) + fs*(fs*(4.33125890661071e-12*fs + 7.24063988933406e-9) - 1.0937522491441e-7));

    b2 = Gain*(Gain*pow(fs,2)*(4.33125890661071e-12*fs - 2.1875044982882e-11) + fs*(fs*(-4.33125890661071e-12*fs + 7.24063988933406e-9) + 1.0937522491441e-7));

    b3 = Gain*(Gain*pow(fs,2)*(-1.44375296887024e-12*fs + 2.1875044982882e-11) + fs*(fs*(1.44375296887024e-12*fs - 7.24063988933406e-9) + 1.0937522491441e-7));

    a0 = Gain*(Gain*pow(fs,2)*(-2.37114810573187e-14*fs - 6.90938348698522e-13) + fs*(fs*(2.29013691097909e-14*fs - 1.12102439518276e-11) - 3.45469174349261e-10)) + fs*(fs*(8.10111947527771e-16*fs + 1.34509147324758e-10) + 6.33060724204724e-8) + 1.72734587174631e-6;

    a1 = Gain*(Gain*pow(fs,2)*(7.1134443171956e-14*fs + 6.90938348698522e-13) + fs*(fs*(-6.87041073293727e-14*fs + 1.12102439518276e-11) - 3.45469174349261e-10)) + fs*(fs*(-2.43033584258331e-15*fs - 1.34509147324758e-10) + 6.33060724204724e-8) + 5.18203761523892e-6;

    a2 = Gain*(Gain*pow(fs,2)*(-7.1134443171956e-14*fs + 6.90938348698522e-13) + fs*(fs*(6.87041073293727e-14*fs + 1.12102439518276e-11) + 3.45469174349261e-10)) + fs*(fs*(2.43033584258331e-15*fs - 1.34509147324758e-10) - 6.33060724204724e-8) + 5.18203761523892e-6;

    a3 = Gain*(Gain*pow(fs,2)*(2.37114810573187e-14*fs - 6.90938348698522e-13) + fs*(fs*(-2.29013691097909e-14*fs - 1.12102439518276e-11) + 3.45469174349261e-10)) + fs*(fs*(-8.10111947527771e-16*fs + 1.34509147324758e-10) - 6.33060724204724e-8) + 1.72734587174631e-6;
};

w20_1clip = _<: ba.if(signbit(_), w20_1_neg_clip, w20_1_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    w20_1_clip = ffunction(float w20_1clip(float), "w20_1_table.h", "");

    w20_1_neg_clip = ffunction(float w20_1_negclip(float), "w20_1_neg_table.h", "");

};

p2 =  pre : fi.iir((b0/a0,b1/a0),(a1/a0)) : w20_2aclip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    Level = vslider("Level[name:Level]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(3) : si.smooth(s);

    b0 = -0.000616100994039436*Level*fs;

    b1 = 0.000616100994039436*Level*fs;

    a0 = 2.07411011655813e-5*fs + 0.00442714405209691;

    a1 = -2.07411011655813e-5*fs + 0.00442714405209691;
};

w20_2aclip = _<: ba.if(signbit(_), w20_2a_neg_clip, w20_2a_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    w20_2a_clip = ffunction(float w20_2aclip(float), "w20_2a_table.h", "");

    w20_2a_neg_clip = ffunction(float w20_2a_negclip(float), "w20_2a_neg_table.h", "");

};

amp =  p1:p2 ;
freq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));
process    = freq_split: ( amp , amp , amp, amp, amp) :>_;
