declare id 		"tonemodul";
declare name            "3 Band EQ";
declare category        "Tone Control";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("stdfaust.lib");
import("guitarix.lib");

F = 600; //nentry("split_low_freq", 250, 20, 600, 10);
F1 = 1200; //nentry("split_middle_freq", 650, 600, 1250, 10);
F2 = 2400; //nentry("split_high_freq", 1250, 1250, 12000, 10);

/**********************************************************************
*** this part is included here for backward compatibility from 0.9.27 to
*** 0.9.24 
***********************************************************************/

//------------------------------ ba.count and ba.take --------------------------------------

countN ((xs, xxs)) = 1 + countN(xxs);
countN (xx) = 1;

takeN (1, (xs, xxs))     = xs;
takeN (1, xs)                    = xs;
takeN (nn, (xs, xxs))    = takeN (nn-1, xxs);

//------------------------------ low/high-passfilters --------------------------------------

tf1N(b0,b1,a1) = _ <: *(b0), (mem : *(b1)) :> + ~ *(0-a1);

tf2N(b0,b1,b2,a1,a2) = sub ~ conv2(a1,a2) : conv3(b0,b1,b2)
with {
  conv3(k0,k1,k2,x)     = k0*x + k1*x' + k2*x'';
  conv2(k0,k1,x)        = k0*x + k1*x';
  sub(x,y)              = y-x;
};

tf1sN(b1,b0,a0,w1) = tf1N(b0d,b1d,a1d)
with {
  c   = 1/tan((w1)*0.5/ma.SR); // bilinear-transform scale-factor
  d   = a0 + c;
  b1d = (b0 - b1*c) / d;
  b0d = (b0 + b1*c) / d;
  a1d = (a0 - c) / d;
};

tf2sN(b2,b1,b0,a1,a0,w1) = tf2N(b0d,b1d,b2d,a1d,a2d)
with {
  c   = 1/tan((w1)*0.5/ma.SR); // bilinear-transform scale-factor
  csq = c*c;
  d   = a0 + a1 * c + csq;
  b0d = (b0 + b1 * c + b2 * csq)/d;
  b1d = 2 * (b0 - b2 * csq)/d;
  b2d = (b0 - b1 * c + b2 * csq)/d;
  a1d = 2 * (a0 - csq)/d;
  a2d = (a0 - a1*c + csq)/d;
};

lowpassN(N,fc) = lowpass0_highpass1N(0,N,fc);
highpassN(N,fc) = lowpass0_highpass1N(1,N,fc);
lowpass0_highpass1N(s,N,fc) = lphpr(s,N,N,fc)
with {
  lphpr(s,0,N,fc) = _;
  lphpr(s,1,N,fc) = tf1sN(s,1-s,1,2*ma.PI*fc);
  lphpr(s,O,N,fc) = lphpr(s,(O-2),N,fc) : tf2sN(s,0,1-s,a1s,1,w1) with {
    parity = N % 2;
    S = (O-parity)/2; // current section number
    a1s = -2*cos(-ma.PI + (1-parity)*ma.PI/(2*N) + (S-1+parity)*ma.PI/N);
    w1 = 2*ma.PI*fc;
  };
};

//------------------------------ an.analyzer --------------------------------------
analyzern(O,lfreqs) = _ <: bsplit(nb) with
{
   nb = countN(lfreqs);
   fc(n) = takeN(n, lfreqs);
   lp(n) = lowpassN(O,fc(n));
   hp(n) = highpassN(O,fc(n));
   bsplit(0) = _;
   bsplit(i) = hp(i), (lp(i) <: bsplit(i-1));
};

analyzerN(lfreqs) = analyzern(3,lfreqs);

filterbankn(O,lfreqs) = analyzern(O,lfreqs) : delayeq with
{
   nb = ba.count(lfreqs);
   fc(n) = ba.take(n, lfreqs);
   ap(n) = fi.highpass_plus_lowpass(O,fc(n));
   delayeq = par(i,nb-1,apchain(nb-1-i)),_,_;
   apchain(0) = _;
   apchain(i) =  ap(i) : apchain(i-1);
};

filterbankN(lfreqs) = fi.filterbank(3,lfreqs);

/**********************************************************************
*** end for backward compatibility from 0.9.27 to
*** 0.9.24 , it could removed when switch completly to > 0.9.27
***********************************************************************/

//----------tone_controll---------

t = vslider("Treble[name:Treble", 0., -5., 5, 0.01): ba.db2linear : smoothi(0.999);
m = vslider("Middle[name:Middle", 0., -5., 5, 0.01): ba.db2linear : smoothi(0.999);
l = vslider("Bass[name:Bass", 0., -5., 5, 0.01): ba.db2linear : smoothi(0.999) ;

//tstack = component("tonestack.dsp");
sharp = vslider("sharper[name:Sharp]", -2, -2.5, 5, 0.1);
press = -5. * sharp;

attack  = 0.005;
release = 5.0;
knee    = 10.5;
ratio   = 3.0;

env = abs : max(1);

compress(env) = level * (1-r)/r
with {
	level = env : h ~ _ : ba.linear2db : (_ - press ) : max(0)
	with {
		h(x,y)  = f*x+(1-f)*y with { f = (x<y)*ga+(x>=y)*gr; };
		ga      = exp(-1/(ma.SR*attack));
		gr      = exp(-1/(ma.SR*release));
	};
	p = level/(knee+eps) : max(0) : min(1) with { eps = 0.001; };
	r = 1 - p + p * ratio;
};

comp1(x) = g(x) * x
with {
	g = env : compress + sharp : ba.db2linear;
};
comp = BP( comp1);

tone_controll =  _ : filterbankN((F,F2)): *(t),*(m),*(l):>_;

process 		=  (tone_controll : comp) ,(tone_controll : comp);
