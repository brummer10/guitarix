
import("stdfaust.lib");
import("guitarix.lib");

fuzzy = vslider("fuzzy[name:ba.count]", 1, -3, 10, 1);
process = fuzzy_tube(a,b,c,fuzzy)
with {
  a = 2;
  b = 1;
  c = 0.5;
};
