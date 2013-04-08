declare id "Redeye Vibro Chump"; // in amp tube selector
declare name "Redeye Vibro Chumo";
declare category "Amplifier";

import("music.lib");
import("filter.lib");
import("oscillator.lib");
import("effect.lib"); 
import("guitarix.lib");



/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
**
** SHP : Experiment with the presence control as a feedback loop
**	Created a loop with high shelf filter cutting around 1khz and up 
**    pot controls the amount of cut 0 > -70dB 
**    If feedback loop is inverted get mad distortion and feedback!
**   With no inversion get required effect so guess the combination 
**  of filter and processing delay may be shifting phase some
**
** To do :
**	Play with amp structure say a champ clone
** 	tube:eq:tube:tube
**	12AX7:??:12AX7:6V6
**
**	Move feedback loop in more complex amp around driver and power tube
**	12AX7:EQ:(12AX7:6V6)~FEEDBACK 
*/

/*
** Model of a vactrol tremolo unit by "transmogrify"
** c.f. http://sourceforge.net/apps/phpbb/guitarix/viewtopic.php?f=7&t=44&p=233&hilit=transmogrifox#p233
** http://transmogrifox.webs.com/vactrol.m
*/
/* vactrol model */

R1 = 2700;
Ra = 1e6;
Rb = 300;
b = exp(log(Ra)/log(Rb)) - exp(1);
dTC = 0.06;
minTC = log(0.005/dTC);

cds = ((_ <: _,_),_ : _+(1-alpha)*_) ~ (_<:*(alpha)) with {
    iSR = 1/SR;
    dRC = dTC * exp(*(minTC));
    alpha = 1 - iSR / (dRC + iSR);
};

vactrol = pow(_,1.9) : cds : *(b) + exp(1) : exp(log(Ra)/log) : R1/(_ + R1);


/* triangle oscillator (not bandlimited, frequency is approximate) */

trianglewave(freq) = _ ~ (_ <: _ + hyst) : /(periodsamps) with {
    if(c,t,e) = select2(c,e,t);
    hyst(x) = if(_ > 0, 2 * (x < periodsamps) - 1, 1 - 2 * (x > 0)) ~ _;
    periodsamps = int(SR / (2*float(freq)));
};

/* tremolo unit, using triangle or sine oscillator as lfo */

tremolo(freq, depth) = lfo * depth + 1 - depth : vactrol with {
    sine(freq) = (oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
    SINE=checkbox("SINEWAVE[enum:triangle|sine]");
    lfo = select2(SINE, trianglewave(freq), sine(freq));
};

effect =  (tremolo(vslider("speed[style:knob]",5,0.1,10,0.1),vslider("intensity[style:knob]",5,0,10,0.1)/10));


// After some playing it seems that tubestage() phase inverts
// so if presence is wrapped around odd number of tubestages no need to reverse
// if even then we need to reverse

process =  stage1:tone:*(preamp):( + : stage2:transformer )~feedback with {
        preamp =  vslider("Gain[alias][style:knob]",0,-20,20,0.1):db2linear: smoothi(0.999);
	stage1= tubestage(TB_12AX7_68k,86.0,2700.0,1.581656) ; 
	tone = component("bigmuff.dsp").bigmuff ;
	// This range 0.1 -> 10
	volume =  vslider("Volume[alias][style:knob]",0,-20,10,0.1):db2linear:smoothi(0.999);
	// Ideal attenuation is :
	// master -20 -> 0 NONE
	// master 0 - > 20 Either 0.75 or 0.5
	// How to do in Faust!
	atten = 0.5; // Seems to need at least this much!
	stage2 =  lowpass(1,6531.0):tubestage(TB_12AX7_250k,100.0,1500.0,1.204285):*(volume):lowpass(1,6531.0):*(effect):tubestage(TB_6V6_250k,120.0,820.0,1.130462):*(atten); 
       transformer = lowpass( 1, 6531 ):highpass( 1, 120) ;
	feedback = *(checkbox("feedback") ):high_shelf( 3, 6531 ): *(-0.5);
      cabinet = lowpass(2,5500):peak_eq(-15.0,400.0,400):highpass(2,120);

};


