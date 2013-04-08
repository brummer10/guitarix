declare name "Tape Delay";
declare category "Echo / Delay";

import("music.lib");
import("effect.lib");
import("oscillator.lib");
import("guitarix.lib");

/*
HEAD SPACING

I have lold Selmer unit where playback heads are 1.5 inches apart
and record head is 1.8 inches from last playback so :


	record - play4 - play 3 - play 2 - play 1

		1.8  - 1.5 - 1.5 - 1.5 - 1.5
 
Se we have record -1.8inches - head1, 2.3 to head2, 3.8 to head3 5.3 to head 4 !
 Or	at 15ips	head1 120ms head2 220ms head3 320ms head4 420ms

According to what I have read the heads are not parallel but output from each one is fed into next ??? What ??? Also max delay from one head is 425ms
Apparently originsl units has 23 inch tapes!
  
Actual topology
In -> stage1 -> pentode driver for record head ->play heads -> 2stage valve amp ->mixer->out and feedback to pentode
Sounds OK maybe too much bandwidth loss try cleaner path
Look ay adding soft clip before machine to simulate saturation 
Frequency response of tape in copicat would be poor due to design and use
Tape usually has steep low end frop with a hump and not quite so steep high drop, maybe as for guitar we can lower this but would guess that should start around
	40 - 80Hz steep highpass with possible hump ( ? resonant filter )
	5- 6k lowpass
Am concerned that as each valve stage already has same lowapss filter that this
may have same effect as in real amp of creating a resonance an will try same solution : stagger filters and identify dominant one ( biggest effect ) and slug it or drastically reduce it.
*/

// So we need multiple delay heads
// Each head can be bypassed or moved to alter delay time
// so tape speed in inches per second
// distance from record head in inches
// thus we get delay in milliseconds
speed = 7.5 ;
// The wow should be preset by experiment...
// Lets introduce just a little
sine(freq) = (oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
freq= 4 ; // 4Hz
depth = 0.005 ;	// Play with this
wow =  sine( freq) * depth ;
tapespeed = hgroup( "Tape Control",speed + wow ); 

// Control input level
input = hgroup( "Input", vslider("InputGain[style:knob]", 0, 0, 1.0, 0.01) );
gain = hgroup( "Output", vslider("OutputGain[style:knob]", 0, 0, 1.0, 0.01));
echo = hgroup( "Echo", vslider("Swell[style:knob]", 0, 0, 1, 0.1)) ;
feedback = hgroup( "Echo", vslider("Sustain[style:knob]", 0, 0.0, 0.95, 0.01));

dtime1 = SR*( 1.5/tapespeed) ;
dtime2 = SR*( 3.0/tapespeed) ;
dtime3 = SR*( 4.5/tapespeed ) ;
dtime4 = SR*( 6.0/tapespeed ) ;

head1 = sdelay(N, interp, dtime1):*(checkbox("Head1")) with {
	interp = SR/10.0; // 100*SER/1000
 	N = int( 2^19 ) ;
};
head2 = sdelay(N, interp, dtime2):*(checkbox("Head2")) with {
	interp = 100*SR/1000.0;
 	N = int( 2^19 ) ;
};
head3 = sdelay(N, interp, dtime3):*(checkbox("Head3")) with {
	interp = 100*SR/1000.0;
 	N = int( 2^19 ) ;
};
head4 = sdelay(N, interp, dtime4):*(checkbox("Head4")) with {
	interp = 100*SR/1000.0;
 	N = int( 2^19 ) ;
};

// Added gain reduction to get unity gain at 0dB ( trial and error for each stage )
// Real tube values 
//	Fk		Rk			Vk
//			1500		1.3
//			2700		1,83
//			820			0.96
stage1 = tubestage(TB_12AX7_68k,2.1,1500.0,1.204541) ; // Gain 2.9   2nd -29.8 3rd -26.24
// End amp is 2 stages of 12AX7 with 100K anode and 3k3 and then 2k2 cathode!
// Tube details 3k3 cathode res 2.637334 vk0
// Tube details 2k2 cathode res 2.426864 vk0
stage2 =tubestage(TB_12AX7_250k,2.1,3300.0,2.637334) ; 
stage3 =tubestage(TB_12AX7_250k,2.1, 2200.0,2.426864) ; 

// IN real machine the ECHO level control is after the last 2 stages of valves
machine = vgroup( "Tape Heads", highpass( 4, 40 )<:head1,head2,head3:>lowpass( 1, 6500 ):dcblocker:*(echo) );

fbloop = lowpass( 1, 7500 ):*(feedback):*(0.5):highpass( 1, 125 )  ;

process = highpass( 1, 80 ):*(input):stage1<:_,(+:_<:machine :>stage2:stage3)~fbloop:>*(gain);

