declare id     "ampmodul";
declare name   "Postamp";
declare category "Distortion";
declare groups "amp2.stage1[Postamp Tube1], amp2.stage2[Postamp Tube2]";
declare samplerate "96000";

import("stdfaust.lib"); 
import("guitarix.lib");

feedback = hslider("feedback[name:Wet/FB]", 0, -1, 1, 0.01);
fbackw = (- : ma.neg ) ~ (feedback * _'''');

feedbac = hslider("feedbac[name:Dry/FB]", 0, -1, 1, 0.01);
fback = (- : ma.neg ) ~ (feedbac * _'''');

preamp =  (vslider(".ampmodul.amp2.stage1.tube1[name:Tube I]",6,-20,20,0.1):ba.db2linear : smoothi(0.999)); 
gain1 = vslider(".ampmodul.amp2.stage2.tube2[name:Tube II]", 6, -20.0, 20.0, 0.1) : ba.db2linear : smoothi(0.999);
gain = vslider("level[name:Level]", -20, -40, 4, 0.1) : ba.db2linear : smoothi(0.999);

wet_dry = vslider("wet_dry[name:Dry/Wet]", 0, -1, 1, 0.1);
balanc(b) = *(1 - max(0, b)), *(1 - max(0, -b));
wet_dry_mx(w, Fx) = _ <: (_:fback), Fx : balanc(w) : +;

process = wet_dry_mx(wet_dry, _:(*(gain) : component("gxamp2.dsp").tubec(preamp,gain1):fbackw)), wet_dry_mx(wet_dry, _:(*(gain) : component("gxamp2.dsp").tubec(preamp,gain1):fbackw));
