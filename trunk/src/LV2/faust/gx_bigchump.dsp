declare name "Redeye Big Chump";
declare category "Amplifier";

import("stdfaust.lib"); 
import("guitarix.lib");
import("redeye.lib");

trannie = coil1,coil2:>_ with {
	coil1 = fi.lowpass( 1, ( 8075 )  ):fi.highpass( 1, 84):*(0.98)  ;
	coil2 = fi.lowpass( 1, 8925 ):fi.highpass( 1, 76) ;
}; 

amp = bigChumpPre:bigChumpPre2:bigChumpPower:*(volume) with {
	
	// Try this as -12 -> +12 dB
	volume = vslider("Volume[2][alias][style:knob]",0.5, 0.0, 1.0,0.01) : smoothi(0.999);

	// This does not work at present may cut it out
	feedback = *(checkbox("feedback") ):fi.high_shelf( 3, 6531 ):*(-0.5);


};
freq_split = fi.filterbank(3, (86.0,210.0,1200.0,6531.0));
process    = freq_split: ( amp , amp , amp, amp, amp) :>_;
