declare name "amp";

import("math.lib");

fold = ffunction(float fold(float,float), <math.h>, "");
ngate = fvariable(float ngate, <math.h>);

feedback = hslider("feedback[name:Feedback][old:fslider0]", 0, -1, 1, 0.01);
feedforward = hslider("feedforward[name:Feedforward][old:fslider23]", 0, -1, 1, 0.01);
threshold = hslider("fuzz[name:fuzz][old:fthreshold]", 1, 0, 1, 0.01);
tmax = 1-pow(10,-6); // 0 is bad value when using sigmoid in fold

fforw(x) = x + feedforward * x''';
fbackw = (- : neg : *(ngate) : fold(min(tmax,threshold))) ~ (feedback * _'''');

process = fforw : fbackw <: _,_;
