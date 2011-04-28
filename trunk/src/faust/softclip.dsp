declare name "amp";

import("math.lib");
import("guitarix.lib");
b = hslider("fuzz", 0.0, 0.0, 1.99, 0.01);
a = 2-b;
//cut(x) = (fabs (x-a) -fabs (x+a))*0.5;

process = sym_clip(a);
