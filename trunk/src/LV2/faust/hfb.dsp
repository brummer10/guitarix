// generated automatically
// DO NOT MODIFY!
declare id "hfb";
declare name "HF Brightener";
declare category "Tone Control";
declare shortname "HF Brightener";
declare description "High Frequency Brightener";

import("stdfaust.lib");

process = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
        Volume = vslider("Volume[name:Volume]", 0.5, 0, 1, 0.01) : Inverted(1) : si.smooth(s);
    
        Intensity = vslider("Intensity[name:Intensity]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = Intensity*(5.12666523663255e-23*Intensity*pow(fs,2) - 1.59041010538546e-9*pow(fs,2)) - 3.18082021077091e-10*Volume*pow(fs,2) - 1.06027340359031e-6*fs;

    b1 = Intensity*(-1.02533304732651e-22*Intensity*pow(fs,2) + 3.18082021077092e-9*pow(fs,2)) + 6.36164042154183e-10*Volume*pow(fs,2);

    b2 = Intensity*(5.12666523663255e-23*Intensity*pow(fs,2) - 1.59041010538546e-9*pow(fs,2)) - 3.18082021077091e-10*Volume*pow(fs,2) + 1.06027340359031e-6*fs;

    a0 = Intensity*(Intensity*fs*(-1.17023754306854e-9*fs - 6.50608604711861e-8) + fs*(1.18275520407517e-9*fs + 6.61287722583147e-8)) + Volume*fs*(2.36551040815034e-10*fs + 1.32257544516629e-8) + 7.88503469383447e-7*fs + 4.40858481722098e-5;

    a1 = Intensity*(2.34047508613708e-9*Intensity*pow(fs,2) - 2.36551040815034e-9*pow(fs,2)) - 4.73102081630068e-10*Volume*pow(fs,2) + 8.81716963444196e-5;

    a2 = Intensity*(Intensity*fs*(-1.17023754306854e-9*fs + 6.50608604711861e-8) + fs*(1.18275520407517e-9*fs - 6.61287722583147e-8)) + Volume*fs*(2.36551040815034e-10*fs - 1.32257544516629e-8) - 7.88503469383447e-7*fs + 4.40858481722098e-5;
};
