declare id "bmpf";
declare name "BigMuffFuzzPadel";
declare shortname "FuzzPadel";
declare category "Distortion";
declare description "BigMuffFuzzPadel";

import("guitarix.lib");
import("stdfaust.lib");

bigmuff      = _<: filter1,filter2:>_   with {
	tone     = vslider("tone",0.5,0,1,0.01);
	filter1  = fi.highpass( 1, 1856):*(tone);
	filter2  = fi.lowpass( 1, 408 ) :*(1-tone);
};

process = _<:*(dry),(*(wet):*(gain):bigmuff:fuzz:fuzzy:fiz):>downfilter with {
    //fuzz(x)      = x-0.15*x^2-0.15*x^3;
    //fuzz(x)      = 1.5*x-0.5*x^3;
    fuzz(x)      = (1+drive/101)*x/(1+drive/101*abs(x));
    drive        = vslider("drive", 1, -3, 100, 1);
    fuzzy        = fuzzy_tube(2,1,0.5,drive);
    fiz(x)       = x+(x^7);
    downfilter   = fi.lowpass(1,5631): fi.highpass(1,80);
    gain         = vslider("Input",0,-24,20,0.1) : ba.db2linear : smoothi(0.999);
    wet          = vslider("Output",  100, 50, 100, 1) : /(100);
    dry          = 1 - wet;

};
