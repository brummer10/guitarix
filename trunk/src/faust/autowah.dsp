//-----------------------------------------------
//     Auto-Wah
//-----------------------------------------------

import("effect.lib"); //for crybaby definition

a = 20 * vslider(".crybaby.wah[old:fslider11]", 0, 0, 1, 0.01);

Sum(n,x) = +(x - (x @ n)) ~_ ;

Average(n,x) = x * (1<<22) : int : abs : Sum(n) : float : /(1<<22)
                 : /(n);

Map(x) = x * a : max(0) : min(1) ;

process(x) = x : crybaby(x : Average(1000) : Map) ;
