
/* Expander unit. */

/* This is pretty much the same as compressor.dsp, but here the given ratio is
   applied to *attenuate* levels *below* the threshold. */

declare name "Expander";
declare category "Guitar Effects";

declare description "expander unit";
declare author "Albert Graef";
declare version "1.0";

import("stdfaust.lib");
import("reduce.lib");

/* Controls. */

ratio		= nentry("ratio", 2, 1, 20, 0.1);
threshold	= nentry("threshold", -40, -96, 10, 0.1);
knee		= nentry("knee", 3, 0, 20, 0.1);

attack		= hslider("attack", 0.001, 0, 1, 0.001) : max(1/ma.SR);
release		= hslider("release", 0.1, 0, 10, 0.01) : max(1/ma.SR);

t		= 0.1;
g		= exp(-1/(ma.SR*t));
env		= abs : *(1-g) : + ~ *(g);
rms		= sqr : *(1-g) : + ~ *(g) : sqrt;
sqr(x)		= x*x;

env2(x)	= max(env(x));

expand(env)	= level*(1-r)
with {
	level	= env : h ~ _ : ba.linear2db : (threshold+knee-_) : max(0)
	with {
		h(x,y)	= f*x+(1-f)*y with { f = (x<y)*ga+(x>=y)*gr; };
		ga	= exp(-1/(ma.SR*attack));
		gr	= exp(-1/(ma.SR*release));
	};
	p	= level/(knee+eps) : max(0) : min(1) with { eps = 0.001; };
	r	= 1-p+p*ratio;
};

vmeter1(x)		= attach(x, envelop(x) : vbargraph("v1[nomidi:no]", -70, +5));

envelop         = abs : max ~ (1.0/ma.SR) : reduce(max,4096); // : max(ba.db2linear(-70)) : ba.linear2db;

process(x)	= (g(x)*x)
with {
	g	= env2(x) : expand : vmeter1 : ba.db2linear;
};
