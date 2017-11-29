import("stdfaust.lib");

// Port from SuperCollider (SC) to Faust of SOSkick in 
// <SuperCollider>/examples/demonstrations/DrumSynths.scd
// based on a Sound-on-Sound 'synth secrets' tutorial:
// http://www.soundonsound.com/sos/jan02/articles/synthsecrets0102.asp

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

perc(att,rel,trigger) = adsr(att,0,1.0,rel,envgate(att,trigger));
pmosc(carfreq,modfreq,index) = os.oscrs(carfreq + (index*modfreq)
			     * os.oscrs(modfreq));

line(start,end,dur,trigger) = trigger : release(int(dur*float(ma.SR))) 
		    : *(start-end)+end;
		    
lpf(freq) = fi.lowpass(3,freq);
hpf(freq) = fi.highpass(3,freq);

gate = checkbox(" gate [nomidi:no][alias]");
ampdb  = vslider("Gain [tooltip: Volume level in decibels]",-20,-60,40,0.1);
amp = ampdb : si.smooth(0.999) : ba.db2linear;
freq = 50;
mod_freq = 5.0;
mod_index = 5.0;
sustain = 0.4;
beater_noise_level = 0.03;

trigger = gate>gate';
pitch_contour = line(freq*2, freq, 0.02, trigger);
drum_osc = pmosc(pitch_contour, mod_freq, mod_index/1.3);
drum_lpf = drum_osc : lpf(1000);
drum_env = drum_lpf * perc(0.005,sustain,trigger);

beater_source = no.noise * beater_noise_level;
beater_hpf = beater_source : hpf(500);
lpf_cutoff_contour = line(6000, 500, 0.03, trigger);
beater_lpf = beater_hpf : lpf(lpf_cutoff_contour);
beater_env = beater_lpf * perc(0.01, 1.0, trigger);
kick_mix = (drum_env + beater_env) * 2 * amp;

process = kick_mix;
