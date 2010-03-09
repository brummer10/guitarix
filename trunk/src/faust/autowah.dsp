   //-----------------------------------------------
 
   //     Auto-Wha
 
   //-----------------------------------------------
 
 
   import("effect.lib"); //for crybaby definition

import("math.lib");
import("music.lib");

import("filter.lib");

monom 	=  _ <:  _,_;
switch1		= checkbox("on/off");
verb1    	= select2(switch1, _, _);
echo2  = vgroup("echo", (mono2stereo : _,echo1:>_ : dist));
balcb		= hslider("wet/dry", 0, -1, 1, 0.001);
balancecb		= *(1-max(0,0-balcb)), *(1-max(0,balcb));
//le   = hslider("level",0.1,0,1,0.01);
//wah  = vslider("wah", 0, 0, 1, 0.01);

 
//a = hslider("Mapping",1,1,50,0.1) ;
a = 1;

Sum(n,x) = +(x - (x @ n)) ~_ ;

Average(n,x) = x * (1<<22) : int : abs : Sum(n) : float : /(1<<22)
                 : /(n);

Map(x) = x * a : max(0) : min(1) ;


//process(x)	= vgroup("crybaby",monom : _, (_<: balancecb:(*: crybaby(x : Average(1000) : Map)),_:>_) : verb1);



process(x) = x : crybaby(x : Average(1000) : Map) ;
