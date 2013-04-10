declare name "Tube Delay";
declare category "Echo / Delay";


import("music.lib");
import("guitarix.lib");

level = vslider("level[style:knob]", 0, 0, 10, 0.1)/10;
gain = vslider("gain[style:knob]", 0, -30, 6, 0.1) : db2linear : smoothi(0.999);
feedback = vslider("feedback[style:knob]", 0, 0.0, 10, 0.1)/10;
dtime	= hslider("delay[unit:ms][style:knob]", 0, 0.1, 5000, 0.1)*SR/1000.0;

// Added gain reduction to get unity gain at 0dB ( trial and error for each stage )
// Real tube values 
//	Fk		Rk			Vk
//			1500		1.3
//			2700		1,83
//			820			0.96
stage1 = tubestage(TB_12AX7_68k,2.1,1500.0,1.204541):lowpass( 1, 6531 ) ; // Gain 2.9   2nd -29.8 3rd -26.24
stage2 = tubestage(TB_12AX7_250k,2.1,1500.0,1.204285) :lowpass( 1, 6531 ); //  Gain 2.41 2nd -34.34 3rd -23.36

interp = 100*SR/1000.0;

// for a 5 sec delay, mem size of 262144 will be enough
//N = int( 2^19 ) ;
delayed = sdelay(262144, interp, dtime) ;

// added a delay bypass output to get a real tape delay,
// and a low/highpass filter section in the feedback loop
// to avoid self oscillation

process = stage1:_<:((+:_<:_ ,( delayed:*(level)) :>_)~(*(feedback): highpass(1,120):lowpass(1,12000))):>_:*(gain):stage2;
