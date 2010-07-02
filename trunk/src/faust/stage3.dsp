import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");


/****************************************************************
 ** Tube Preamp Emulation stage 3
 */
 
 process =  hgroup("stage3", BP(stage3)) 
	with {
    stage3 = lowpass1(6531.0) : component("amp2.dsp").tubestage(1,194.0,820.0) : *(gain3) with {
        gain3 = vslider("gain3", 6, -10.0, 20.0, 0.1) : db2linear : smoothi(0.999);
    };    
};
