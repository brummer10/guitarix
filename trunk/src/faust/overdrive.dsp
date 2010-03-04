drive = vslider("drive[old:drive]", 1, 1, 20, 0.1);
f0 = 0.001 * pow(10, (0.05 * (drive * -0.5)));
f1 = +(f0) ~ 0.999;

process(x) = (x*(abs(x) + drive)/(x*x + (drive-1)*abs(x) + 1)) * f1;
