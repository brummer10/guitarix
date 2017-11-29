import("stdfaust.lib");

// Port from SuperCollider (SC) to Faust of SynthDef \SOStom in 
// <SuperCollider>/examples/demonstrations/DrumSynths.scd
// e.g., /usr/local/share/SuperCollider/examples/demonstrations/DrumSynths.scd
// based on a Sound-on-Sound 'synth secrets' tutorial:
// http://www.soundonsound.com/sos/Mar02/articles/synthsecrets0302.asp

// SOStom -------
// http://www.soundonsound.com/sos/Mar02/articles/synthsecrets0302.asp

//https://github.com/josmithiii/faust-jos/tree/master/percussion

gate = checkbox("gate [nomidi:no][alias]");
trigger = gate > gate';

ampdb  = vslider("Gainf [nomidi:no][alias]",-20,-60,40,0.1);
amp = ampdb : si.smooth(0.999) : ba.db2linear;

freq = vslider("[2] freq [nomidi:no][alias]", 90, 90, 150, 1);
//freq = 90;
// freq = 128;
// freq = 150;
sustain = 0.4;
drum_timbre = 1.0;
drum_mode_level = 0.25;

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
sinosc0(freq) = os.oscrs(freq); // SinOsc at phase fi.zero
pmosc(carfreq,modfreq,index) = os.oscrs(carfreq + (index*modfreq)
			     * os.oscrs(modfreq));

drum_mode_env = perc(0.005, sustain, trigger);
drum_mode_sin_1 = sinosc0(freq*0.8) * drum_mode_env * 0.5;
drum_mode_sin_2 = sinosc0(freq) * drum_mode_env * 0.5;
drum_mode_pmosc = pmosc(os.saw2(freq*0.9), freq*0.85, drum_timbre/1.3)
		  * drum_mode_env * 5;
drum_mode_mix = (drum_mode_sin_1 + drum_mode_sin_2 + drum_mode_pmosc)
	      * drum_mode_level;
stick_env = perc(0.005, 0.01, trigger) * 3;
tom_mix = (drum_mode_mix + stick_env) * 2 * amp;

process = tom_mix;
