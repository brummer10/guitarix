import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");


/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */


tubestage(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube(int,float), "valve.h", "");
    vplus = 250.0;
    divider = 40;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

process = hgroup("amp2", hgroup("preamp",(BP(preamp))) :
          hgroup("stage1", BP(stage1)) :
          hgroup("stage2", BP(stage2)) 
          ) with {
    preamp =  *(vslider("Pregain",30,-10,80,0.1):db2linear : smoothi(0.999));     
    stage1 = tubestage(0,86.0,2700.0) : *(gain1) with {
        gain1 = vslider("gain1", 6, -10.0, 20.0, 0.1) : db2linear : smoothi(0.999);
    };
    stage2 = lowpass1(6531.0) : tubestage(1,132.0,1500.0) : *(gain2) with {
        gain2 = vslider("gain2", 6, -10.0, 20.0, 0.1) : db2linear : smoothi(0.999);
    }; 
};
