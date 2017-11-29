// Tape compression/saturation and frequency response
// Add wow & flutter and we have tape emulation - needsa to modulate the frequency
// which means basically vibrato
// So far so good - tubes may not be needed
// Need to work out better levels of saturation as current range too distorted
// wow at 1% is 0.15 inchs per second > 10ms * ma.SR/1000
// Which would indicate we need a de.delay time of 10ms to allow +-10ms modulation
// and thus delaytime = (10 + modulation ) * ma.SR/1000;

import("stdfaust.lib");
import("guitarix.lib");

import("redeye.lib");

// ((( lfo + 1 ) *5)+5) from vibrato
//wow = sine( freq )* depth with{
wow =  de.sdelay(N, interp, delaytime) with{
	freq =  hgroup( "Wow Control",vslider("wowfreq[style:knob]",0.0,0.0,4.0,0.1) );
	depth =  hgroup( "Wow Control",vslider("wowdepth[style:knob]",0.0,0.0,0.03,0.001) );
	sine(freq) = (os.oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy what is range of this
	modulation = (( sine( freq ) + 1 ) * 5)* depth ; // This should give number between 0-10 ms ??
	delaytime = modulation * ma.SR/1000;
	N 	= int(2^12);  
	interp = 100.0 *ma.SR/1000.0;
};

flutter = de.sdelay(N, interp, modulation*ma.SR/1000.0) with{
	freq =  hgroup( "Flutter",vslider("flutterfreq[style:knob]",4,4,60,0.1) );
	depth =  hgroup( "Flutter",vslider("flutterdepth[style:knob]",0.0,0.0,0.03,0.001) );
	sine(freq) = (os.oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
	modulation = ((( sine( freq ) + 1 ) *5))* depth ;
	N 	= int(2^12);  
	interp = 100.0 *ma.SR/1000.0;
};

// Each tape recorde rhas its own frequency response 
// Revox A77 
// Hump in bass around 50Hz around 2-3dB
// Gentle slope from 100Hz down to 10K about -3dB
// fairly steep rolloff after that
// Can it be done with fi.iir or fi.fir?
 
// Try to boost highs 1st then cut after to get frequency dependent compressor
// These filters very subtly boost and cut highs 
// So should be that the highs are more compressed - which seems to sound better
// may be look into better filter curve
tapesaturate = filter1:sigmoid:filter2:fi.lowpass( 3, 15000):fi.highpass(1,25) with {
//tapesaturate = sigmoid:fi.lowpass( 3, 15000):fi.highpass(1,25) with {
  sigmoid(x) = 2.0/( 1.0 + exp(-5.0*x)) - 1.0;

	filter1 = fi.iir((1.0, 0.0, 0.0),
                    (0.3 , 0.0 ,0.0)); // Boost higher frequencies
	filter2 = fi.iir((1.0, 0.0, 0.0),
                    (-0.3 , 0.0 ,0.0));	// Cut higher frequencies

};
// We can incorporate a speed switch ( 7.5 ips / 15 ips )
// This would then select an alternative response curve
// 7.5 ips Revox has no bass hump and cuts treble off even more sharply
// In theory the frequency of no.noise would also double
speed = checkbox("speed"); 

taperesponse = _<:select2( tapetype, taperesponse1, taperesponse2 ):tapehiss with{

	// This is loosely based on Revox B77
	tapetype = vslider("tapetype[style:knob]", 0, 0, 1,1);
	taperesponse1 = select2( speed ,taperesponse1b,taperesponse1a);
	// Taperesponses
	// Revoc B77
	// 7.5ips
	taperesponse1a = fi.highpass(1,25):fi.lowpass( 1, 10000 ):fi.lowpass( 2, 12500 );	
	// 15 ips
	taperesponse1b = fi.highpass(1,25):fi.peak_eq_cq(3, 50, 0.4 ):fi.lowpass( 1, 12500 ):fi.lowpass( 2, 15000 ) ;

	// Loosely based on Tascam A3340X
	taperesponse2 = select2( speed ,taperesponse2b,taperesponse2a);
	
	// TASCAM Q = 0.4 peak 9dB -- Although the ma.sub fi.lowpass wporks creates a lot of unwanted high end 
	//7.5ips
	taperesponse2a = fi.highpass(1,25):fi.peak_eq_cq(6,75,0.4):ma.sub~fi.lowpass( 1, 4500 ):fi.lowpass( 4, 10000 );
	// 15ips
	taperesponse2b = fi.highpass(1,35):fi.peak_eq_cq(6,75,0.4):ma.sub~fi.lowpass( 1, 4500 ):fi.lowpass( 4, 15000 );

	// Sort this out so level is -XXdB no.noise floor
	tapehiss = _<:_,(no.noise * level:hissfilter):>_ ;
	level = vslider("tapehiss[style:knob]", 0.0, 0.0, 1.0, 0.01):*(0.0316):si.smooth( 0.9999) ;
	scale = ( ( 1.0-speed) + 1.0 )/2.0 ;
	// Might be able to simplify this once I get to grips with IIR and fi.fir....!
	// Current value is pretty good approximation of actual tape hiss 
	hissfilter = _<:(fi.highpass(1,3000):*(0.2)),fi.lowpass( 1, 250 ):>fi.lowpass( 2, 15000*scale );

} ;

machine =  tapesaturate:taperesponse:wow:flutter;
delaystage = component( "delaystage.dsp").delaystage ;

// This is standard IEC eq maybe wrong way round as I want highs saturated more than lows
iec_in = fi.lowpass( 1, 4500 );
iec_out = ma.sub~fi.lowpass( 1, 4500 );

channel = input12au7:*(0.1):BP(iec_in:machine:iec_out):output12au7:fi.lowpass( 2, 20000);
//process = channel,channel;
