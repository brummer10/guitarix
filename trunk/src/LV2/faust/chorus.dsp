declare name "Chorus";
declare category "Modulation";

/* Stereo chorus. */

// declare name "chorus -- stereo chorus effect";
declare author "Albert Graef";
declare version "1.0";

import("stdfaust.lib");

level	= hslider("level", 0.5, 0, 1, 0.01) : si.smooth(0.993);
freq	= hslider("freq", 3, 0, 10, 0.01) : si.smooth(0.993);
dtime	= hslider("de.delay", 0.02, 0, 0.2, 0.01) : si.smooth(0.993);
depth	= hslider("depth", 0.02, 0, 1, 0.01) : si.smooth(0.993);

tblosc(n,f,freq,mod)	= (1-d)*rdtable(n,wform,i&(n-1)) +
			  d*rdtable(n,wform,(i+1)&(n-1))
with {
	wform 	= ba.time*(2.0*ma.PI)/n : f;
	phase		= freq/ma.SR : (+ : ma.decimal) ~ _;
	modphase	= ma.decimal(phase+mod/(2*ma.PI))*n;
	i		= int(floor(modphase));
	d		= ma.decimal(modphase);
};

interp = ma.SR/1000.0;

chorus(dtime,freq,depth,phase,x)
			= x+level*de.sdelay(1<<16, interp, t, x)
with {
	t		= ma.SR*dtime/2*(1+depth*tblosc(1<<16, sin, freq, phase));
};

process			= vgroup("chorus", (left, right))
with {
	left		= chorus(dtime,freq,depth,0);
	right		= chorus(dtime,freq,depth,ma.PI/2);
};
