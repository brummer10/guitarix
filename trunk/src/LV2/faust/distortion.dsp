//declare name 		"distortion";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("stdfaust.lib");
import("guitarix.lib");

F = nentry("split_low_freq", 250, 20, 600, 10);
F1 = nentry("split_middle_freq", 650, 600, 1250, 10);
F2 = nentry("split_high_freq", 1250, 1250, 12000, 10);

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

tf2N(b0,b1,b2,a1,a2) = ma.sub ~ conv2(a1,a2) : conv3(b0,b1,b2)
with {
  conv3(k0,k1,k2,x)     = k0*x + k1*x' + k2*x'';
  conv2(k0,k1,x)        = k0*x + k1*x';
  ma.sub(x,y)              = y-x;
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

/**********************************************************************
*** end for backward compatibility from 0.9.27 to
*** 0.9.24 , it could removed when switch completly to > 0.9.27
***********************************************************************/

//----------distortion---------

//-speaker emulation
sbp1    		= vslider("low_freq[name:low freq][tooltip:low-freq cutoff Hz]",130,20,1000,10);
sbp2    		= vslider("high_freq[name:high freq][tooltip:high-freq cutoff Hz]",5000,1000,12000,10);
switch1 		= checkbox("on_off[name:low highcutoff]");
sbp 			= hgroup("low_highcutoff", bypass(switch1, +(anti_denormal_ac) : ef.speakerbp(sbp1,sbp2)));

//-low and fi.highpass
lowpassfreq  	= nentry("low_freq[name:low freq]", 5000, 20, 12000, 10);
highpassfreq 	= nentry("high_freq[name:high freq]", 130, 20, 7040, 10);
switch       	= checkbox("on_off[name:low fi.highpass]");
passo 		 	= +(anti_denormal_ac) : lowpassN(1,lowpassfreq) : highpassN(1,highpassfreq);
pass 		 	= hgroup("low_highpass", bypass(switch, passo));

//-distortion
drivelevel      = vslider("level", 0.01, 0, 0.5, 0.01);
drivegain1      = vslider("gain", 2, -10, 10, 0.1)-10 : ba.db2linear : smoothi(0.999);
low_gain      	= vslider("low_gain", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
high_gain      	= vslider("high_gain", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
middle_gain_l     = vslider("middle_l_gain", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
middle_gain_h     = vslider("middle_h_gain", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
drive			= vslider("drive", 0.64, 0, 1, 0.01);
drive1			= vslider("low_drive", 1, 0, 1, 0.01)*drive;
drive2			= vslider("high_drive", 1, 0, 1, 0.01)*drive;
drive3			= vslider("middle_l_drive", 1, 0, 1, 0.01)*drive;
drive4			= vslider("middle_h_drive", 1, 0, 1, 0.01)*drive;
distortion1 	=  _:ef.cubicnl(drive1,drivelevel): *(low_gain); 
distortion2 	=  _:ef.cubicnl(drive2,drivelevel) : *(high_gain);
distortion3 	=  _:ef.cubicnl(drive3,drivelevel) : *(middle_gain_l);
distortion4 	=  _:ef.cubicnl(drive4,drivelevel) : *(middle_gain_h);
distortion	= _ : analyzerN((F,(F1,F2))) : distortion2,distortion4 ,distortion3,distortion1 :>_;

//-resonator
resonator 		= (+ <: (de.delay(4096, d-1) + de.delay(4096, d)) / 2) ~ *(1.0-a)
with {
  d = vslider("vibrato", 1, 0, 1, 0.01);
  a = vslider("trigger", 0.12, 0, 1, 0.01);
};

switch2       	= checkbox("resonator.on_off[name:resonat]");
//reso 			= hgroup("resonator", bypass(switch2, resonator));

hs 				= component("HighShelf.dsp").hs;
process 		= bypass(switch2, resonator) : +(anti_denormal_ac) : pass  : sbp : hs : distortion : *(drivegain1) : hs : sbp;
