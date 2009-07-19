declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

/*-----------------------------------------------
		      The tone control
   Low and high shelf filters, from Robert Bristow-Johnson's "Audio
   EQ Cookbook", see http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt.
  -----------------------------------------------*/

/* Fixed bass and treble frequencies.*/
bass_freq	= 660;
//mid_freq = 600;
treble_freq	= 4978;

filter(b0,b1,b2,a0,a1,a2)	= f : (+ ~ g)
with {
	f(x)	= (b0/a0)*x+(b1/a0)*x'+(b2/a0)*x'';
	g(y)	= 0-(a1/a0)*y-(a2/a0)*y';
};

low_shelf(f0,g)		= filter(b0,b1,b2,a0,a1,a2)
with {
	S  = 1;
	A  = pow(10,g/40);
	w0 = 2*PI*f0/SR;
	alpha = sin(w0)/2 * sqrt( (A + 1/A)*(1/S - 1) + 2 );

	b0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
	b1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
	b2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
	a0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
	a1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
	a2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;
};

high_shelf(f0,g)	= filter(b0,b1,b2,a0,a1,a2)
with {
	S  = 1;
	A  = pow(10,g/40);
	w0 = 2*PI*f0/SR;
	alpha = sin(w0)/2 * sqrt( (A + 1/A)*(1/S - 1) + 2 );

	b0 =    A*( (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha );
	b1 = -2*A*( (A-1) + (A+1)*cos(w0)                   );
	b2 =    A*( (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha );
	a0 =        (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha;
	a1 =    2*( (A-1) - (A+1)*cos(w0)                   );
	a2 =        (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha;
};


bass_gain	= vslider("bass", 0, -20, 20, 0.1);
mid_gain	= vslider("mid", 0, -20, 20, 0.1);
treble_gain	= vslider("treble", 0, -20, 20, 0.1);
tone		= hgroup("tone",low_shelf(bass_freq,bass_gain): low_shelf(treble_freq,mid_gain): high_shelf(bass_freq,mid_gain): high_shelf(treble_freq,treble_gain));

process = tone:_;



