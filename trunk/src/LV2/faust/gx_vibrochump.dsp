declare id "Redeye Vibro Chump"; // in amp tube ba.selector
declare name "Redeye Vibro Chumo";
declare category "Amplifier";

import("stdfaust.lib");
import("guitarix.lib");
import("redeye.lib");

/****************************************************************
 ** Tube Preamp Emulation stage 1 - 2 
**
** SHP : Experiment with the presence control as a feedback loop
**	Created a loop with high shelf filter cutting around 1khz and up 
**    pot controls the amount of cut 0 > -70dB 
**    If feedback loop is inverted get mad distortion and feedback!
**   With no inversion get required effect so guess the combination 
**  of filter and processing de.delay may be shifting phase some
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
    iSR = 1/ma.SR;
    dRC = dTC * exp(*(minTC));
    alpha = 1 - iSR / (dRC + iSR);
};

vactrol = pow(_,1.9) : cds : *(b) + exp(1) : exp(log(Ra)/log) : R1/(_ + R1);

/* os.triangle oscillator (not bandlimited, frequency is approximate) */

trianglewave(freq) = _ ~ (_ <: _ + hyst) : /(periodsamps) with {
    if(c,t,e) = select2(c,e,t);
    hyst(x) = if(_ > 0, 2 * (x < periodsamps) - 1, 1 - 2 * (x > 0)) ~ _;
    periodsamps = int(ma.SR / (2*float(freq)));
};

process = chumpPreamp:*(0.1):poweramp:transformer:*(0.5):*(volume) with{

	volume =  hgroup( "Amp",vslider("Volume[alias][style:knob]",0.5,0,1,0.01):smoothi(0.999) );
	poweramp = *(vibe):tubestage(TB_6V6_250k,120.0,820.0,1.130462) ;
	transformer = fi.lowpass( 1, 5500 ):fi.highpass( 1, 120) ;
	
	// Tremelo effect

/* tremolo unit, using os.triangle or sine oscillator as lfo */

tremolo(freq, depth) = lfo * depth + 1 - depth : vactrol with {
    sine(freq) = (os.oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy

    SINE=hgroup( "Tremelo",checkbox("SINEWAVE[3][enum:os.triangle|sine]") );
    
    lfo = select2(SINE, trianglewave(freq), sine(freq));
};

	speed = hgroup( "Tremelo",vslider("speed[2][style:knob]",5,0.1,10,0.1) ) ;
	intensity = hgroup( "Tremelo", vslider("intensity[1][style:knob]",5,0,10,0.1)/10.2 ) ;
	effect =  tremolo(speed,intensity);
	vof = hgroup( "Tremelo",checkbox("vibe[0][enum:Off|On]"));
	vibe = select2(vof, 1.0, effect) ;

	
};
