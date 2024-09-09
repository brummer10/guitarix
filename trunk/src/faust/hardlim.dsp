declare id "hardlim";
declare name "?limiter";
//declare category "Guitar Effects";

import("stdfaust.lib");
import("guitarix.lib");
rd = library("reducemaps.lib");

softclip_stereo_with_meters(th,x,y) = softclip_stereo(th,x,y) with {
  softclip(th,x) = softsat(preclip(x)) with {
    // The softsat function will map [-cth,cth] to [-1,1], but outside of that input range
    // it is not well behaved.  So, hard clip to the valid input range first.
    preclip(x) = aa.clip(-cth,cth,x);
    // Defines a transfer function with linearly decaying derivative ouside of [-th,th]
    softsat(x) = ba.if(ax<=th,x,ma.signum(x)*((cth-(ax+th)/2.0)*(ax-th)/2.0/(1.0-th) + th));
    cth = 2-th;                
    ax=abs(x);
  };
  softclip_stereo(th) = (vmeter1:softclip(th)),(vmeter2:softclip(th));

  // ::: Meter :::
  vmeter1(x) = attach(x, envelop(max(abs(x)-th,0.0)/th/2) :
                      vbargraph("v1[nomidi][tooltip:Rack output limiter left]", 0.0, 1.0));
  vmeter2(x) = attach(x, envelop(max(abs(x)-th,0.0)/th/2) :
                      vbargraph("v2[nomidi][tooltip:Rack output limiter right]", 0.0, 1.0));
  envelop    = abs : max ~ (1.0/ma.SR) : rd.maxn(1024); 
};



// This is where soft clipping will start
clip_ceiling = ba.db2linear(-1.0);  // below 0.0dB
    
//lim = compressor_stereo(4,-3.0,0.0008,0.5);
lim = softclip_stereo_with_meters(clip_ceiling);

process = lim;

