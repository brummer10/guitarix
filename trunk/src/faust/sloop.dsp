declare id 		"sloop";
declare version 	"1.0";
declare author 		"brummer";
declare license 	"BSD";

import("stdfaust.lib");

B = checkbox("Capture");	// Capture sound while pressed
C = checkbox("Play");

I = int(B);				// convert button signal from float to integer
R = (I-I') <= 0;		// Reset capture when button is pressed
D = (+(I):*(R))~_;		// Compute capture duration while button is pressed: 0..NNNN0..MMM

capture = ( *(B) : (+ : de.de.fdelay(2097152, D-1)) ~ *(1.0-B)) *(C);

si.smooth(c)	= *(1-c) : +~*(c);
level		= hslider("gain", 0, -96, 4, 0.1) : ba.db2linear : si.smooth(0.999);

process 	= vgroup( "SampleLooper", _ <:_, (capture : *(level)):>_ ) ;
