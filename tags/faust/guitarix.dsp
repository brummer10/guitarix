
declare name 		"guitarfx";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

/*-----------------------------------------------
 		Vibrato Volume control in dB
  -----------------------------------------------*/

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");
import("osc.lib");  

echo1  = hgroup("echo", +~(delay(131072,   int(vslider("time", 0, 0,	2000, 1)*millisec)-1) * (vslider("release", 0, 0,  100, 0.1)/100.0)));

//a		= 0.12;
//d		= 0.1;

 

echo = _ ;

smoothi(c)	= *(1-c) : +~*(c);
gain		= vslider("gain", 0, -40, 40, 0.1) : db2linear : smoothi(0.999);
gain1		= vslider("gain", 0, -40, 40, 0.1) : db2linear : smoothi(0.999);

resonator(d,a) 	= (+ <: (delay(4096, d-1) + delay(4096, d))/2.0)~*(1.0-a) ;

mono2stereo 	=  _ <:  _,_;
mono2mono 	=  _ <:  _,_;
monomono 	=  _ <:  _,_;
monom 	=  _ <:  _,_;
mono2 	=  _ <:  _,_;
mono2i 	=  _ <:  _,_;

/*----------------------------------------------- 
		Balance control linear 
  -----------------------------------------------*/

bal		= hslider("balance", 0, -1, 1, 0.001);
balance		= *(1-max(0,bal)), *(1-max(0,0-bal));

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
/*-----------------------------------------------
		freeverb  by "Grame"
  -----------------------------------------------*/

// Filter Parameters

combtuningL1	= 1116;
combtuningL2	= 1188;
combtuningL3	= 1277;
combtuningL4	= 1356;
combtuningL5	= 1422;
combtuningL6	= 1491;
combtuningL7	= 1557;
combtuningL8	= 1617;

allpasstuningL1	= 556;
allpasstuningL2	= 441;
allpasstuningL3	= 341;
allpasstuningL4	= 225;


dampslider 		= vslider("damp",0.5, 0, 1, 0.025)*0.4;
roomsizeSlider 	= vslider("RoomSize", 0.5, 0, 1, 0.025)*0.28 + 0.7;
combfeed 		= roomsizeSlider;
wetslider 		= vslider("wet", 0.3333, 0, 1, 0.025);

// Comb and Allpass filters

allpass(dt,fb) = (_,_ <: (*(fb):+:@(dt)), -) ~ _ : (!,_);
comb(dt, fb, damp) = (+:@(dt)) ~ (*(1-damp) : (+ ~ *(damp)) : *(fb));

// Reverb components

monoReverb(fb1, fb2, damp, spread)
	= _ <:	comb(combtuningL1+spread, fb1, damp),
			comb(combtuningL2+spread, fb1, damp),
			comb(combtuningL3+spread, fb1, damp),
			comb(combtuningL4+spread, fb1, damp),
			comb(combtuningL5+spread, fb1, damp),
			comb(combtuningL6+spread, fb1, damp),
			comb(combtuningL7+spread, fb1, damp),
			comb(combtuningL8+spread, fb1, damp)
		+>
		 	allpass (allpasstuningL1+spread, fb2)
		:	allpass (allpasstuningL2+spread, fb2)
		:	allpass (allpasstuningL3+spread, fb2)
		:	allpass (allpasstuningL4+spread, fb2)
		;

//----------------------------------------------------------------

fxctrl(g,w,Fx) =  _ <: (*(g),*(g) : Fx : *(w),*(w)), *(1-w), *(1-w) +> _;
//freeverb = fxctrl(0.015, 0.5, monoReverb(combfeed, 0.5, 0.5, 23));
freeverb = fxctrl(0.015, wetslider, monoReverb(combfeed, 0.5, dampslider, 23));




/*bandfilter 		= hgroup("Multi Band Filter",
							seq( i, 10, vgroup(" %i", component("bandfilter.dsp").bandfilter(1000*(1+i))) )
						);*/


/*-----------------------------------------------
		boxes
  -----------------------------------------------*/

play = checkbox("play");
playit = _ : _';
playitnow = vgroup("play", *(playit, play));

switch		= checkbox("on/off");
switch1		= checkbox("on/off");
dist    	= select2(switch, _, _);
verb    	= select2(switch1, _, _);
verb1    	= select2(switch1, _, _);
verb2    	= select2(switch1, _, _);

//----------distortion---------

//-speaker emulation
sbp1  = vslider("low-freq cutoff Hz",130,20,1000,1);
sbp2  = vslider("high-freq cutoff Hz",5000,1000,10000,1);
sbpon =  select2(switch1, _, _);
sbp = hgroup("sp",_<:(_, speakerbp(sbp1,sbp2)) : sbpon);

//-low and highpass
lowpassfreq = nentry("freqlow", 723, 20, 7040, 1);  // Hz723.431
highpassfreq = nentry("freqhigh", 720, 20, 7040, 1);  // Hz720.484
passon =  select2(switch1, _, _);
passo = vgroup("",lowpass1(lowpassfreq) : highpass1(highpassfreq ));
pass = hgroup("low/highpass",_<:(_, passo) : passon);

//-distortion
drivelevel = vslider("drivelevel", 0.01, 0, 1, 0.01);
drivegain1		= vslider("gain", 2, 0, 10, 0.1)-10 : db2linear : smoothi(0.999);
//drivegain		= (-8.0) : db2linear : smoothi(0.999);
drive		= vslider("drive", 0.64, 0, 1, 0.01);
distortion 	= cubicnl(drive,drivelevel); 

