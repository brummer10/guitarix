import("maxmsp.lib");
import("guitarix.lib");

declare name "HighShelf";

hs(x) = highShelf(x,F,G,Q)
with {
    G = -20.;
    F = SR/2 -100.;
    Q = 1.;
};

process = +(anti_denormal_ac) : hs;
