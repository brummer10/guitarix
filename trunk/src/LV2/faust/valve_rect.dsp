// dsp algorithm from swh ladspa valve_rect plugin (Steve Harrison)

import("stdfaust.lib");
import("guitarix.lib");

sag = vslider("sag", 0, 0, 1, 0.01);
dist_p = vslider("dist", 0, 0, 1, 0.01);

process(x) = valve.vt(dist, q(x), x)
with {
    dist = dist_p * 40 + 0.1;
    q(x) = lp1tm1(x) * sag - lp2tm1(x) * 1.02 - 1.0 : clip(-1,-0.01);
    lp(a) = *(1 - a) : + ~ *(a);
    lp1tm1 = abs <: lp(0.9999), _ : max;
    avgs = lp1tm1 : avg;
    avg_size = ma.SR/9;
    avg(x) = x - delay1s(avg_size,x) : + ~ _ : /(avg_size);
    lp2tm1 = avgs : lp(0.999);
};
