declare name "amp";

import("math.lib");

b = hslider("fuzz", 0.01, 0.01, 0.99, 0.01);
a = 1-b;
cut(x) = (fabs (x-a) -fabs (x+a))*0.5;

process(x) = cut(x);
