declare name "tube2";

import("music.lib");
import("effect.lib");
import("guitarix.lib");

resonator = (+ <: (delay(4096, d-1) + delay(4096, d))/2.0)~*(1.0-a)
with {
//d = vslider("vibrato[old:fresotube2]", 0.5, 0, 1, 0.01);
d = 1 - vslider("vibrato[old:fresotube2]", 1, 0, 1, 0.01);
//a = vslider("trigger[name:resonanz][old:fresotube1]", 0.12, 0, 1, 0.01);
a = 0.9 - vslider("resonanz[old:fresotube1]", 0.5, 0, 0.9, 0.01);
};

//fuzzy = vslider("fuzzy[name:count][old:fresotube3]", 0.5, 0, 1, 0.01);
fuzzy = vslider("fuzzy[name:count][old:fresotube3]", 1, -3, 10, 1);

tube1 = component("HighShelf.dsp").hs : nonlin1 : resonator : +(anti_denormal_ac) : speakerbp(130,5000) * fuzzy * 0.5;
process(x) = x + tube1(x) : sym_clip(0.7);
