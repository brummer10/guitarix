// generated automatically
// DO NOT MODIFY!
declare id "bmp";
declare name "BigMuffPi";
declare category "Fuzz";
declare shortname "BMP";
declare description "BigMuffPi";
declare samplerate "96000";

import("stdfaust.lib");

bpmin = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
    b0 = 3.7454979802542e-6*fs;

    b1 = 0;

    b2 = -3.7454979802542e-6*fs;

    a0 = 2.08287704934496e-5*fs + 0.000219016314271736;

    a1 = 0.000438032628543473;

    a2 = -2.08287704934496e-5*fs + 0.000219016314271736;
};

bpmamp1 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
        Sustain = vslider("Sustain[name:Sustain]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = Sustain*fs*(2.26293387153501e-12*fs - 1.17905906929765e-5) + fs*(2.26293387153501e-14*fs - 1.17905906929765e-7);

    b1 = -4.52586774307001e-12*Sustain*pow(fs,2) - 4.52586774307001e-14*pow(fs,2);

    b2 = Sustain*fs*(2.26293387153501e-12*fs + 1.17905906929765e-5) + fs*(2.26293387153501e-14*fs + 1.17905906929765e-7);

    a0 = Sustain*(Sustain*fs*(-1.13446519814126e-9*fs - 2.89110812782566e-6) + fs*(1.12312054615984e-9*fs + 2.8621970465474e-6)) + fs*(1.2821120020393e-10*fs + 6.26521815410076e-7) + 0.000146000960455196;

    a1 = Sustain*(2.26893039628251e-9*Sustain*pow(fs,2) - 2.24624109231969e-9*pow(fs,2)) - 2.5642240040786e-10*pow(fs,2) + 0.000292001920910392;

    a2 = Sustain*(Sustain*fs*(-1.13446519814126e-9*fs + 2.89110812782566e-6) + fs*(1.12312054615984e-9*fs - 2.8621970465474e-6)) + fs*(1.2821120020393e-10*fs - 6.26521815410076e-7) + 0.000146000960455196;
};

bpmamp2 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
    b0 = fs*(7.66731214399861e-12*fs - 3.99490857178962e-5);

    b1 = -1.53346242879972e-11*pow(fs,2);

    b2 = fs*(7.66731214399861e-12*fs + 3.99490857178962e-5);

    a0 = fs*(3.920487958595e-10*fs + 2.00478727462711e-6) + 0.000489785157611555;

    a1 = -7.84097591718999e-10*pow(fs,2) + 0.000979570315223111;

    a2 = fs*(3.920487958595e-10*fs - 2.00478727462711e-6) + 0.000489785157611555;
};

bpmtone = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
        Tone = vslider("Tone[name:Tone]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = Tone*(3.68688858465455e-10*pow(fs,2) - 0.00316091270975185) + 8.67101574539126e-7*fs + 0.00401435914138484;

    b1 = Tone*(-7.37377716930911e-10*pow(fs,2) - 0.00632182541950369) + 0.00802871828276969;

    b2 = Tone*(3.68688858465455e-10*pow(fs,2) - 0.00316091270975185) - 8.67101574539126e-7*fs + 0.00401435914138484;

    a0 = fs*(3.68688858465455e-10*fs + 3.03485551088694e-6) + 0.00486780557301784;

    a1 = -7.37377716930911e-10*pow(fs,2) + 0.00973561114603569;

    a2 = fs*(3.68688858465455e-10*fs - 3.03485551088694e-6) + 0.00486780557301784;
};

bpmout = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
        Volume = vslider("Volume[name:Volume]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
    
    b0 = -1.74325899023428e-9*Volume*pow(fs,2);

    b1 = 3.48651798046856e-9*Volume*pow(fs,2);

    b2 = -1.74325899023428e-9*Volume*pow(fs,2);

    a0 = fs*(4.33884681055068e-10*fs + 6.86809013445937e-9) + 2.65226702159437e-8;

    a1 = -8.67769362110135e-10*pow(fs,2) + 5.30453404318874e-8;

    a2 = fs*(4.33884681055068e-10*fs - 6.86809013445937e-9) + 2.65226702159437e-8;
};

antialiasing = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0,b4/a0),(a1/a0,a2/a0,a3/a0,a4/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
    b0 = fs*(4.68362091734077e-13*fs + 7.44521670106066e-7);

    b1 = 1.48904334021213e-6*fs;

    b2 = -9.36724183468154e-13*pow(fs,2);

    b3 = -1.48904334021213e-6*fs;

    b4 = fs*(4.68362091734077e-13*fs - 7.44521670106066e-7);

    a0 = fs*(7.55757331680132e-11*fs + 8.45438325675249e-7) + 0.000114185647251642;

    a1 = 1.6908766513505e-6*fs + 0.00045674258900657;

    a2 = -1.51151466336026e-10*pow(fs,2) + 0.000685113883509854;

    a3 = -1.6908766513505e-6*fs + 0.00045674258900657;

    a4 = fs*(7.55757331680132e-11*fs - 8.45438325675249e-7) + 0.000114185647251642;
};

    symclip = ffunction(float symclip(float), "clipping.h", "");
    sclip = symclip(_);

process = bpmin : bpmamp1 : sclip  : bpmamp2 : sclip  : bpmtone : bpmout;
