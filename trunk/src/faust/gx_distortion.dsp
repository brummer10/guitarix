declare name 		"Multi Band Distortion";
declare shortname       "Distortion";
declare category        "Distortion";
declare groups "resonator[Distortion resonator]";
declare gladefile       "gx_distortion_ui.glade";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("stdfaust.lib");
import("guitarix.lib");

F = nentry("split_low_freq[name:Split Lo]", 250, 20, 600, 10);
F1 = nentry("split_middle_freq[name:Split Mid]", 650, 600, 1250, 10);
F2 = nentry("split_high_freq[name:Split Hi]", 1250, 1250, 12000, 10);

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

//----------distortion---------

//-distortion
drivelevel      = vslider("level[name:Level]", 0.0, 0, 0.5, 0.01);
drivegain1      = vslider("gain[name:Gain]", 2, -10, 10, 0.1)-10 : ba.db2linear : smoothi(0.999);
low_gain      	= vslider("low_gain[name:Lo]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
high_gain      	= vslider("high_gain[name:Hi]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
middle_gain_l     = vslider("middle_l_gain[name:LoMid]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
middle_gain_h     = vslider("middle_h_gain[name:HiMid]", 10, -10, 20, 0.1)-10 : ba.db2linear : smoothi(0.999);
drive			= vslider("drive[name:Drive]", 0.64, 0, 1, 0.01);
drive1			= vslider("low_drive[name:Lo]", 1, 0, 1, 0.01)*drive;
drive2			= vslider("high_drive[name:Hi]", 1, 0, 1, 0.01)*drive;
drive3			= vslider("middle_l_drive[name:LoMid]", 1, 0, 1, 0.01)*drive;
drive4			= vslider("middle_h_drive[name:HiMid]", 1, 0, 1, 0.01)*drive;
distortion1 	=  _:ef.cubicnl(drive1,drivelevel): *(low_gain); 
distortion2 	=  _:ef.cubicnl(drive2,drivelevel) : *(high_gain);
distortion3 	=  _:ef.cubicnl(drive3,drivelevel) : *(middle_gain_l);
distortion4 	=  _:ef.cubicnl(drive4,drivelevel) : *(middle_gain_h);
distortion	= fi.lowpass(2,15000.0): fi.highpass(1,31.0)  : filterbankN((F,(F1,F2))) : distortion2,distortion4 ,distortion3,distortion1 :>fi.lowpass(1,6531.0);

//-resonator
resonator 		= (+ <: (de.delay(4096, d-1) + de.delay(4096, d)) / 2) ~ *(1.0-a)
with {
  d = vslider("vibrato[name:Vibrato]", 1, 0, 1, 0.01);
  a = vslider("trigger[name:Trigger]", 0.12, 0, 1, 0.01);
};

switch2       	= checkbox("resonator.on_off[name:resonat]");
//reso 			= hgroup("resonator", bypass(switch2, resonator));
moving_filter(x) = (x+x'+x'')/3;

wet = vslider("wet_dry[name:Wet/Dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;

process_dist 		= bypass(switch2, resonator) : +(anti_denormal_ac) : distortion : *(drivegain1) ;

process = _<:*(dry),(*(wet): process_dist):>_;
