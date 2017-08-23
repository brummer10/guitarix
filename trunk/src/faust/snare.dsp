ml = library("music.lib");
fl = library("filter.lib");
ol = library("oscillator.lib");

// Port from SuperCollider to Faust of snare_stein in
// SynthDefPool by Dan Stowell, which in turn was based
// on a Sound-on-Sound 'synth secrets' tutorial

//https://github.com/josmithiii/faust-jos/tree/master/percussion

decay(n,x) = x - (x>0.0)/n;
release(n) = + ~ decay(n);
envgate(dur,trigger) = trigger : release(int(dur*float(ml.SR))) : >(0.0);

perc(att,rel,trigger) = ml.adsr(att,0,1.0,rel,envgate(att,trigger));
sinosc0(freq) = ol.oscrs(freq); // SinOsc at phase zero

line(start,end,dur,trigger) = trigger : release(int(dur*float(ml.SR))) 
		    : *(start-end)+end;
		    
lpf(freq) = fl.lowpass(3,freq);
hpf(freq) = fl.highpass(3,freq);

gate = checkbox("gate [nomidi:no][alias]");
trigger = (gate>gate');

ampdb  = vslider("Gain [tooltip: Volume level in decibels] ",-20,-60,40,0.1);
amp = ampdb : fl.smooth(0.999) : ml.db2linear;

lpnoise = ml.noise : lpf(7040);
hpnoise = ml.noise : hpf(523);
att = 0.0005; // attack-time in seconds

snare = (0.25 + sinosc0(330)) * perc(att,0.055,trigger)
      + (0.25 + sinosc0(185)) * perc(att,0.075,trigger)
      + 0.2 * lpnoise * perc(att,0.2,trigger)
      + 0.2 * hpnoise * perc(att,0.183,trigger);

process = snare * amp;

