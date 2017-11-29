declare id "tube2";

import("stdfaust.lib");
import("guitarix.lib");

resonator = (+ <: (de.delay(4096, d-1) + de.delay(4096, d))/2.0)~*(1.0-a)
with {
//d = vslider("vibrato", 0.5, 0, 1, 0.01);
d = 1 - vslider("vibrato", 1, 0, 0.99, 0.01);
//a = vslider("trigger[name:resonanz]", 0.12, 0, 1, 0.01);
a = 0.9 - vslider("resonanz", 0.5, 0, 0.9, 0.01);
};

//fuzzy = vslider("fuzzy[name:tube]", 0.5, 0, 1, 0.01);
fuzzy = vslider("fuzzy[name:tube]", 1, -3, 10, 1);

tube1 = component("HighShelf.dsp").hs : nonlin1 : resonator : +(anti_denormal_ac) : ef.speakerbp(130,5000) * fuzzy * 0.5;
process(x) = x + tube1(x) : sym_clip(0.7);
