/*
Attempt at a true vibrato
And it works well!
Sounds very sweet with tubes wrapped

Need
LFO to modulate de.delay	- LFO 5 - 14Hz
	speed and depth
*/
import("stdfaust.lib");
import("guitarix.lib");
import("redeye.lib");

/* os.triangle oscillator (not bandlimited, frequency is approximate) */

trianglewave(freq) = _ ~ (_ <: _ + hyst) : /(periodsamps) with {
    if(c,t,e) = select2(c,e,t);
    hyst(x) = if(_ > 0, 2 * (x < periodsamps) - 1, 1 - 2 * (x > 0)) ~ _;
    periodsamps = int(ma.SR / (2*float(freq)));
};

/* vibrato unit, using os.triangle or sine oscillator as lfo 
	to modulate the de.delay time 
*/

vibrato = ((( lfo + 1 ) *5)+5)*depth with {
    sine(freq) = (os.oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
    SINE=checkbox("SINEWAVE[enum:os.triangle|sine]");
    lfo = select2(SINE, trianglewave(freq), sine(freq));
	freq = vslider("speed[style:knob]",5,0,14,0.1) ;
	depth = vslider("depth[style:knob]",0.5,0,1,0.01) ;
};

delayed  = de.sdelay(65536, interp, vibrato*ma.SR/1000.0) with{
	N 		= int(2^12); //65536
	interp = 100.0 *ma.SR/1000.0;
//	interp 	= hslider("interpolation[unit:ms][style:knob]",10,1,100,0.1)*ma.SR/1000.0; 
	dtime	= hslider("de.delay[unit:ms][style:knob]", 0, 0, 14, 0.1)*ma.SR/1000.0;
};

//stage1 = tubestage(TB_12AX7_68k,120,1500.0,1.204541) ; // Gain 2.9   2nd -29.8 3rd -26.24
//stage2 = fi.lowpass( 1, 6531 ):tubestage(TB_12AX7_250k,80,1500.0,1.204285) ; //  Gain 2.41 2nd -34.34 3rd -23.36
//drive = vslider("gain[style:knob]", 0, -64, 6, 0.1) :ba.db2linear: smoothi(0.999);
//process = stage1:delayed:*(drive):stage2;
process = input12au7:*(0.1):delayed:output12au7;
