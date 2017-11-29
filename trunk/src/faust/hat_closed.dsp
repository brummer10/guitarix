import("stdfaust.lib");

// Port from SuperCollider (SC) to Faust of SynthDef \SOShat in 
// <SuperCollider>/examples/demonstrations/DrumSynths.scd
// e.g., /usr/local/share/SuperCollider/examples/demonstrations/DrumSynths.scd
// on Linux
// based on a Sound-on-Sound 'synth secrets' tutorial:
// http://www.soundonsound.com/sos/Jun02/articles/synthsecrets0602.asp

//https://github.com/josmithiii/faust-jos/tree/master/percussion

pi = ma.PI;

decay(n,x) = x - (x>0.0)/n;
release(n) = + ~ decay(n);
envgate(dur,trigger) = trigger : release(int(dur*float(ma.SR))) : >(0.0);

adsr(a,d,s,r,t) = env ~ (_,_) : (!,_) // the 2 'state' signals are fed back
with {
    env (p2,y) =
        (t>0) & (p2|(y>=1)),          // p2 = decay-sustain phase
        (y + p1*u - (p2&(y>s))*v*y - p3*w*y)	// y  = envelop signal
	*((p3==0)|(y>=eps)) // cut off tails to prevent denormals
    with {
		p1 = (p2==0) & (t>0) & (y<1);         // p1 = attack phase
		p3 = (t<=0) & (y>0);                  // p3 = release phase
		// #samples in attack, decay, release, must be >0
		na = ma.SR*a+(a==0.0); nd = ma.SR*d+(d==0.0); nr = ma.SR*r+(r==0.0);
		// correct zero sustain level
		z = s+(s==0.0)*ba.db2linear(-60);
		// attack, decay and (-60dB) release rates
		u = 1/na; v = 1-pow(z, 1/nd); w = 1-1/pow(z*ba.db2linear(60), 1/nr);
		// values below this threshold are considered zero in the release phase
		eps = ba.db2linear(-120);
    };
};

perc(att,rel,trigger) = adsr(att,0,1.0,rel,envgate(att,trigger));
pmosc(carfreq,modfreq,index) = os.oscrs(carfreq + (index*modfreq)
			     * os.oscrs(modfreq));

line(start,end,dur,trigger) = trigger : release(int(dur*float(ma.SR))) 
		    : *(start-end)+end;
		    
lpf(freq) = fi.lowpass(3,freq);
hpf(freq) = fi.highpass(3,freq);

bpf(freq, rq) = fi.tf2(1.0,0,-1.0,-2.0*R*cos(theta),R^2) with {
  theta = 2.0*pi*freq/ma.SR;
  R = -pi*freq*rq/ma.SR;
};
pulse0p5(freq) = os.square(freq); // phase 0, duty cycle 0.5

gate = checkbox("gate [nomidi:no][alias]");

ampdb  = vslider("Gain [tooltip: Volume level in decibels]",-20,-60,40,0.1);
amp = ampdb : si.smooth(0.999) : ba.db2linear;

freq = 1600.0; 
sustain = 0.01; 

//freq = 6000; // orig value
// sustain = 0.1; // orig value

trigger = gate > gate';

root_cymbal_square = pulse0p5(freq);
root_cymbal = root_cymbal_square <: 
    pmosc(freq*1.34, 310.0/1.3) + 
    pmosc(freq*2.405, 26.0/0.5) +
    pmosc(freq*3.09, 11.0/3.4) + 
    pmosc(freq*1.309, 0.72772);
initial_bpf_contour = line(15000, 9000, 0.1, trigger);
initial_env = perc(0.005, 0.1, trigger);
initial_bpf = root_cymbal : bpf(initial_bpf_contour,1.0) * initial_env;

body_env = sqrt(perc(0.005, sustain, trigger)); 
body_hpf = root_cymbal : hpf(line(9000, 12000, sustain, trigger)) 
	 * body_env;
cymbal_mix = (initial_bpf + body_hpf) * amp;

process = cymbal_mix;
