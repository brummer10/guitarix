declare id   "phaser";
declare name "Phaser";
declare category "Modulation";

//phaser taken from effect.lib 
// by Julius O. Smith III

import("stdfaust.lib");

vibrato_mono(sections,phase01,fb,width,frqmin,fratio,frqmax,speed) = 
 (+ : seq(i,sections,ap2p(R,th(i)))) ~ *(fb)
with {
    // fi.tf2 = component("filter.lib").fi.tf2;
     // second-order resonant digital allpass given fi.pole radius and angle:
     ap2p(R,th) = fi.tf2(a2,a1,1,a1,a2) with {
       a2 = R^2;
       a1 = -2*R*cos(th);
     };
    // ma.SR = component("music.lib").ma.SR;
     R = exp(-pi*width/ma.SR);
     cososc = os.oscrc;
     sinosc = os.oscrs;
     osc1 = cososc(speed) * phase01 + sinosc(speed) * (1-phase01);
     lfo = (1-osc1)/2; // in [0,1]
     pi = 4*atan(1);
     thmin = 2*pi*frqmin/ma.SR;
     thmax = 2*pi*frqmax/ma.SR;
     th1 = thmin + (thmax-thmin)*lfo;
     th(i) = (fratio^(i+1))*th1;
};

phaser_mono(Notches,phase01,width,frqmin,fratio,frqmax,speed,depth,fb,invert) = 
      _ <: *(g1) + g2mi*vibrato_mono(Notches,phase01,fb,width,frqmin,fratio,frqmax,speed)
with {               // depth=0 => direct-signal only
     g1 = 1-depth/2; // depth=1 => phaser mode (equal sum of direct and allpass-pm.chain)
     g2 = depth/2;   // depth=2 => vibrato mode (allpass-pm.chain signal only)
     g2mi = select2(invert,g2,-g2); // inversion negates the allpass-pm.chain signal
};
  
phaser_stereo(Notches,width,frqmin,fratio,frqmax,speed,depth,fb,invert)
   = phaser_mono(Notches,0,width,frqmin,fratio,frqmax,speed,depth,fb,invert),
     phaser_mono(Notches,1,width,frqmin,fratio,frqmax,speed,depth,fb,invert);

phaser_stereogx = *(level),*(level) : phaser_stereo(Notches,width,frqmin,fratio,frqmax,freq,mdepth,fb,invert)
with {
  Notches = 4;
  //freq  = hslider("Speed [unit:Hz] ", 0.5, 0, 10, 0.01);
  freq     = hslider("lfobpm[name:Speed (bpm)][tooltip:Speed in Beats per Minute]",30,24,360,1)/60;
  
  depth	 = hslider("depth[name:Depth]", 1, 0, 1, 0.01);
  fb	 = hslider("feedback gain[name:Feedback]", 0, 0, 1, 0.01);
  width  = hslider("Notch width [name:Width][unit:Hz]", 1000, 10, 5000, 1);
  vibr   = checkbox("VibratoMode[enum:direct | vibrato]");
  frqmin = hslider("MinNotch1Freq [name:Freq][unit:Hz] ", 100, 20, 5000, 1);
  frqmax = hslider("MaxNotch1Freq [name:Max Freq][unit:Hz] ", 800, 20, 10000, 1) : max(frqmin);
  fratio = hslider("NotchFreq[name:Min Freq][unit:Hz]", 1.5, 1.1, 4, 0.01);
  mdepth = select2(vibr,depth,2); 
  
  invert   = checkbox("invert[enum:linear|invert]");
  level	 = hslider("level [name:Level][unit:dB]", 0, -60, 10, 0.1) : ba.db2linear;
  
};

process = phaser_stereogx;
