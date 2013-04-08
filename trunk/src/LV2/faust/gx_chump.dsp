declare id "Redeye Chump"; // in amp tube selector
declare name "Redeye Chumo";
declare category "Amplifier";

import("music.lib");
import("filter.lib");
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

// Note that we seem to have far too much gain for use as a plugin
// Well before we get decent guitar sounds Ardour has run out of headroom 
// Have to set track fader to very low level....

process =  stage1:tone:*(preamp):( + : stage2:transformer )~feedback with {
    preamp =  vslider("Gain[alias][style:knob]",0,-20,20,0.1):db2linear: smoothi(0.999);
	stage1= tubestage(TB_12AX7_68k,86.0,2700.0,1.581656) ; 
	tone = component("bigmuff.dsp").bigmuff ;
	// This range 0.1 -> 10
	volume =  vslider("Volume[alias][style:knob]",0,-20,10,0.1):db2linear:smoothi(0.999);
	// Ideally attenuation should be proportional to the volume so that we achieve
	// a kind of compression if volume > 0dB 
	//atten = 0.5; // Seems to need at least this much!
	atten = 1-( volume/20);

	stage2 =  lowpass(1,6531.0):tubestage(TB_12AX7_250k,100.0,1500.0,1.204285):*(volume):lowpass(1,6531.0):tubestage(TB_6V6_250k,120.0,820.0,1.130462):*(atten); 
       transformer = lowpass( 1, 6531 ):highpass( 1, 120) ;
	feedback = *(checkbox("feedback") ):high_shelf( 3, 6531 ): *(-0.5);
      cabinet = lowpass(2,5500):peak_eq(-15.0,400.0,400):highpass(2,120);

};

