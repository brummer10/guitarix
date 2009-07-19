declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");

switch1		= checkbox("on/off");
echo = _ ;
smoothi(c)	= *(1-c) : +~*(c);
gain		= vslider("gain", 0, -40, 40, 0.1) : db2linear : smoothi(0.999);
resonator(d,a) 	= (+ <: (delay(4096, d-1) + delay(4096, d))/2.0)~*(1.0-a) ;

// preamp
k = 2*(0.05)/(1-0.05);
fee = (1+k)*(20)/(1+k*abs(20));
verb3    	= select2(switch1, _, _);
pa = vgroup ("preamp",_<: _, *(fee): verb3);

/*-----------------------------------------------
		      The tone control
   Low and high shelf filters, from Robert Bristow-Johnson's "Audio
   EQ Cookbook", see http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt.
  -----------------------------------------------*/

/* Fixed bass and treble frequencies.*/
bass_freq	= 300;
treble_freq	= 1200;

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
treble_gain	= vslider("treble", 0, -20, 20, 0.1);
tone		= hgroup("tone",low_shelf(bass_freq,bass_gain) : high_shelf(treble_freq,treble_gain));
vol		= hgroup("in", *(gain, echo));

g1  = hslider("feedforward gain", 0, -1, 1, 0.01);
g2  = hslider("feedback gain", 0, -1, 1, 0.01);

feedbackco = firparto : + ~ feedbacko
with {
  firparto(x) = x + g1 * x''';
  feedbacko(v) = 0 - g2 * v'''';
};

process = hgroup("monoamp",pa:vol:tone:feedbackco);



