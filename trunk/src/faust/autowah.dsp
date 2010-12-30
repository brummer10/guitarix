//-----------------------------------------------
//     Auto-Wah
//-----------------------------------------------

import("effect.lib"); //for crybaby definition
import("guitarix.lib");

a = 20 * vslider(".crybaby.wah[alias]", 0, 0, 1, 0.01);
w = vslider(".crybaby.wet_dry[alias]", 0, -1, 1, 0.1);
l = vslider(".crybaby.level[alias]", 0, -1, 1, 0.1);
Sum(n,x) = +(x - (x @ n)) ~_ ;

Average(n,x) = x * (1<<22) : int : abs : Sum(n) : float : /(1<<22)
                 : /(n);

Map(x) = x * a : max(0) : min(1) ;
 

process(x) = x : wet_dry_mix(w,*(l) :crybaby(x : Average(1000) : Map)) ;
