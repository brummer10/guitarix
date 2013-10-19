import("filter.lib");
import("guitarix.lib");


ssclip(x) = a : sym_clip(0.9) with {
    th = 0.33;
    a = if(abs(x)<th, 2*x, copysign(x,(3-(2-x*3)^2)/3));
};

process = lowpass(1,5631): highpass(1,80):lowshelf(3,-6,350):*(1.4):ssclip  ;
