import("stdfaust.lib");

fold = ffunction(float fold(float,float), <math.h>, "");
ngate = fvariable(float ngate, <math.h>);

feedback = hslider("amp.feedback[name:Feedback]", 0, -1, 1, 0.01);
feedforward = hslider("amp.feedforward[name:Feedforward]", 0, -1, 1, 0.01);
threshold = hslider("amp.fuzz[name:fuzz]", 1, 0, 1, 0.01);
tmax = 1-pow(10,-6); // 0 is bad value when using sigmoid in fold

fforw(x) = x + feedforward * x''';
fbackw = (- : ma.neg : *(ngate) : fold(min(tmax,threshold))) ~ (feedback * _'''');

process = fforw : fbackw <: _,_;
