fatan = vslider("atan[name:drive][old:fatan][tooltip:Input level for pre-amp (higher level gives more distortion)]", 1, 1, 10, 1);
moving_filter(x) = (x+x'+x'')/3;
nonlin1(x) = (x-0.15*x*x)-(0.15*x*x*x);
nonlin2(x) = 1.5*x - 0.5*x*x*x;
normalize(fatan) =  1/atan(fatan) * atan(_*fatan);
process = moving_filter : nonlin1 : nonlin2 : normalize(fatan)*0.75 : moving_filter;
/*
** old definition was:
** moving_filter*0.001 : nonlin1 : nonlin2 : normalize(fatan)*750;
*/