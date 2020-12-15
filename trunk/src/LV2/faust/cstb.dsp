// generated automatically
// DO NOT MODIFY!
declare id "cstb";
declare name "Colorsound Tone Blender";
declare category "Distortion";
declare shortname "CS Toneblender";
declare description "Colorsound Tone Blender";

import("stdfaust.lib");
import("trany.lib");

process = pre : _<:*(dry),(*(wet) : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0,b4/a0),(a1/a0,a2/a0,a3/a0,a4/a0)) : clip ):>_ with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;
    wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100) : si.smooth(s);
    dry = 1 - wet;
    clip =  tranystage(TB_7199P_68k,86.0,2700.0,3.571981) : tranystage(TB_7199P_68k,86.0,2700.0,3.571981) ;
    //clip(x) = 0.3 * (min(0.7514,max(-0.4514,x)));
        
        Level =  vslider("Level[name:Level]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
        Attack = vslider("Attack[name:Attack]", 0.5, 0, 0.95, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = Attack*(Attack*(2.34677954600673e-19*Level*pow(fs,4) + 2.34677954600673e-22*pow(fs,4)) - 2.35728909376724e-17*Level*pow(fs,4) - 2.35728909376724e-20*pow(fs,4)) - 2.50775435507154e-15*Level*pow(fs,3) - 2.50775435507154e-18*pow(fs,3);

    b1 = Attack*(Attack*(-9.38711818402692e-19*Level*pow(fs,4) - 9.38711818402692e-22*pow(fs,4)) + 9.42915637506898e-17*Level*pow(fs,4) + 9.42915637506898e-20*pow(fs,4)) + 5.01550871014307e-15*Level*pow(fs,3) + 5.01550871014307e-18*pow(fs,3);

    b2 = Attack*(Attack*(1.40806772760404e-18*Level*pow(fs,4) + 1.40806772760404e-21*pow(fs,4)) - 1.41437345626035e-16*Level*pow(fs,4) - 1.41437345626035e-19*pow(fs,4));

    b3 = Attack*(Attack*(-9.38711818402692e-19*Level*pow(fs,4) - 9.38711818402692e-22*pow(fs,4)) + 9.42915637506898e-17*Level*pow(fs,4) + 9.42915637506898e-20*pow(fs,4)) - 5.01550871014307e-15*Level*pow(fs,3) - 5.01550871014307e-18*pow(fs,3);

    b4 = Attack*(Attack*(2.34677954600673e-19*Level*pow(fs,4) + 2.34677954600673e-22*pow(fs,4)) - 2.35728909376724e-17*Level*pow(fs,4) - 2.35728909376724e-20*pow(fs,4)) + 2.50775435507154e-15*Level*pow(fs,3) + 2.50775435507154e-18*pow(fs,3);

    a0 = Attack*(Attack*fs*(fs*(fs*(-7.13788307669893e-19*fs - 3.81274375281155e-16) - 1.78337596435683e-14) - 3.57720562427687e-14) + fs*(fs*(fs*(7.26395344169953e-19*fs + 3.82634300978431e-16) + 1.78716714442828e-14) + 3.58457860428614e-14)) + fs*(fs*(7.72761004436121e-17*fs + 4.0705776699833e-14) + 1.90124164300881e-12) + 3.81338149392143e-12;

    a1 = Attack*(Attack*fs*(pow(fs,2)*(2.85515323067957e-18*fs + 7.6254875056231e-16) - 7.15441124855374e-14) + fs*(pow(fs,2)*(-2.90558137667981e-18*fs - 7.65268601956861e-16) + 7.16915720857228e-14)) + fs*(-1.54552200887224e-16*pow(fs,2) + 3.80248328601762e-12) + 1.52535259756857e-11;

    a2 = Attack*(Attack*pow(fs,2)*(-4.28272984601936e-18*pow(fs,2) + 3.56675192871367e-14) + pow(fs,2)*(4.35837206501972e-18*pow(fs,2) - 3.57433428885656e-14)) - 8.14115533996661e-14*pow(fs,2) + 2.28802889635286e-11;

    a3 = Attack*(Attack*fs*(pow(fs,2)*(2.85515323067957e-18*fs - 7.6254875056231e-16) + 7.15441124855374e-14) + fs*(pow(fs,2)*(-2.90558137667981e-18*fs + 7.65268601956861e-16) - 7.16915720857228e-14)) + fs*(1.54552200887224e-16*pow(fs,2) - 3.80248328601762e-12) + 1.52535259756857e-11;

    a4 = Attack*(Attack*fs*(fs*(fs*(-7.13788307669893e-19*fs + 3.81274375281155e-16) - 1.78337596435683e-14) + 3.57720562427687e-14) + fs*(fs*(fs*(7.26395344169953e-19*fs - 3.82634300978431e-16) + 1.78716714442828e-14) - 3.58457860428614e-14)) + fs*(fs*(-7.72761004436121e-17*fs + 4.0705776699833e-14) - 1.90124164300881e-12) + 3.81338149392143e-12;
};
