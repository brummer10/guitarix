declare name "amp";

import("math.lib");

fold = ffunction(float fold(float), <math.h>, "");
ngate = fvariable(float ngate, <math.h>);

feedback = hslider("feedback[name:Feedback][old:fslider0]", 0, -1, 1, 0.01);
feedforward = hslider("feedforward[name:Feedforward][old:fslider23]", 0, -1, 1, 0.01);

fforw(x) = x + feedforward * x''';
fbackw = (- : neg : fold) ~ (feedback * _'''');

process = fforw : fbackw <: _,_;
