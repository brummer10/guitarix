declare name "preamp";

fatan = vslider("atan[name:drive][tooltip:Input level for pre-amp (higher level gives more distortion)]", 1, 1, 10, 1);
moving_filter(x) = (x+x'+x'')/3;
nonlin1(x) = (x-0.15*x*x)-(0.15*x*x*x);
nonlin2(x) = 1.5*x - 0.5*x*x*x;
normalize(fatan) =  1/atan(fatan) * atan(_*fatan);
process = moving_filter*0.001 : nonlin1 : nonlin2, fatan : normalize*750
