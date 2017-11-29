// dsp algorithm from swh ladspa valve plugin (Steve Harrison)

import("stdfaust.lib");
import("guitarix.lib");

g = vslider("g", 1, 0.2, 2, 0.1);

vt = valve.vt(dist, q) : *(g) : ma.neg : valve.vt(dist, q) : ma.neg with
{
        q_p = vslider("q", 0.4, 0.4, 1, 0.001);
        dist_p = vslider("dist", 0, 0, 1.7, 0.01);
        q = -q_p*-q_p*-q_p;
        dist = pow(10,dist_p);
};

process = vt  ;
