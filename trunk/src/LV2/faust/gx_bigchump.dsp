declare name "Redeye Big Chump";
declare category "Amplifier";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");
import("redeye.lib");

trannie = coil1,coil2:>_ with {
	coil1 = lowpass( 1, ( 8075 )  ):highpass( 1, 84):*(0.98)  ;
	coil2 = lowpass( 1, 8925 ):highpass( 1, 76) ;
}; 


process = chumpPreamp:*(volume):amp with {
	
	volume = vslider("Volume[2][alias][style:knob]",0.5, 0, 1,0.01) : smoothi(0.999);
	// Look into these so we can more accurately copy PP 6V6 design
	pp1 = tubestage(TB_6V6_250k,60.0,822.0,1.130462); 
	pp2 = tubestage(TB_6V6_250k,60.0,818.0,1.130462); 
	// This splits positive and negative signals and sends each to different valves 
	positive(x) = x * ( x >= 0.0 ) ; 
	negative(x) = x * ( x <= 0.0 ) ;
	stage1 = tubestage(TB_12AX7_68k,40.0,2700.0,1.83);
	stage2 = lowpass( 1, 6531):tubestage(TB_12AX7_250k,40.0,2700.0,1.83) ;
	driver1 = lowpass( 1, 6531):tubestage(TB_12AU7_250k,132.0,1525.0,1.214285);
	driver2 = lowpass( 1, 6531):tubestage(TB_12AU7_250k,132.0,1475.0,1.204285);

	feedback = *(checkbox("feedback") ):*(0.5);

	// This is bodge for transformer simple low and high pass roll off

	pushpull = (positive:pp1),(negative:pp2) ;

	amp = (+:_<:pushpull:trannie:>_)~feedback ;
	atten = 0.5;
	cabinet = lowpass(2,5500):peak_eq(-15.0,400.0,600):highpass(2,80);

};
