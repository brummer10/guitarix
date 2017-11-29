import("stdfaust.lib");
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
 */

process = hgroup("amp2", hgroup("preamp",(BP(preamp))) :
          hgroup("stage1", BP(stage1)) :
          hgroup("stage2", BP(stage2)) 
          ) with {
    preamp =  *(vslider("Pregain",30,-10,80,0.1):ba.db2linear : smoothi(0.999));     
    stage1 = tubestage(TB_12AX7_68k,86.0,2700.0,1.581656) : *(gain1) with {
        gain1 = vslider("gain1", 6, -10.0, 20.0, 0.1) : ba.db2linear : smoothi(0.999);
    };
    stage2 = lowpass1(6531.0) : tubestage(TB_12AX7_250k,132.0,1500.0,1.204285) : *(gain2) with {
        gain2 = vslider("gain2", 6, -10.0, 20.0, 0.1) : ba.db2linear : smoothi(0.999);
    }; 
};
