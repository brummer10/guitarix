declare id   "phaser";
declare name "Phaser";
declare category "Modulation";

//phaser taken from effect.lib 
// by Julius O. Smith III


import("effect.lib");
//import("oscillator.lib");

vibrato_mono(sections,phase01,fb,width,frqmin,fratio,frqmax,speed) = 
 (+ : seq(i,sections,ap2p(R,th(i)))) ~ *(fb)
with {
     tf2 = component("filter.lib").tf2;
     // second-order resonant digital allpass given pole radius and angle:
     ap2p(R,th) = tf2(a2,a1,1,a1,a2) with {
       a2 = R^2;
       a1 = -2*R*cos(th);
     };
     SR = component("music.lib").SR;
     R = exp(-pi*width/SR);
     cososc = component("oscillator.lib").oscrc;
     sinosc = component("oscillator.lib").oscrs;
     osc = cososc(speed) * phase01 + sinosc(speed) * (1-phase01);
     lfo = (1-osc)/2; // in [0,1]
     pi = 4*atan(1);
     thmin = 2*pi*frqmin/SR;
     thmax = 2*pi*frqmax/SR;
     th1 = thmin + (thmax-thmin)*lfo;
     th(i) = (fratio^(i+1))*th1;
};

phaser_mono(Notches,phase01,width,frqmin,fratio,frqmax,speed,depth,fb,invert) = 
      _ <: *(g1) + g2mi*vibrato_mono(Notches,phase01,fb,width,frqmin,fratio,frqmax,speed)
with {               // depth=0 => direct-signal only
     g1 = 1-depth/2; // depth=1 => phaser mode (equal sum of direct and allpass-chain)
     g2 = depth/2;   // depth=2 => vibrato mode (allpass-chain signal only)
     g2mi = select2(invert,g2,-g2); // inversion negates the allpass-chain signal
};
  
phaser_stereo(Notches,width,frqmin,fratio,frqmax,speed,depth,fb,invert)
   = phaser_mono(Notches,0,width,frqmin,fratio,frqmax,speed,depth,fb,invert),
     phaser_mono(Notches,1,width,frqmin,fratio,frqmax,speed,depth,fb,invert);

phaser_stereogx = *(level),*(level) : phaser_stereo(Notches,width,frqmin,fratio,frqmax,freq,mdepth,fb,invert)
with {
  Notches = 4;
  freq  = hslider("Speed [unit:Hz] ", 0.5, 0, 10, 0.01);
  
  depth	 = hslider("depth", 1, 0, 1, 0.01);
  fb	 = hslider("feedback gain", 0, 0, 1, 0.01);
  width  = hslider("Notch width [unit:Hz]", 1000, 10, 5000, 1);
  vibr   = checkbox("VibratoMode[enum:direct | vibrato]");
  frqmin = hslider("MinNotch1Freq [unit:Hz] ", 100, 20, 5000, 1);
  frqmax = hslider("MaxNotch1Freq [unit:Hz] ", 800, 20, 10000, 1) : max(frqmin);
  fratio = hslider("NotchFreq", 1.5, 1.1, 4, 0.01);
  mdepth = select2(vibr,depth,2); 
  
  invert   = checkbox("invert[enum:linear|invert]");
  level	 = hslider("level [unit:dB]", 0, -60, 10, 0.1) : db2linear;
  
};

process = phaser_stereogx;
