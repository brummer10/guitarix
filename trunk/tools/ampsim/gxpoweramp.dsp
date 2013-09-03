declare name "PowerAmp";
import("../../src/faust/guitarix.lib");

feedbackfilter = (_ <: *(b0), (mem : *(b1)) :> + ~ *(a1)) with {
    k = *(1e3);
    M = *(1e6);
    nF = *(1e-9);
    pF = *(1e-12);
    R3 = 100:k;
    R4m = 22:k;
    R4 = vslider("R4", R4m, 0, R4m, 100);
    R5 = 4.7:k;
    C3 = 100:nF;
    B0 = R5;
    B1 = R4*R5*C3;
    A0 = R3 + R5;
    A1 = C3*R4*R5 + C3*R3*R5 + C3*R3*R4;
    a = A0 + 2*A1*SR;
    a1 = -1 * (A0 - 2*A1*SR) / a;
    b0 = (B0 + 2*B1*SR) / a;
    b1 = (B0 - 2*B1*SR) / a;
};

process = *(pregain) : (- : PowAmp) ~ (feedbackfilter : *(fbgain)) : *(postgain) with {
    PowAmp = ffunction(float PowAmp(float), <math.h>, "");
    pregain =  vslider("Pregain",0,-20,40,0.1) : db2linear : smoothi(0.999); 
    postgain = vslider("postgain", 0, -20.0, 20.0, 0.1) : db2linear : /(450): smoothi(0.999);
    fbgain = vslider("fbgain", 0, -40.0, 20.0, 0.1) : db2linear : /(15): smoothi(0.999);
};
