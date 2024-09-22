declare id "hardlim";
declare name "?limiter";
//declare category "Guitar Effects";

import("stdfaust.lib");
import("guitarix.lib");
rd = library("reducemaps.lib");

softclip_stereo_with_meters(th,x,y) = softclip_stereo(th,x,y) with {
  softclip_stereo(th) = (softclip(th):vmeter1),(softclip(th):vmeter2);

  softclip(th,x) = softsat(x) with {
    softsat(x) = ba.if(abs(x)<=th,x,ma.signum(x)*fun(x));
    fun(x)=1.0+(th-1.0)*exp((abs(x)-th)/(th-1.0));
    //fun(x)=(((2.0-th)-(abs(x)+th)/2.0)*(abs(x)-th)/2.0/(1.0-th) + th);
  };

  
  // ::: Meter :::
  vmeter1(x) = attach(x, envelop(max(abs(x)-th,0.0)/(1.0-th)) :
                      vbargraph("v1[nomidi][tooltip:Rack output limiter left]", 0.0, 1.0));
  vmeter2(x) = attach(x, envelop(max(abs(x)-th,0.0)/(1.0-th)) :
                      vbargraph("v2[nomidi][tooltip:Rack output limiter right]", 0.0, 1.0));
  envelop    = abs : max ~ (1.0/ma.SR) : rd.maxn(1024); 
};



// This is where soft clipping will start
clip_ceiling = ba.db2linear(-1.0);  // below 0.0dB
    
//lim = compressor_stereo(4,-3.0,0.0008,0.5);
lim = softclip_stereo_with_meters(clip_ceiling);

process = lim;

