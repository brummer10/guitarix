// Simple Tilt tone control
declare name "Gx Tilt Tone";
declare category "Distortion";
import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");


stage1 = tubestage(TB_12AX7_68k,86.0,2700.0,1.581656);
tone = component("bigmuff.dsp").bigmuff ;
process =  *(drive):stage1:tone:*(preamp):lowpass(1,6531):stage1:/(drive) with{
preamp =  vslider("Gain[alias][style:knob]",0,0,20,0.1) : db2linear : smoothi(0.999);
drive =  vslider("Drive[alias][style:knob]",0,0,20,0.1) : db2linear : smoothi(0.999);
};