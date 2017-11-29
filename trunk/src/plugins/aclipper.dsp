declare id 		"aclipper";
declare name            "Rat";
declare category        "Distortion";
declare samplerate "96000";

import("stdfaust.lib");

s = 0.993;
fs = float(ma.SR);
drive =  hslider("drive[name:Drive]", 0.5, 0, 1, 0.01) : si.smooth(s);

rat_in = fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {

    b0 = 1.82432723786905e-5*fs;

    b1 = 0.000829239653576842;

    b2 = -1.82432723786905e-5*fs;

    a0 = fs*(3.64865447573811e-11*fs + 1.9073341271921e-5) + 0.000414619826788421;

    a1 = -7.29730895147621e-11*pow(fs,2) + 0.000829239653576842;

    a2 = fs*(3.64865447573811e-11*fs - 1.9073341271921e-5) + 0.000414619826788421;
};

rat_out = fi.iir((b0/a0,b1/a0),(a1/a0)) with {

    b0 = 2.08332871602678e-5*fs;

    b1 = -2.08332871602678e-5*fs;

    a0 = 2.08332871602678e-5*fs + 2.21630714470934e-6;

    a1 = -2.08332871602678e-5*fs + 2.21630714470934e-6;
};

rat_tone =  fi.iir((b0/a0,b1/a0),(a1/a0)) with {

    Tone = 1.0 - vslider("tone[name:Tone]", 0.5, 0, 1, 0.01) : si.smooth(s);
    
    b0 = 0.0593824228028504;

    b1 = 0.0593824228028504;

    a0 = -3.91923990498812e-5*Tone*fs + 3.91923990498812e-5*fs + 0.0593824228028504;

    a1 = 3.91923990498812e-5*Tone*fs - 3.91923990498812e-5*fs + 0.0593824228028504;
};

ratdrive = fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {

    Volume = 0.5 + drive * 0.75 ;
    
    b0 = -9.26800656732889e-10*Volume*pow(fs,2);

    b1 = 1.85360131346578e-9*Volume*pow(fs,2);

    b2 = -9.26800656732889e-10*Volume*pow(fs,2);

    a0 = fs*(4.3384046341364e-10*fs + 8.99037897457717e-9) + 3.41041934946762e-8;

    a1 = -8.6768092682728e-10*pow(fs,2) + 6.82083869893523e-8;

    a2 = fs*(4.3384046341364e-10*fs - 8.99037897457717e-9) + 3.41041934946762e-8;
};

process = rat_in : X3 : rat_out : ratdrive : asclip : rat_tone : *(gain)  with {
    R1 = 4700;
    R2 = 1000 + 500000 * drive;
    C = 0.047 * 1e-6;
    a1 = (R1 + R2) * C * 2 * ma.SR;
    a2 = R1 * C * 2 * ma.SR;
    B0 = (1 + a1) / (1 + a2);
    B1 = (1 - a1) / (1 + a2);
    A1 = (1 - a2) / (1 + a2);
    X1 = _<:_,(rat_drive):>_;
    X2 = fi.tf1(B0, B1, A1);
    opamp = ffunction(float opamp(float), "clipping.h", "");
    X3 = _ <: _ - opamp(X2-_) :> _ ;
    asymclip = ffunction(float asymclip3(float), "clipping.h", "");
    asclip = asymclip(_);
    gain = hslider("level[name:Level]", -2, -20, 12, 0.1) : ba.db2linear : si.smooth(s);
};
