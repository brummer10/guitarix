// generated automatically
// DO NOT MODIFY!
declare id "bfuzz";
declare name "Bass Fuzz Pedal";
declare category "Fuzz";
declare shortname "Bass Fuzz";
declare description "Bass Fuzz Pedal";

import("stdfaust.lib");
import("trany.lib");

process = pre : _<:*(dry),(*(wet) : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0,b4/a0),(a1/a0,a2/a0,a3/a0,a4/a0)) : clip):>_ with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;
    wet = vslider("wet_dry[name:Wet/Dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
    dry = 1 - wet;
    clip = tranystageb(TB_7199P_68k,86.0,2700.0,5.571981) : tranystageb(TB_7199P_68k,86.0,2700.0,5.571981) ;

    
        Level = vslider("Level[name:Level]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
        Drive = vslider("Drive[name:Drive]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
        Thickness = vslider("Thickness[name:Thickness]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = Drive*Level*pow(fs,2)*(-1.65780932898435e-16*fs - 8.29281439339673e-13) + Level*pow(fs,2)*(-7.76911913609341e-14*fs - 3.88632527694127e-10) + Thickness*(1.65780932898435e-16*Drive*Level*pow(fs,3) + 7.76911913609341e-14*Level*pow(fs,3));

    b1 = 3.3156186579687e-16*Drive*Level*pow(fs,3) + 1.55382382721868e-13*Level*pow(fs,3) + Thickness*(-3.3156186579687e-16*Drive*Level*pow(fs,3) - 1.55382382721868e-13*Level*pow(fs,3));

    b2 = 1.65856287867935e-12*Drive*Level*pow(fs,2) + 7.77265055388254e-10*Level*pow(fs,2);

    b3 = -3.3156186579687e-16*Drive*Level*pow(fs,3) - 1.55382382721868e-13*Level*pow(fs,3) + Thickness*(3.3156186579687e-16*Drive*Level*pow(fs,3) + 1.55382382721868e-13*Level*pow(fs,3));

    b4 = Drive*Level*pow(fs,2)*(1.65780932898435e-16*fs - 8.29281439339673e-13) + Level*pow(fs,2)*(7.76911913609341e-14*fs - 3.88632527694127e-10) + Thickness*(-1.65780932898435e-16*Drive*Level*pow(fs,3) - 7.76911913609341e-14*Level*pow(fs,3));

    a0 = Drive*(fs*(fs*(fs*(-1.8235902618655e-20*fs - 8.82979918090661e-15) - 5.32286268006641e-11) - 2.42569918771087e-9) - 9.41937118747331e-10) + Thickness*(Drive*fs*(fs*(fs*(1.8235902618655e-20*fs + 8.73857822258011e-15) + 9.51587528271067e-12) + 4.14452332248826e-10) + fs*(fs*(fs*(-1.90624114055858e-19*fs - 9.05150991318089e-15) - 9.57238853136628e-11) - 4.70914107604798e-9)) + fs*(fs*(fs*(1.90624114055858e-19*fs + 1.0005063720083e-14) + 1.41002006493022e-10) + 6.98583678876617e-9) + 1.07025933546545e-8;

    a1 = Drive*(fs*(pow(fs,2)*(7.294361047462e-20*fs + 1.76595983618132e-14) - 4.85139837542174e-9) - 3.76774847498933e-9) + Thickness*(Drive*fs*(pow(fs,2)*(-7.294361047462e-20*fs - 1.74771564451602e-14) + 8.28904664497652e-10) + fs*(pow(fs,2)*(7.6249645622343e-19*fs + 1.81030198263618e-14) - 9.41828215209595e-9)) + fs*(pow(fs,2)*(-7.6249645622343e-19*fs - 2.00101274401661e-14) + 1.39716735775323e-8) + 4.2810373418618e-8;

    a2 = Drive*(pow(fs,2)*(-1.0941541571193e-19*pow(fs,2) + 1.06457253601328e-10) - 5.65162271248399e-9) + Thickness*(Drive*pow(fs,2)*(1.0941541571193e-19*pow(fs,2) - 1.90317505654213e-11) + pow(fs,2)*(-1.14374468433515e-18*pow(fs,2) + 1.91447770627326e-10)) + pow(fs,2)*(1.14374468433515e-18*pow(fs,2) - 2.82004012986045e-10) + 6.4215560127927e-8;

    a3 = Drive*(fs*(pow(fs,2)*(7.294361047462e-20*fs - 1.76595983618132e-14) + 4.85139837542174e-9) - 3.76774847498933e-9) + Thickness*(Drive*fs*(pow(fs,2)*(-7.294361047462e-20*fs + 1.74771564451602e-14) - 8.28904664497652e-10) + fs*(pow(fs,2)*(7.6249645622343e-19*fs - 1.81030198263618e-14) + 9.41828215209595e-9)) + fs*(pow(fs,2)*(-7.6249645622343e-19*fs + 2.00101274401661e-14) - 1.39716735775323e-8) + 4.2810373418618e-8;

    a4 = Drive*(fs*(fs*(fs*(-1.8235902618655e-20*fs + 8.82979918090661e-15) - 5.32286268006641e-11) + 2.42569918771087e-9) - 9.41937118747331e-10) + Thickness*(Drive*fs*(fs*(fs*(1.8235902618655e-20*fs - 8.73857822258011e-15) + 9.51587528271067e-12) - 4.14452332248826e-10) + fs*(fs*(fs*(-1.90624114055858e-19*fs + 9.05150991318089e-15) - 9.57238853136628e-11) + 4.70914107604798e-9)) + fs*(fs*(fs*(1.90624114055858e-19*fs - 1.0005063720083e-14) + 1.41002006493022e-10) - 6.98583678876617e-9) + 1.07025933546545e-8;
};
