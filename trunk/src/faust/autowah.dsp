declare id "auto"; // ba.selector ve.crybaby / ve.autowah
declare name "auto";

//-----------------------------------------------
//     Auto-Wah
//-----------------------------------------------

import("stdfaust.lib"); //for ve.crybaby definition
import("guitarix.lib");

l = crybaby_ctrl.level;
a = crybaby_ctrl.wah;
w = crybaby_ctrl.wet_dry;
/*
a = 20 * vslider(".ve.crybaby.wah[alias]", 0, 0, 1, 0.01);
w = vslider(".ve.crybaby.wet_dry[alias]", 100, 0, 100, 0.1):/(100);
l = vslider(".ve.crybaby.level[alias]", 0, -1, 1, 0.1);
*/

d = 1-w;
Sum(n,x) = +(x - (x @ n)) ~_ ;

Average(n,x) = x * (1<<22) : int : abs : Sum(n) : float : /(1<<22)
                 : /(n);

Map(x) = x * a : max(0) : min(1) ;
 //ve.autowah(level,x) = level * ve.crybaby(an.amp_follower(0.1,x),x) + (1.0-level)*x;
//an.amp_follower_ud(att,rel) = an.amp_follower(rel) : si.smooth(ba.tau2pole(att));

//process(x) = x : _<:*(d),(*(w):*(l) :ve.crybaby(x : Average(1000) : Map)):>_ ;
process(x) = x : _<:*(d),(*(w):*(l) :a * ve.crybaby(x : an.amp_follower_ud(0.01,0.1) : min(1)) + (1.0-a) * x):>_ ;
