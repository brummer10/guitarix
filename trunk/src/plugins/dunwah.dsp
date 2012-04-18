declare id "dunwah";
declare name "DunWah";

import("effect.lib");

dunwah = *(gs) : tf2(1,-1,0,a1s,a2s)
with {
    // calculated by dunwah1.py
    theta2pi = (1892.75 - 1 / (((0.000927476*wah+-0.00197293)*wah+0.002474)*wah+-0.00152132))/SR;
    Q = ((-12.1248*wah+21.9241)*wah+-33.2116)*wah+25.8564;
    g = 0.025 - 1 / ((((-127.479*wah+387.412)*wah+-466.009)*wah+302.062)*wah+-96.9872);

    R = 1 - theta2pi/(2*Q);
    a1 = 0-2.0*R*cos(theta2pi); // biquad coeff
    a2 = R*R;                   // biquad coeff

    // dezippering of slider-driven signals:
    s = 0.999; // smoothing parameter (one-pole pole location)
    a1s = a1 : smooth(s);
    a2s = a2 : smooth(s);
    gs =  g  : smooth(s);

    tf2 = component("filter.lib").tf2;
    //wah = vslider("wah", 0, 0, 1, 0.01) : *(9) : +(1) : log10;
    wah = vslider("wah", 0, 0, 1, 0.01);
};

dunwah2 = *(gs) : iir((b0, b1, b2, b3), (A1, A2, A3))
with {
    // calculated by dunwah2.py
    theta2pi = (1973.48 - 1000 / ((((((12.499*wah+-40.3658)*wah+49.9836)*wah+-28.3434)*wah+5.76598)*wah+1.9841)*wah+-1.6086)) / SR;
    Q = ((((-52.3051*wah+115.375)*wah+-99.7712)*wah+42.2734)*wah+-24.555)*wah+21.9737;
    g = -0.933975 - 1 / (((((2.85511*wah+-5.20364)*wah+3.64419)*wah+-0.86331)*wah+0.270546)*wah+-0.814203);
    gc = (-8.38823e-12*SR+1.73888e-06)*SR+-0.193457;
    p1 = exp(-1000/(0.808471*SR));
    z1 = 1.00038;
    z2 = (-8.52216e-12*SR+1.77528e-06)*SR+0.879905;
    z3 = (-6.43963e-11*SR+1.54419e-05)*SR+-0.386688;

    b0 = 1.0;
    b1 = -z1-z2-z3;
    b2 = z1*z2+z1*z3+z2*z3;
    b3 = -z1*z2*z3;

    // dezippering of slider-driven signals:
    s = 0.993; // smoothing parameter (one-pole pole location)

    R = 1 - theta2pi/(2*Q);
    a1 = -2.0*R*cos(theta2pi) : smooth(s); // biquad coeff
    a2 = R*R : smooth(s);                  // biquad coeff
    gs =  g * gc : smooth(s);

    A1 = a1 - p1;
    A2 = a2 - a1 * p1;
    A3 = -a2 * p1;

    iir = component("filter.lib").iir;

    //wah = vslider("wah", 0, 0, 1, 0.01) : *(9) : +(1) : log10;
    wah = vslider("wah", 0, 0, 1, 0.01);
};

process = dunwah2;
