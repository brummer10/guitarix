// dsp algorithm from swh ladspa valve plugin (Steve Harrison)

import("guitarix.lib");


q_p = vslider("q", 0, 0, 1, 0.01);
dist_p = vslider("dist", 0, 0, 1, 0.01);

process = valve_transfer(dist, q) : filter
with {
    q = q_p - 0.999 ;
    dist = dist_p * 40 + 0.1;
    filter(x) = +(x - x') ~ *(0.999);
};
