declare name "jconv";

import("music.lib");
import("guitarix.lib");

wet_dry = vslider("wet_dry[name:wet/dry][old:fslider24]",  0, -1, 1, 0.1);
ldelay = vslider("left_delay[name:Left Delay][old:fsliderdel0]",   0, 0, 5000, 10)*millisec;
rdelay = vslider("right_delay[name:Right Delay][old:fsliderdel1]", 0, 0, 5000, 10)*millisec;
lgain = vslider("left_gain[name:Left Gain][old:fjc_ingain]", 0, -20, 20, 0.1) : db2linear : smoothi(0.999);
rgain = vslider("right_gain[name:Right Gain][old:fjc_ingain1]", 0, -20, 20, 0.1): db2linear : smoothi(0.999);
bal = vslider(".amp.balance[name:Balance][old:fslider25]", 0, -1, 1, 0.1);

dry = 1 - max(0, wet_dry);
wet = 1 - max(0, -wet_dry);
process = *(dry), *(dry), lgain * fdelay43s(ldelay) * wet, rgain * fdelay43s(rdelay) * wet :> balance(bal);
