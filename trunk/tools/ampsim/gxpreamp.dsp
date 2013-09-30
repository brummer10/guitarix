declare name "PreAmp";
import("../../src/faust/guitarix.lib");

Xprocess = PreAmp with { PreAmp = ffunction(float PreAmp1(float), <math.h>, ""); };

process =   *(gain1) : PreAmp1 : highpass(1,31.0) : *(2/92)
          : *(gain2) : PreAmp2 : highpass(1,31.0) : *(2/92)
          : *(gain3) : PreAmp3 : highpass(1,31.0) : *(2/92)
    with {
    PreAmp1 = ffunction(float PreAmp1(float), <math.h>, "");
    PreAmp2 = ffunction(float PreAmp2(float), <math.h>, "");
    PreAmp3 = ffunction(float PreAmp3(float), <math.h>, "");
    gain1 =  vslider("gain1",0,-20,40,0.1) : db2linear : smoothi(0.999); 
    gain2 =  vslider("gain2",0,-20,40,0.1) : db2linear : smoothi(0.999); 
    gain3 =  vslider("gain3",0,-20,40,0.1) : db2linear : smoothi(0.999); 
};

/*
process = *(gain3) : PreAmp3 : highpass(1,31.0) : *(2/92)
          : *(gain1) : mix(gain2, PreAmp1 : highpass(1,31.0), PreAmp2 : highpass(1,31.0)) : *(2/92)
    with {
    mix(w, Fx1, Fx2) = _ <: Fx1, Fx2 : balance(w) : +;
    PreAmp1 = ffunction(float PreAmp1(float), <math.h>, "");
    PreAmp2 = ffunction(float PreAmp2(float), <math.h>, "");
    PreAmp3 = ffunction(float PreAmp3(float), <math.h>, "");
    PreAmp4 = ffunction(float PreAmp4(float), <math.h>, "");
    PreAmp5 = ffunction(float PreAmp5(float), <math.h>, "");
    PreAmp6 = ffunction(float PreAmp6(float), <math.h>, "");
    gain1 =  vslider("gain1",0,-20,40,0.1) : db2linear : smoothi(0.999);
    gain2 =  vslider("gain2",0,-1,1,0.1);
    gain3 =  vslider("gain3",0,-20,40,0.1) : db2linear : smoothi(0.999);
};
*/
