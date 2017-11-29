declare id "HighShelf";

import("maxmsp.lib");
import("guitarix.lib");

hs(x) = highShelf(x,F,G,Q)
with {
    G = -20.;
    F = ma.SR/2 -100.;
    Q = 100.;
};

process = +(anti_denormal_ac) : hs;
