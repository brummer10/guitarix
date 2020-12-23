declare id "hardlim";
declare name "?limiter";
//declare category "Guitar Effects";

import("stdfaust.lib");
import("guitarix.lib");
rd = library("reducemaps.lib");


compressor_stereo(ratio,thresh,att,rel,x,y) = cgm*x, cgm*y with {
  cgm = compression_gain_mono(ratio,thresh,att,rel,max(abs(x),abs(y)));
};

compression_gain_mono(ratio,thresh,att,rel) =
  an.amp_follower_ar(att,rel) : ba.linear2db  : outminusindb(ratio,thresh) :
  kneesmooth(att) : ba.db2linear : vmeter1
with {
  // kneesmooth(att) installs a "knee" in the dynamic-range compression,
  // where knee smoothness is set equal to half that of the compression-attack.
  // A general 'knee' parameter could be used instead of tying it to att/2:
  kneesmooth(att)  = si.smooth(ba.tau2pole(att/2.0));
  // compression gain in dB:
   outminusindb(ratio,thresh,level) = max(level-thresh,0.0) * (1.0/float(ratio)-1.0) ;
  // Note: "float(ratio)" REQUIRED when ratio is an integer > 1!
vmeter1(x)		= attach(x, envelop(1.0-x) : vbargraph("v1[nomidi][tooltip:Rack output Limiter]", 0.0, 1.0));

envelop         = abs : max ~ (1.0/ma.SR) : rd.maxn(1024); // : max(ba.db2linear(-70)) : ba.linear2db;
};


lim = compressor_stereo(4,-6,0.0008,0.5);

process = lim;
