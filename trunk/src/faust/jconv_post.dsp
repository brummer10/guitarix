declare name "jconv";

import("music.lib");
import("guitarix.lib");

wet = vslider("wet_dry[name:wet/dry]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;
deltadelay = vslider("diff_delay[name:Delta Delay]",   0, -10, 10, 0.1)*millisec;
//bug in faust (at least up to version 0.9.27)
//ldelay = -deltadelay : max(0);
//rdelay = deltadelay : max(0);
ldelay = select2(deltadelay > 0, -deltadelay, 0);
rdelay = select2(deltadelay < 0, deltadelay, 0);

gain = vslider("gain[name:Gain]", 0, -20, 20, 0.1) : db2linear : smoothi(0.999);
jbal = vslider("balance[name:Balance]", 0, -1, 1, 0.1);
bal = vslider(".amp.balance[name:Balance][alias]", 0, -1, 1, 0.1);
fx = gain * fdelay1s(ldelay), gain * fdelay1s(rdelay) : balance(jbal);
process = *(dry), *(dry), (*(wet),*(wet) : fx) :> balance(bal);
