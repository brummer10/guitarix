// dsp algorithm from swh ladspa valve plugin (Steve Harrison)

import("music.lib");
import("guitarix.lib");

vt = valve.vt(dist, q) : neg : valve.vt(dist, q) : neg with
{
        q_p = vslider("q", 0, 0.5, 2, 0.01);
        dist_p = vslider("dist", 0, 0, 2, 0.01);
        q = -q_p*-q_p*-q_p;
        dist = pow(10,dist_p);
};

process = vt ,vt ;
