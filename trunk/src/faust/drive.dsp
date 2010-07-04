import("guitarix.lib");

fuzzy = vslider("value[name:drive]", 1, 1, 10, 1);
process = fuzzy_tube(a,b,c,fuzzy)
with {
  a = 4;
  b = 4;
  c = 0.125;
};
