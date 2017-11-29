declare id "RedeyePreStereo"; 
declare name "RedeyePreStereo";

import("stdfaust.lib"); 
import("guitarix.lib");

// Using guitarix tubes to create a simple line stage emulation stereo
// 

//stage1 has approx 3.2dB gain
//stage2 has -10.7dB gain
stage1adjust = *( -3.2:ba.db2linear);
stage2adjust = *( 10.7:ba.db2linear);
stage1 = tubestage(TB_12AX7_68k,40.0,1500.0,1.5025):stage1adjust; 
stage2 = tubestage(TB_12AX7_68k,20.0,1500.0,1.4925):stage1adjust ; 
// We now have untiy gain stages which makes feedback easier to apply consistently 
// And measure freq response flat up tpo around 19K then slow rolloff
// Feedback : 
// Fror some reason what works here causes trouble in LV2 plugin ?
//  Basically we have a peak eq around 17-18k when feedback applied
// Could this be phase shifts caused by filters in feedback loop?
level =  vslider("Feedback[alias][style:knob]",-12,-75,-3,0.1):ba.db2linear:smoothi(0.999) ; 

// This could be a ba.selector :
//	Peak_EQ at 2500Hz = guitar presence
//  High shelf at 1500Hz = Alternative Guitar
//  High shelf at 2500Hz = Studio presence/air

//guitar = fi.peak_eq_cq( -presence, 2500, 6.0 );
//guitar2 = fi.high_shelf( -presence, 1500 );
//studio = fi.high_shelf( -presence, 2500 );

presence_filter = fi.high_shelf( -presence, 1500 );

lineamp = stage1:stage2 ;

input =  vslider("Input[alias][style:knob]",0,-20,20,0.1):ba.db2linear:smoothi(0.999)  ; 
output =   vslider("Output[alias][style:knob]",0,-20,20,0.1) :ba.db2linear:smoothi(0.999);

// With the shelf filter no response after 18dB only gives 4dB boost
//presence =  vslider("Presence[alias][style:knob]",0,0,10,0.1)/10:  smoothi(0.999):*(24);
presence =  vslider("Presence[alias][style:knob]",0,0,10,0.1)/10:smoothi(0.999):*(24);
// This needs to be sorted so that minimum is lowest but not off
// At poresent basically - 2.0 so we could make 1+1 
// Drive in db -12db->+12dB
drive =  vslider("Drive[alias][style:knob]",0.0,-15.0,15.0,0.1):ba.db2linear:smoothi(0.999);
resonance =  vslider("Resonance[alias][style:knob]",0,0,10,0.1)/10:smoothi(0.999):*(24);
// Does altering position of level affect strength of filters
//feedback = hgroup( "Processing", *(level):presence_filter:fi.low_shelf( -resonance,750):*(-1)); 
feedback = hgroup( "Processing",fi.low_shelf( -resonance,750):presence_filter:*(level):*(-1)); 
//channel =hgroup("Input", *(input)):hgroup("Tube",*(1.0+drive)):(+:lineamp)~ feedback:hgroup("Output",fi.lowpass( 1, 15000 ) :*(output));

channel =hgroup("Input", *(input)):hgroup("Tube",*(drive)):
(+:lineamp)~feedback:hgroup("Output",fi.lowpass( 1, 18000 ) :*(output));
process =channel,channel ;
