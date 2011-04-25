declare name "shaper";

import("music.lib");

sharp = vslider("sharper[name:sharper]", 1, 1, 10, 1);
press = 5 * sharp;

attack  = 0.005;
release = 10;
knee    = 10.5;
ratio   = 1.5;

env = abs : max(1);

compress(env) = level * (1-r)/r
with {
	level = env : h ~ _ : linear2db : (_ + press) : max(0)
	with {
		h(x,y)  = f*x+(1-f)*y with { f = (x<y)*ga+(x>=y)*gr; };
		ga      = exp(-1/(SR*attack));
		gr      = exp(-1/(SR*release));
	};
	p = level/(knee+eps) : max(0) : min(1) with { eps = 0.001; };
	r = 1 - p + p * ratio;
};

process(x) = g(x) * x
with {
	g = env : compress + sharp : db2linear;
};
