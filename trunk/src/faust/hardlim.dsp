declare id "hardlim";
declare name "?limiter";
//declare category "Guitar Effects";

import("stdfaust.lib");
import("guitarix.lib");
rd = library("reducemaps.lib");

softclip_stereo_with_meters(th,x,y) = softclip_stereo(th,x,y) with {
  softclip_stereo(th) = (vmeterL:softclip(th)),(vmeterR:softclip(th));

  // ::: Clipper :::
  // Values above 'th' will be exponentially more distorted.  No
  // values above 1.0 are be allowed through.
  softclip(th,x) = softsat(x) with {
    softsat(x) = ba.if(abs(x)<=th,x,ma.signum(x)*fun(x));
    fun(x)=1.0+(th-1.0)*exp((abs(x)-th)/(th-1.0));
  };
  
  // ::: Meter :::
  vmeterL(x) = attach(x, envelop(meter_calc(x)) :
                      vbargraph("vleft[nomidi][tooltip:Rack output limiter left]", 0.0, 1.0));
  vmeterR(x) = attach(x, envelop(meter_calc(x)) :
                      vbargraph("vright[nomidi][tooltip:Rack output limiter right]", 0.0, 1.0));
  meter_calc(x) = min(max((x-th),0.0),1.0);
  envelop    = abs : max ~ (1.0/ma.SR) : rd.maxn(1024); 
};


// This is where soft clipping will start
clip_ceiling = ba.db2linear(-1.0);  // below 0.0dB
    
//lim = compressor_stereo(4,-3.0,0.0008,0.5);
lim = softclip_stereo_with_meters(clip_ceiling);

process = lim;

