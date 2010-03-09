import("effect.lib");
level = vslider("level[old:fslider12]", 0.1, 0, 1, 0.01);
wah = vslider("wah[old:fslider11]", 0, 0, 1, 0.01);
process = crybaby(wah);
