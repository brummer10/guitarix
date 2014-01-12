declare id   "ring modulator";
declare name "Ring Modulator Mono";
declare category "Modulation";

import("music.lib");

freq = hslider("freq", 240, 120, 1600, 0.5);
wet_dry = hslider("dry/wet", 0.5, 0, 1, 0.05);

process = _<:((1 - wet_dry)*_,(_*osc(freq))*wet_dry):>_;
