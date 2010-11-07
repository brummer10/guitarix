
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("effect.lib"); 
import("guitarix.lib");
import("math.lib");

//-speaker emulation
sbp1    		= vslider("low_freq[name:low freq][tooltip:low-freq cutoff Hz]",130,20,1000,10);
sbp2    		= vslider("high_freq[name:high freq][tooltip:high-freq cutoff Hz]",5000,1000,12000,10);
switch1 		= checkbox("on_off[name:low highcutoff]");
sbp 			= hgroup("lhc", bypass(switch1, +(anti_denormal_ac) : speakerbp(sbp1,sbp2)));


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
  c   = 1/tan((w1)*0.5/SR); // bilinear-transform scale-factor
  d   = a0 + c;
  b1d = (b0 - b1*c) / d;
  b0d = (b0 + b1*c) / d;
  a1d = (a0 - c) / d;
};

tf2sN(b2,b1,b0,a1,a0,w1) = tf2N(b0d,b1d,b2d,a1d,a2d)
with {
  c   = 1/tan((w1)*0.5/SR); // bilinear-transform scale-factor
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
  lphpr(s,1,N,fc) = tf1sN(s,1-s,1,2*PI*fc);
  lphpr(s,O,N,fc) = lphpr(s,(O-2),N,fc) : tf2sN(s,0,1-s,a1s,1,w1) with {
    parity = N % 2;
    S = (O-parity)/2; // current section number
    a1s = -2*cos(-PI + (1-parity)*PI/(2*N) + (S-1+parity)*PI/N);
    w1 = 2*PI*fc;
  };
};

//-low and highpass

lowpassfreq  	= nentry("low_freq[name:low freq]", 5000, 20, 12000, 10);
highpassfreq 	= nentry("high_freq[name:high freq]", 130, 20, 7040, 10);
switch       	= checkbox("on_off[name:low highpass]");
passo 		 	= +(anti_denormal_ac) : lowpassN(1,lowpassfreq) : highpassN(1,highpassfreq);
pass 		 	= hgroup("lhp", bypass(switch, passo));

process 		=  pass  : sbp ;
