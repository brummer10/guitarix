declare name "Compressor";
declare category "Guitar Effects";

/* Compressor unit. */

//declare name "compressor -- compressor/limiter unit";
declare author "Albert Graef";
declare version "1.0";

import("stdfaust.lib");
import("guitarix.lib");
rd = library("reducemaps.lib");

/* Controls. */

// partition the controls into these three groups
comp_group(x)	= hgroup("1-compression", x);
env_group(x)	= vgroup("2-envelop", x);
gain_group(x)	= vgroup("3-gain", x);

// compressor controls: ratio, threshold and knee size
ratio		= nentry("ratio[name:Ratio]", 2, 1, 20, 0.1);
threshold	= nentry("threshold[name:Threshold]", -20, -96, 10, 0.1);
knee		= nentry("knee[name:Knee]", 3, 0, 20, 0.1);

// attack and release controls; clamped to a minimum of 1 sample
attack		= hslider("attack[name:Attack]", 0.002, 0, 1, 0.001) : max(1/ma.SR);
release		= hslider("release[name:Release]", 0.5, 0, 10, 0.01) : max(1/ma.SR);

// gain controls: make-up gain, compression gain meter
makeup_gain	= gain_group(hslider("makeup gain[name:Makeup]", 0, -96, 96, 0.1));
gain(x)		= attach(x, x : gain_group(hbargraph("gain", -96, 0)));

t		= 0.1;
g		= exp(-1/(ma.SR*t));
env		= abs : *(1-g) : + ~ *(g);
rms		= sqr : *(1-g) : + ~ *(g) : sqrt;
sqr(x)		= x*x;

/* Compute the envelop of a stereo signal. Replace env with rms ba.if you want to
   use the RMS value instead. */

//env2(x,y)	= max(env(x),env(y));
env2(x)	= max(env(x));

/* Compute the compression factor for the current input level. The gain is
   always 0 dB ba.if we're below the reduced threshold, threshold-knee. Beyond
   the real threshold value the level is scaled by 1/ratio. Between these two
   extremes we return a convex combination of those factors. This is also
   known as "soft-knee" compression: the compression kicks in gradually at
   threshold-knee and reaches its full value at threshold. For special
   effects, you can also achieve old-school "hard-knee" compression by setting
   the knee value to fi.zero. Also note that, before computing the gain, the
   input level is first smoothed out using a 1 fi.pole IIR to prevent clicks when
   the input level changes abruptly. The attack and release times of this
   filter are configured with the corresponding envelop controls of the
   compressor. */

compress(env)	= level*(1-r)/r
with {
	// the (filtered) input level above the threshold
	level	= env : h ~ _ : ba.linear2db : (_-threshold+knee) : max(0)
	with {
		h(x,y)	= f*x+(1-f)*y with { f = (x<y)*ga+(x>=y)*gr; };
		ga	= exp(-1/(ma.SR*attack));
		gr	= exp(-1/(ma.SR*release));
	};
	// the knee factor, clamped to 0..1; we add a small perturbation in
	// the denominator to prevent infinities and nan when knee<<1
	p	= level/(knee+eps) : max(0) : min(1) with { eps = 0.001; };
	// the actual compression ratio
	r	= 1-p+p*ratio;
};

vmeter1(x)		= attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -70, +5));

envelop         = abs : max ~ (1.0/ma.SR) : rd.mean(2048); // : max(ba.db2linear(-70)) : ba.linear2db;

process(x)	= g(x)*x
with {
	//g	= env2(x) : compress : gain : +(makeup_gain) : ba.db2linear ;
	g	= add_dc : env : compress : vmeter1 : ba.db2linear ;
};
