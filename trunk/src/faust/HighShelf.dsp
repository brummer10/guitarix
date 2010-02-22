import("maxmsp.lib");
declare name "HighShelf";

G = -20;
F = SR/2 -100;
Q = 100;

process(x) = highShelf(x,F,G,Q);


