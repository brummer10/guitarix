declare name 		"sloop";
declare category "Echo / Delay";
declare version 	"1.0";
declare author 		"brummer";
declare license 	"BSD";


import("music.lib");


B = checkbox("Capture");	// Capture sound while pressed
C = checkbox("Play");

I = int(B);				// convert button signal from float to integer
R = (I-I') <= 0;		// Reset capture when button is pressed
D = (+(I):*(R))~_;		// Compute capture duration while button is pressed: 0..NNNN0..MMM


capture = ( *(B) : (+ : fdelay(2097152, D-1)) ~ *(1.0-B)) *(C);


smooth(c)	= *(1-c) : +~*(c);
level		= hslider("gain", 0, -96, 4, 0.1) : db2linear : smooth(0.999);

process 	= vgroup( "sloop", _ <:_, (capture : *(level)):>_ ) ;

