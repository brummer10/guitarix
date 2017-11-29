declare id "tube2";
import("stdfaust.lib");
import("guitarix.lib");

resonator = (+ <: (de.delay(4096, d-1) + de.delay(4096, d))/2.0)~*(1.0-a)
with {
//d = vslider("vibrato", 0.5, 0, 1, 0.01);
d = 1 - vslider("vibrato[alias]", 1, 0, 1, 0.01);
//a = vslider("trigger", 0.12, 0, 1, 0.01);
a = 0.9 - vslider("resonanz[alias]", 0.5, 0, 0.9, 0.01);
};

//fuzzy = vslider("fuzzy", 0.5, 0, 1, 0.01);
fuzzy = vslider("fuzzy[name:tube][alias]", 1, -3, 10, 1);
tube1 = nonlin1 : resonator * fuzzy * 0.5 : sym_clip(0.7) : ma.neg;

process = add_dc <: _ + tube1 : sym_clip(0.7);
