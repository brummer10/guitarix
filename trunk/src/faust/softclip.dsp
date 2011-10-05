declare id "amp.clip";

import("math.lib");
import("guitarix.lib");
b = hslider(".amp.fuzz", 0.0, 0.0, 1.99, 0.01);
a = 2-b;
//cut(x) = (fabs (x-a) -fabs (x+a))*0.5;
r(x) = x-sym_clip(a*0.88);
process(x) = x:sym_clip(a*0.88) <:+(r(x)*0.33);
