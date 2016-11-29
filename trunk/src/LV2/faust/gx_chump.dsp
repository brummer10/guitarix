declare id "Redeye Chump"; // in amp tube selector
declare name "Redeye Chumo";
declare category "Amplifier";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
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



process = chumpPreamp:( + : poweramp:transformer )~feedback:*(volume) with{

	volume =  vslider("Volume[alias][style:knob]",0.5,0,1,0.01):smoothi(0.999);
	poweramp = lowpass(1,6531.0):tubestage(TB_6V6_250k,120.0,820.0,1.130462) ;
   transformer = lowpass( 1, 6531 ):highpass( 1, 80) ;
	feedback = *(checkbox("feedback") ):high_shelf( 3, 6531 ): *(-0.5);

};
