declare id         "mxrdis";
declare name       "MXR Distortion Plus";
declare shortname  "MXR+";
declare category   "Distortion";
declare samplerate "96000";

import("stdfaust.lib");

s = 0.993;
fs = float(ma.SR);
drive =  0.75 + hslider("drive[name:Drive]", 0.5, 0, 1, 0.01) * 0.25 : si.smooth(s);

mxr_in = fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    
    b0 = fs*(4.29274359816386e-10*fs + 6.43911539724579e-10);

    b1 = -8.58548719632772e-10*pow(fs,2);

    b2 = fs*(4.29274359816386e-10*fs - 6.43911539724579e-10);

    a0 = fs*(4.3356710341455e-10*fs + 2.2111922274142e-8) + 2.14637179908193e-8;

    a1 = -8.671342068291e-10*pow(fs,2) + 4.29274359816386e-8;

    a2 = fs*(4.3356710341455e-10*fs - 2.2111922274142e-8) + 2.14637179908193e-8;
};

mxr_out = fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {

       Volume = vslider("Volume[name:Volume]", 0.5, 0, 1, 0.01) : si.smooth(s);
    
    b0 = 7.03343695930453e-6*Volume*fs;

    b1 = 0;

    b2 = -7.03343695930453e-6*Volume*fs;

    a0 = fs*(1.40668739186091e-10*fs + 1.40739073555684e-5) + 0.000351671847965227;

    a1 = -2.81337478372181e-10*pow(fs,2) + 0.000703343695930453;

    a2 = fs*(1.40668739186091e-10*fs - 1.40739073555684e-5) + 0.000351671847965227;
};

process = mxr_in : X3  : mxr_out   with {
    R1 = 4700 + (1000000 * (1.0 -drive));
    R2 = 1000000 ;
    C = 0.047 * 1e-6;
    a1 = (R1 + R2) * C * 2 * ma.SR;
    a2 = R1 * C * 2 * ma.SR;
    B0 = (1 + a1) / (1 + a2);
    B1 = (1 - a1) / (1 + a2);
    A1 = (1 - a2) / (1 + a2);
    X2 = fi.tf1(B0, B1, A1);
    opamp1 = ffunction(float opamp2(float), "clipping.h", "");
    X3 = _ <: _ - opamp1(X2-_) :> _ ;
    asymclip = ffunction(float asymhardclip2(float), "clipping.h", "");
    clip = asymclip(_);
};
