declare name "Overdrive";
declare category "Distortion";

import("stdfaust.lib");
import("guitarix.lib");

drive = vslider("drive[name:Drive]", 1, 1, 20, 0.1);
f = drive * -0.5 : ba.db2linear : smoothi(0.999);

wet = vslider("wet_dry[name:Dry/Wet][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;

overdrive(x) = (x*(abs(x) + drive)/(x*x + (drive-1)*abs(x) + 1)) * f;

process =  _<:*(dry),(*(wet) : overdrive):>_;
