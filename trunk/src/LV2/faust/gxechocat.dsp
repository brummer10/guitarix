declare name "Tape Delay";
declare category "Echo / Delay";

import("stdfaust.lib");
import("guitarix.lib");
import("redeye.lib");

/*
HEAD SPACING

I have lold Selmer unit where playback heads are 1.5 inches apart
and record head is 1.8 inches from last playback so :

	record - play4 - play 3 - play 2 - play 1

		1.8  - 1.5 - 1.5 - 1.5 - 1.5
 
Se we have record -1.8inches - head1, 2.3 to head2, 3.8 to head3 5.3 to head 4 !
 Or	at 15ips	head1 120ms head2 220ms head3 320ms head4 420ms

According to what I have read the heads are not parallel but output from each one is fed into next ??? What ??? Also max de.delay from one head is 425ms
Apparently originsl units has 23 inch tapes!
  
Actual topology
In -> stage1 -> pentode driver for record head ->play heads -> 2stage valve amp ->mixer->out and feedback to pentode
Sounds OK maybe too much bandwidth loss try cleaner path
Look ay adding soft clip before machine to simulate saturation 
Frequency response of tape in copicat would be poor due to design and use
Tape usually has steep low end drop with a hump and not quite so steep high drop, maybe as for guitar we can lower this but would guess that should start around
	40 - 80Hz steep fi.highpass with possible hump ( ? resonant filter )
	5- 6k fi.lowpass
Am concerned that as each valve stage already has same lowapss filter that this
may have same effect as in real amp of creating a resonance an will try same solution : stagger filters and identify dominant one ( biggest effect ) and slug it or drastically reduce it.
*/

// So we need multiple de.delay heads
// Each head can be bypassed or moved to alter de.delay time
// so tape speed in inches per second
// distance from record head in inches
// thus we get de.delay in milliseconds
//speed = 7.5 ;

bpm = hgroup( "Echo", vslider("BPM[style:knob]", 120, 24, 360, 0.1)) ;

// The wow should be preset by experiment...
// Lets introduce just a little
sine(freq) = (os.oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
freq= 4 ; // 4Hz
depth = 0.005 ;	// Play with this
wow =  sine( freq) * depth ;
speed = ( 72/(2*bpm))  ;
tapespeed = hgroup( "Tape Control",speed + wow ); 

LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
s = 0.993;

echo = hgroup( "Echo", vslider("Swell[style:knob]", 0, 0, 1, 0.01)): LogPot(1):si.smooth(s):*(0.25) ;
feedback = hgroup( "Echo", vslider("Sustain[style:knob]", 0, 0.0, 1.0, 0.01)):LogPot(1):si.smooth(s):*(0.25);

// Play with delays to get following ranges 
// 83.33ms => 1.25s on head1 
// 166.6ms => 2.5s on head1 
// 250ms => 3.75s on head1 
dtime1 = ma.SR*( 30/bpm) ;
dtime2 = ma.SR*( 60/ bpm) ;
dtime3 = ma.SR*( 90/bpm ) ;
dtime4 = ma.SR*( 240/bpm ) ;

head1 = de.sdelay(N, interp, dtime1):*(checkbox("Head1")) with {
	interp = ma.SR/10.0; // 100*SER/1000
 	N = int( 2^19 ) ;
};
head2 = de.sdelay(N, interp, dtime2):*(checkbox("Head2")) with {
	interp = 100*ma.SR/1000.0;
 	N = int( 2^19 ) ;
};
head3 = de.sdelay(N, interp, dtime3):*(checkbox("Head3")) with {
	interp = 100*ma.SR/1000.0;
 	N = int( 2^19 ) ;
};
head4 = de.sdelay(N, interp, dtime4):*(checkbox("Head4")) with {
	interp = 100*ma.SR/1000.0;
 	N = int( 2^19 ) ;
};


input = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) : copicat1clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


//    Input = vslider("Input[name:Input]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(3) : si.smooth(s);
    Input = vslider("AUDIO_IN[name:Input]", 0.5, 0, 1, 0.01) : si.smooth(s);

    b0 = Input*fs*(-2.06740841499587e-8*fs - 5.51308910665569e-7);

    b1 = 4.13481682999174e-8*Input*pow(fs,2);

    b2 = Input*fs*(-2.06740841499587e-8*fs + 5.51308910665569e-7);

    a0 = Input*(Input*fs*(-7.83789728824443e-11*fs - 3.13458049067171e-9) + fs*(8.32844278169955e-11*fs + 5.0418669893366e-9) + 6.26916098134342e-8) + fs*(4.11425073415965e-10*fs + 2.49068229273233e-8) + 3.09696552478371e-7;

    a1 = Input*(1.56757945764889e-10*Input*pow(fs,2) - 1.66568855633991e-10*pow(fs,2) + 1.25383219626868e-7) - 8.22850146831931e-10*pow(fs,2) + 6.19393104956741e-7;

    a2 = Input*(Input*fs*(-7.83789728824443e-11*fs + 3.13458049067171e-9) + fs*(8.32844278169955e-11*fs - 5.0418669893366e-9) + 6.26916098134342e-8) + fs*(4.11425073415965e-10*fs - 2.49068229273233e-8) + 3.09696552478371e-7;
};

