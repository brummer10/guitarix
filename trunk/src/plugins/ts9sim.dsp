declare id 		"ts9sim";
declare name            "Tube Screamer";
declare category        "Distortion";

/*
** based on a circuit diagram of the Ibanez TS-9 and
** a mathematical analysis published by Tamás Kenéz
*/

smoothi(c) = *(1-c) : +~*(c);

process = ts9 : lowpass : *(gain) with {
    SR = component("math.lib").SR;
    R1 = 4700;
    R2 = 51000 + 500000 * hslider("drive[name:Drive]", 0.5, 0, 1, 0.01);
    C = 0.047 * 1e-6;
    a1 = (R1 + R2) * C * 2 * SR;
    a2 = R1 * C * 2 * SR;
    B0 = (1 + a1) / (1 + a2);
    B1 = (1 - a1) / (1 + a2);
    A1 = (1 - a2) / (1 + a2);
    X2 = component("filter.lib").tf1(B0, B1, A1);
    ts9nonlin = ffunction(float ts9nonlin(float), "ts9nonlin.h", "");
    ts9 = _ <: _ - ts9nonlin(X2-_) :> _;
    fc = hslider("tone[log][name:Tone]", 400, 100, 1000, 1.03);
    lowpass = component("filter.lib").lowpass1(fc);
    gain = hslider("level[name:Level]", -16, -20, 4, 0.1) : component("music.lib").db2linear : smoothi(0.999);
};