//-resonator
d 		= vslider("vibrato", 0.5, 0, 1, 0.01);
a 		= vslider("trigger", 0.12, 0, 1, 0.01);
reso = vgroup("resonans", resonator(d,a));


showme		= hgroup("distortion", (resonator(0.1,0.12) , (reso :pass : sbp  : distortion : *(drivegain1, echo) : sbp)) : dist);



showme1		= vgroup("freeverb", monomono : _, freeverb : verb);
bass_gain	= vslider("bass", 0, -20, 20, 0.1);
treble_gain	= vslider("treble", 0, -20, 20, 0.1);
tone		= hgroup("tone",low_shelf(bass_freq,bass_gain) : high_shelf(treble_freq,treble_gain));
vol		= hgroup("in", *(gain, echo));
vol1		= hgroup("out", *(gain1, echo));

/* GUI Controls */
g1  = hslider("feedforward gain", 0, -1, 1, 0.01);
g2  = hslider("feedback gain", 0, -1, 1, 0.01);

feedbackco = firparto : + ~ feedbacko
with {
  firparto(x) = x + g1 * x''';
  feedbacko(v) = 0 - g2 * v'''';
};

  g3  = hslider("peak gain", 1, 0, 10, 0.2);
 fr = hslider("frequency (Hz)", 440, 20, 2200, 10);
feedbackcontroll = firpart : + ~ feedback 
with {
  bw = hslider("bandwidth (Hz)", 100, 20, 20000, 10);
  //bw = 100; //fr = 440; //g = 1; // parameters - see caption
  SR = fconstant(int fSamplingFreq, <math.h>); // Faust fn
  pi = 4*atan(1.0);    // circumference over diameter
  R = exp(0-pi*bw/SR); // pole radius [0 required]
  A = 2*pi*fr/SR;      // pole angle (radians pole = 2)
  RR = R*R;
  firpart(x) = (x - x'') * g3 * ((1-RR)/2);  // radius = 2
  // time-domain coefficients ASSUMING ONE PIPELINE DELAY:
  feedback(v) = 0 + 2*R*cos(A)*v - RR*v';
};
ir =  hgroup("IR", (mono2i : _,feedbackcontroll:>_ ));
 ImpulseResponse = vgroup("IR", (mono2 : _,ir:>_ : verb2));

echo2  = vgroup("echo", (mono2stereo : _,echo1:>_ : dist));
balcb		= hslider("wet/dry", 0, -1, 1, 0.001);
balancecb		= *(1-max(0,0-balcb)), *(1-max(0,balcb));
le   = vslider("level",0.1,0,1,0.01);
wah  = vslider("wah", 0, 0, 1, 0.01);
showme2		= hgroup("crybaby",monom : _, (_<: balancecb:(*(le): crybaby(wah)),_:>_) : verb1);


// preamp
k = 2*(0.05)/(1-0.05);
fee = (1+k)*(20)/(1+k*abs(20));
verb3    	= select2(switch1, _, _);
pa = vgroup ("preamp",_<: _, *(fee): verb3);


gainjc		= hslider("jcgain", 0, -40, 40, 0.1) : db2linear : smoothi(0.999);
verb4    	= select2(switch1,_,_);



playjc = checkbox("playjc");
playitjc = _ : _';
playitnowjc = vgroup("playjc", *(playjc,playitjc));
baljc		= hslider("jcbalance", 0, -1, 1, 0.001);
balancejc		= *(1-max(0,0-baljc)), *(1-max(0,baljc));

jcoutput            = (playitnowjc, playitnowjc: *(gainjc , echo), *(gainjc , echo));
//( (_,*(gainjc , echo)),(_,*(gainjc , echo)))

transpose (w, x, s, sig)  =
	fdelay1s(d,sig)*fmin(d/x,1) + fdelay1s(d+w,sig)*(1-fmin(d/x,1))
	   	with {
			i = 1 - pow(2, s/12);
			d = i : (+ : +(w) : fmod(_,w)) ~ _;
	        };

pitchshifter = vgroup("Pitch Shifter", transpose(
									hslider("window (samples)", 1000, 50, 10000, 1),
									hslider("xfade (samples)", 10, 1, 10000, 1),
									hslider("shift (semitones) ", 0, -12, +12, 0.1)
								  )
				);

balpitch		= hslider("wet/dry", 0, -1, 1, 0.001);
balancepitch		= *(1-max(0,0-balpitch)), *(1-max(0,balpitch));
pitchio    	= select2(switch1,_,_);
pit  = hslider("delay", 0, 1, 60000, 10);
pitch = hgroup("pitch",monom : _, (_<: balancecb: (pitchshifter:fdelay3(65536,pit)) ,_:>_) : pitchio); 


compressor 		= hgroup("compressor", component("compressor.dsp") );
/*-----------------------------------------------
		main process
  -----------------------------------------------*/

guitar 		= hgroup("controls", (playitnow : pa :  _: vol  : mono2mono : showme : tone : showme2 : showme1 : vol1 : echo2 ));
//guitar 		= hgroup("controls", (playitnow : pa :  _: vol  : mono2mono : showme : tone :showme2 : showme1  : echo2 <: compressor :>_: vol1));
//guitar 		= hgroup("controls", (playitnow : pa :  _: vol  : mono2mono : showme :pitch : tone :showme2 : showme1 : vol1 : echo2 ));
//process 	= guitar;
process 	= vgroup("monoamplifier", (guitar : ImpulseResponse : feedbackco: _<:_,_: balance : (_<:((_<:balancejc):(_,verb4))),((_<:(_<:balancejc):(_,verb4))) ));

//  preamp > gain in > distortion > bass/treble > crybaby > freeverb > gain out > echo > ImpulseResponse >  feedbak/feedforward > balance > jconv
