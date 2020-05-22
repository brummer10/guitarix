declare id "Redeye Chump"; 
declare name "Redeye Chump";
declare category "Amplifier";

import("stdfaust.lib"); 
import("guitarix.lib");
import("redeye.lib");


// Power Amp With Feedback

powerfb = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0)) : redeyechumppowfclip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(fs*(5.2572119847844e-14*fs + 2.22632342602781e-12) + 5.41994006909799e-15);

    b1 = fs*(fs*(-1.57716359543532e-13*fs - 2.22632342602781e-12) + 5.41994006909799e-15);

    b2 = fs*(fs*(1.57716359543532e-13*fs - 2.22632342602781e-12) - 5.41994006909799e-15);

    b3 = fs*(fs*(-5.2572119847844e-14*fs + 2.22632342602781e-12) - 5.41994006909799e-15);

    a0 = fs*(fs*(9.01314076551628e-15*fs + 1.3955910672935e-12) + 6.86346038146649e-11) + 1.79996158094636e-10;

    a1 = fs*(fs*(-2.70394222965488e-14*fs - 1.3955910672935e-12) + 6.86346038146649e-11) + 5.39988474283909e-10;

    a2 = fs*(fs*(2.70394222965488e-14*fs - 1.3955910672935e-12) - 6.86346038146649e-11) + 5.39988474283909e-10;

    a3 = fs*(fs*(-9.01314076551628e-15*fs + 1.3955910672935e-12) - 6.86346038146649e-11) + 1.79996158094636e-10;
};

redeyechumppowfclip = _<: ba.if(signbit(_), redeyechumppowf_neg_clip, redeyechumppowf_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    redeyechumppowf_clip = ffunction(float redeyechumppowfclip(float), "redeyechumppowf_table.h", "");

    redeyechumppowf_neg_clip = ffunction(float redeyechumppowf_negclip(float), "redeyechumppowf_neg_table.h", "");

};
// Power Amp No feedback
powernfb = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0)) : redeyechumppowclip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = pow(fs,2)*(8.08665507806617e-14*fs + 3.42440032262935e-12);

    b1 = pow(fs,2)*(-2.42599652341985e-13*fs - 3.42440032262935e-12);

    b2 = pow(fs,2)*(2.42599652341985e-13*fs - 3.42440032262935e-12);

    b3 = pow(fs,2)*(-8.08665507806617e-14*fs + 3.42440032262935e-12);

    a0 = fs*(fs*(9.00050108040552e-15*fs + 2.00144504609273e-12) + 1.09475884941298e-10) + 2.87117546539927e-10;

    a1 = fs*(fs*(-2.70015032412166e-14*fs - 2.00144504609273e-12) + 1.09475884941298e-10) + 8.6135263961978e-10;

    a2 = fs*(fs*(2.70015032412166e-14*fs - 2.00144504609273e-12) - 1.09475884941298e-10) + 8.6135263961978e-10;

    a3 = fs*(fs*(-9.00050108040552e-15*fs + 2.00144504609273e-12) - 1.09475884941298e-10) + 2.87117546539927e-10;
};

redeyechumppowclip = _<: ba.if(signbit(_), redeyechumppow_neg_clip, redeyechumppow_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    redeyechumppow_clip = ffunction(float redeyechumppowclip(float), "redeyechumppow_table.h", "");

    redeyechumppow_neg_clip = ffunction(float redeyechumppow_negclip(float), "redeyechumppow_neg_table.h", "");

};


//volume =  vslider("Volume[alias][style:knob]",3.0,0.0,12.0,0.01):ba.db2linear:smoothi(0.999);
volume =  vslider("Volume[alias][style:knob]",2.0,0.0,4.0,0.01):smoothi(0.999);

amp = chumpPreamp:poweramp:*(volume) ;
poweramp = _<:powerfb,powernfb:select2( checkbox("feedback") ) ;

freq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));
process    = freq_split: ( amp , amp , amp, amp, amp) :>_;

