import("stdfaust.lib");

// Port from SuperCollider to Faust of snare_stein in
// SynthDefPool by Dan Stowell, which in turn was based
// on a Sound-on-Sound 'synth secrets' tutorial

//https://github.com/josmithiii/faust-jos/tree/master/percussion

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

perc(att,rel,trigger) = adsr(att,0.001,1.0,rel,envgate(att,trigger));
sinosc0(freq) = os.oscrs(freq); // SinOsc at phase fi.zero

line(start,end,dur,trigger) = trigger : release(int(dur*float(ma.SR))) 
		    : *(start-end)+end;
		    
lpf(freq) = fi.lowpass(3,freq);
hpf(freq) = fi.highpass(3,freq);

gate = checkbox("gate [nomidi:no][alias]");
trigger = (gate>gate');

ampdb  = vslider("Gain [tooltip: Volume level in decibels] ",-20,-60,40,0.1);
amp = ampdb : si.smooth(0.999) : ba.db2linear;

lpnoise = no.noise : lpf(7040);
hpnoise = no.noise : hpf(523);
att = 0.0005; // attack-time in seconds

snare = (0.25 + sinosc0(330)) * perc(att,0.055,trigger)
      + (0.25 + sinosc0(185)) * perc(att,0.075,trigger)
      + 0.2 * lpnoise * perc(att,0.2,trigger)
      + 0.2 * hpnoise * perc(att,0.183,trigger);

process = snare * amp;
