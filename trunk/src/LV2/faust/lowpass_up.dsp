
import("stdfaust.lib");
import("guitarix.lib");

ssclip(x) = a : sym_clip(0.9) with {
    th = 0.33;
    a = ba.if(abs(x)<th, 2*x, copysign(x,(3-(2-x*3)^2)/3));
};

process = fi.lowpass(1,5631): fi.highpass(1,80):ssclip  ;
