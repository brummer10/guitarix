declare id "clipper";
declare name "Clip";
declare category "Fuzz";
declare samplerate "96000";

import("stdfaust.lib");

asymclip = ffunction(float asymclip(float), "clipping.h", "");
asclip = asymclip(_);

asymclip2 = ffunction(float asymclip2(float), "clipping.h", "");
asclip2 = asymclip2(_);

asymclip3 = ffunction(float asymclip3(float), "clipping.h", "");
asclip3 = asymclip3(_);

asymclip4 = ffunction(float asymclip4(float), "clipping.h", "");
asclip4 = asymclip4(_);

asymhardclip = ffunction(float asymhardclip(float), "clipping.h", "");
ashardclip = asymhardclip(_);

asymhardclip2 = ffunction(float asymhardclip2(float), "clipping.h", "");
ashardclip2 = asymhardclip2(_);

symclip = ffunction(float symclip(float), "clipping.h", "");
sclip = symclip(_);

symclip2 = ffunction(float symclip2(float), "clipping.h", "");
sclip2 = symclip2(_);

preclip = min(1) : max(-0.6);

clip(x) = ba.if ((x > 0), (1 - exp(-x)), (-1 + exp(x)));

eclip(x) = ((exp(x*4)-exp(-x*4*1.2))/(exp(x*4)+exp(-x*4)))/4;
tclip(x) = ma.tanh((1.0001)*x)/ma.tanh(1.0001);

process =  asclip4;