copicat1clip = _<: ba.if(signbit(_), copicat1_neg_clip, copicat1_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    copicat1_clip = ffunction(float copicat1clip(float), "copicat1_table.h", "");

    copicat1_neg_clip = ffunction(float copicat1_negclip(float), "copicat1_neg_table.h", "");

};
record = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0)) : copicatrecord_2clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(-1.23938408071082e-8*fs - 7.13052376187718e-7) - 9.98795811595446e-6;

    b1 = fs*(1.23938408071082e-8*fs - 7.13052376187718e-7) - 2.99638743478634e-5;

    b2 = fs*(1.23938408071082e-8*fs + 7.13052376187718e-7) - 2.99638743478634e-5;

    b3 = fs*(-1.23938408071082e-8*fs + 7.13052376187718e-7) - 9.98795811595446e-6;

    a0 = fs*(fs*(6.73029102377671e-15*fs + 1.10493997854221e-10) + 2.30183843147656e-8) + 6.01595252726883e-7;

    a1 = fs*(fs*(-2.01908730713301e-14*fs - 1.10493997854221e-10) + 2.30183843147656e-8) + 1.80478575818065e-6;

    a2 = fs*(fs*(2.01908730713301e-14*fs - 1.10493997854221e-10) - 2.30183843147656e-8) + 1.80478575818065e-6;

    a3 = fs*(fs*(-6.73029102377671e-15*fs + 1.10493997854221e-10) - 2.30183843147656e-8) + 6.01595252726883e-7;
};

copicatrecord_2clip = _<: ba.if(signbit(_), copicatrecord_2_neg_clip, copicatrecord_2_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    copicatrecord_2_clip = ffunction(float copicatrecord_2clip(float), "copicatrecord_2_table.h", "");

    copicatrecord_2_neg_clip = ffunction(float copicatrecord_2_negclip(float), "copicatrecord_2_neg_table.h", "");

};
replay1 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) : copicatreplay1clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(-2.16461324600193e-8*fs - 1.31188681575873e-7);

    b1 = 4.32922649200386e-8*pow(fs,2);

    b2 = fs*(-2.16461324600193e-8*fs + 1.31188681575873e-7);

    a0 = fs*(4.33785780482415e-10*fs + 1.16144315716444e-8) + 6.90530766455131e-8;

    a1 = -8.6757156096483e-10*pow(fs,2) + 1.38106153291026e-7;

    a2 = fs*(4.33785780482415e-10*fs - 1.16144315716444e-8) + 6.90530766455131e-8;
};

copicatreplay1clip = _<: ba.if(signbit(_), copicatreplay1_neg_clip, copicatreplay1_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    copicatreplay1_clip = ffunction(float copicatreplay1clip(float), "copicatreplay1_table.h", "");

    copicatreplay1_neg_clip = ffunction(float copicatreplay1_negclip(float), "copicatreplay1_neg_table.h", "");

};
replay2 =  pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) : copicatreplay2clip with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;


    b0 = fs*(-1.02325156488485e-9*fs - 1.05707806289759e-8);

    b1 = 2.0465031297697e-9*pow(fs,2);

    b2 = fs*(-1.02325156488485e-9*fs + 1.05707806289759e-8);

    a0 = fs*(4.3361242466424e-10*fs + 1.99329936161353e-8) + 1.89880017035189e-7;

    a1 = -8.6722484932848e-10*pow(fs,2) + 3.79760034070379e-7;

    a2 = fs*(4.3361242466424e-10*fs - 1.99329936161353e-8) + 1.89880017035189e-7;
};


copicatreplay2clip = _<: ba.if(signbit(_), copicatreplay2_neg_clip, copicatreplay2_clip) :>_ with {

    signbit = ffunction(int signbit(float), "math.h", "");

    copicatreplay2_clip = ffunction(float copicatreplay2clip(float), "copicatreplay2_table.h", "");

    copicatreplay2_neg_clip = ffunction(float copicatreplay2_negclip(float), "copicatreplay2_neg_table.h", "");

};


machine = record:vgroup( "Tape Heads", fi.highpass( 4, 40 )<:head1,head2,head3:>fi.lowpass( 1, 6500 ):fi.dcblocker ):replay1:replay2;

// May need to look at levels here
fbloop = fi.lowpass( 1, 7500 ):*(feedback):fi.highpass( 1, 150 )  ;

Output = vslider("Output[name:Output]", 1.0, 0.0, 2.0, 0.01) : LogPot(3) : si.smooth(s);

amp = input<:_,((+:_<:machine :>_)~fbloop:*(echo)):>*(Output) ;

freq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));
process    = freq_split: ( amp , amp , amp, amp, amp) :>_;
