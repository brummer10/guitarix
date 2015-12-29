// generated automatically
// DO NOT MODIFY!
declare id "lpbboost";
declare name "LPB-1 Booster";
declare category "Tone control";
declare shortname "LPB-1 Boost";
declare description "LPB-1 Linear Power Booster ";

import("filter.lib");

process = pre : iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = if(b, 1 - x, x);
    s = 0.993;
    fs = float(SR);
    pre = _;

    
        Boost = vslider("Boost[name:Boost]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(0) : smooth(s);
    
    b0 = -8.68034563926398e-9*Boost*pow(fs,2) - 8.68034563926398e-11*pow(fs,2);

    b1 = 1.7360691278528e-8*Boost*pow(fs,2) + 1.7360691278528e-10*pow(fs,2);

    b2 = -8.68034563926398e-9*Boost*pow(fs,2) - 8.68034563926398e-11*pow(fs,2);

    a0 = fs*(4.33054407650898e-10*fs + 4.66962506103765e-8) + 1.22474303201741e-6;

    a1 = -8.66108815301797e-10*pow(fs,2) + 2.44948606403482e-6;

    a2 = fs*(4.33054407650898e-10*fs - 4.66962506103765e-8) + 1.22474303201741e-6;
};
