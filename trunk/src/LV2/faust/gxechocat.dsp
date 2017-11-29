declare name "Tape Delay";
declare category "Echo / Delay";

import("stdfaust.lib");
import("guitarix.lib");
import("redeye.lib");

/*
HEAD SPACING

I have lold Selmer unit where playback heads are 1.5 inches apart
and record head is 1.8 inches from last playback so :

	record - play4 - play 3 - play 2 - play 1

		1.8  - 1.5 - 1.5 - 1.5 - 1.5
 
Se we have record -1.8inches - head1, 2.3 to head2, 3.8 to head3 5.3 to head 4 !
 Or	at 15ips	head1 120ms head2 220ms head3 320ms head4 420ms

According to what I have read the heads are not parallel but output from each one is fed into next ??? What ??? Also max de.delay from one head is 425ms
Apparently originsl units has 23 inch tapes!
  
Actual topology
In -> stage1 -> pentode driver for record head ->play heads -> 2stage valve amp ->mixer->out and feedback to pentode
Sounds OK maybe too much bandwidth loss try cleaner path
Look ay adding soft clip before machine to simulate saturation 
Frequency response of tape in copicat would be poor due to design and use
Tape usually has steep low end frop with a hump and not quite so steep high drop, maybe as for guitar we can lower this but would guess that should start around
	40 - 80Hz steep fi.highpass with possible hump ( ? resonant filter )
	5- 6k fi.lowpass
Am concerned that as each valve stage already has same lowapss filter that this
may have same effect as in real amp of creating a resonance an will try same solution : stagger filters and identify dominant one ( biggest effect ) and slug it or drastically reduce it.
*/

// So we need multiple de.delay heads
// Each head can be bypassed or moved to alter de.delay time
// so tape speed in inches per second
// distance from record head in inches
// thus we get de.delay in milliseconds
//speed = 7.5 ;

bpm = hgroup( "Echo", vslider("BPM[style:knob]", 120, 24, 360, 0.1)) ;

// The wow should be preset by experiment...
// Lets introduce just a little
sine(freq) = (os.oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
freq= 4 ; // 4Hz
depth = 0.005 ;	// Play with this
wow =  sine( freq) * depth ;
speed = ( 72/(2*bpm))  ;
tapespeed = hgroup( "Tape Control",speed + wow ); 

echo = hgroup( "Echo", vslider("Swell[style:knob]", 0, 0, 1, 0.01)) ;
feedback = hgroup( "Echo", vslider("Sustain[style:knob]", 0, 0.0, 0.95, 0.01));

dtime1 = ma.SR*( 60/bpm) ;
dtime2 = ma.SR*( 120/ bpm) ;
dtime3 = ma.SR*( 180/bpm ) ;
dtime4 = ma.SR*( 240/bpm ) ;

head1 = de.sdelay(N, interp, dtime1):*(checkbox("Head1")) with {
	interp = ma.SR/10.0; // 100*SER/1000
 	N = int( 2^19 ) ;
};
head2 = de.sdelay(N, interp, dtime2):*(checkbox("Head2")) with {
	interp = 100*ma.SR/1000.0;
 	N = int( 2^19 ) ;
};
head3 = de.sdelay(N, interp, dtime3):*(checkbox("Head3")) with {
	interp = 100*ma.SR/1000.0;
 	N = int( 2^19 ) ;
};
head4 = de.sdelay(N, interp, dtime4):*(checkbox("Head4")) with {
	interp = 100*ma.SR/1000.0;
 	N = int( 2^19 ) ;
};

// IN real machine the ECHO level control is after the last 2 stages of valves
machine = vgroup( "Tape Heads", fi.highpass( 4, 40 )<:head1,head2,head3:>fi.lowpass( 1, 6500 ):fi.dcblocker:*(echo) );

fbloop = fi.lowpass( 1, 7500 ):*(feedback):*(0.5):fi.highpass( 1, 125 )  ;

process = input12au7<:_,(+:_<:machine :>_)~fbloop:>output12au7:*(0.1) ;
