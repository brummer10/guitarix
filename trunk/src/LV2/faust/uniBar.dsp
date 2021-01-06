declare name "Nonlinear Banded Waveguide Models";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "This instrument uses banded pm.waveguide. For more information, see Essl, G. and Cook, P. Banded Waveguides: Towards Physical Modelling of Bar Percussion Instruments, Proceedings of the 1999 International Computer Music Conference.";

import("stdfaust.lib");

bow(offset,slope) = pow(abs(sample) + 0.75, -4) : saturationPos
	with{
	sample(y) = (y + offset)*slope;
	};
    
bandPass(resonance,radius) = fi.TF2(b0,b1,b2,a1,a2)
	with{
		a2 = radius*radius;
		a1 = -2*radius*cos(ma.PI*2*resonance/ma.SR);
		b0 = 0.5-0.5*a2;
		b1 = 0;
		b2 = -b0;
	};

saturationPos(x) = x <: (_>1),(_<=1 : *(x)) :> +;
saturationNeg(x) = x <: (_<-1),(_>=-1 : *(x)) :> *(-1) + _;

//==================== GUI SPECIFICATION ================

freq = hslider("h:Basic Parameters/synthfreq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
gain = hslider("h:Basic Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",0.8,0,10,0.01)*10; 
gate = checkbox("h:Basic Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");

//==================== MODAL PARAMETERS ================

preset = 1;

nMode(1) = 4;

modes(1,0) = 1;
basegains(1,0) = pow(0.9,1);
excitation(1,0) = 1*gain/nMode(1);

modes(1,1) = 2.756;
basegains(1,1) = pow(0.9,2);
excitation(1,1) = 1*gain/nMode(1);

modes(1,2) = 5.404;
basegains(1,2) = pow(0.9,3);
excitation(1,2) = 1*gain/nMode(1);

modes(1,3) = 8.933;
basegains(1,3) = pow(0.9,4);
excitation(1,3) = 1*gain/nMode(1);

//==================== SIGNAL PROCESSING ================

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//the number of modes depends on the preset being used
nModes = nMode(preset);

//bow table parameters
tableOffset = 0;
tableSlope = 10 - (9);

delayLengthBase = ma.SR/freq;

//de.delay lengths in number of samples
delayLength(x) = delayLengthBase/modes(preset,x);

//de.delay lines
delayLine(x) = de.delay(4096,delayLength(x));

//Filter bank: fi.bandpass filters (declared in instrument.lib)
radius = 1 - ma.PI*32/ma.SR;
bandPassFilter(x) = bandPass(freq*modes(preset,x),radius);

//Delay lines feedback for bow table lookup control
baseGainApp = 0.8999999999999999 + (0.1);
velocityInputApp = 0.8;
velocityInput = velocityInputApp + _*baseGainApp,par(i,(nModes-1),(_*baseGainApp)) :> +;

//Bow velocity is controlled by an ADSR envelope
maxVelocity = 0.03 + 0.1*gain;
bowVelocity = maxVelocity*en.adsr(0.02,0.005,90,0.01,gate);

//----------------------- Algorithm implementation ----------------------------

//Bow table lookup (bow is decalred in instrument.lib)
bowing = bowVelocity - velocityInput <: *(bow(tableOffset,tableSlope)) : /(nModes);

//One resonance
resonance(x) = + : + (excitation(1,x)*gate) : delayLine(x) : _*basegains(1,x) : bandPassFilter(x);

/*process =
		//Bowed Excitation
		_<:((bowing <:
		//nModes resonances with nModes feedbacks for bow table look-up 
		(resonance(1)~_))~_);*/

process(x) =
		//Bowed Excitation
		(bowing <:
		//nModes resonances with nModes feedbacks for bow table look-up 
		par(i,nModes,(resonance(i)~_)))~par(i,nModes,_) :> _ : +(x) :_;
