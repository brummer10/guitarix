import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 3
 */
 
 process =  hgroup("stage3", BP(stage3)) 
	with {
    stage3 = lowpass1(6531.0) : component("amp2.dsp").tubestage(TB_12AX7_250k,194.0,820.0,0.840703) : *(gain3) with {
        gain3 = vslider("gain3", 6, -10.0, 20.0, 0.1) : ba.db2linear : smoothi(0.999);
    };    
};
