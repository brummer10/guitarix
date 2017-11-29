declare id "bboom";
declare name "Bass Boom";
declare shortname "B Boom";
declare category "Distortion";
declare description "Sub Bass Booster";

import("stdfaust.lib");

anti_denormal = pow(10,-20);
anti_denormal_ac = 1 - 1' : *(anti_denormal) : + ~ *(-1);

geq = fi.filterbank(3, (110));

Drive     = hslider("Drive [tooltip: Amount of SubBass Harmonics]", 0.33, 0, 1, 0.01);

Gain      = vslider("Gain", 0, -40, 4, 0.1) : ba.db2linear : si.smooth(0.999);
   
bassclip(drive) = *(pregain) : preclip : clip : *(postgain) with {
    pregain = pow(10.0,1.5*drive); 
    preclip =  min(1) : max(-1); 
    clip(x) = ((exp(x*4)-exp(-x*4*1.2))/(exp(x*4)+exp(-x*4)))/4;
    postgain = max(1.0,1.0/(pregain*2.5));
};
    
clip(drive) = *(pregain) : clip : *(postgain) with {
    pregain = pow(10.0,2*drive);
    clip = ffunction(float symclip(float), "clipping.h", "");
    postgain = max(1.0,1.0/pregain);
};
 
process    = _: +(anti_denormal_ac): geq: ( _, dist1s) :> *(Gain) with { 
    dist1s = bassclip(Drive: si.smooth(0.999)) ;
    
};
