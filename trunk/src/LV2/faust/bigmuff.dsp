// Big Muff tone model
//

import("stdfaust.lib");

// Is basically 2 filters mixed together with a knob.

//Top filter is   39K( R1 ) -> 0.01u( C2 ) to ground - 408Hz fi.lowpass
// Bottom filter is 3900pF( C1 )  -> 22k( R2 ) to ground - 1855.9Hz

// Seems OK but does not create the 1K dip seen on real thing
// assume that the tone pot needs better model as must intercat with the
// other 2 filters such that at mid point both filters are still working 
// There shgould be interaction between the pot ( R3 ) and both of thge other RC filters
// Also as pot changes so do cutoff frequencies
// Reduction moves both frequencies up by roughly 400Hz max
// Increase moves both down by around same
// So need +-400Hz calculated by curent tone position
// pot = 0  -> +400
// pot = 1 -> -400

bigmuff = _<: filter1,filter2:>_   with {
	tone = vslider("tone[style:knob]",0.5,0,1,0.01);
	filter1  = fi.highpass( 1, 1856):*(tone)  ;
	filter2 = fi.lowpass( 1, 408 ) :*(1-tone ) ;
};
process = bigmuff ;
