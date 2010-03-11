declare name "amp";

import("math.lib");

fold = ffunction(float fold(float,float), <math.h>, "");
ngate = fvariable(float ngate, <math.h>);

feedback = hslider("feedback[name:Feedback][old:fslider0]", 0, -1, 1, 0.01);
feedforward = hslider("feedforward[name:Feedforward][old:fslider23]", 0, -1, 1, 0.01);
threshold = hslider("fuzz[name:fuzz][old:fthreshold]", 1, 0, 1, 0.01);

fforw(x) = x + feedforward * x''';
fbackw = (- : neg : *(ngate) : fold(threshold)) ~ (feedback * _'''');

process = fforw : fbackw <: _,_;
