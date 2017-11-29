declare id "jconv";

import("stdfaust.lib");
import("guitarix.lib");

wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;
deltadelay = vslider("diff_delay[name:Delta Delay][tooltip:de.delay left or right channel by the specified amount (unit: ms)]",   0, -100, 100, 0.01)*ba.millisec : smoothi(0.999);
gain = vslider("gain[name:Gain][tooltip:gain trim for processed signal (unit: dB)]", 0, -20, 20, 0.1) : ba.db2linear : smoothi(0.999);
jbal = vslider("balance[name:Balance][tooltip:left/right trim for processed signal]", 0, -1, 1, 0.1): smoothi(0.999);
bal = balance_ctrl.bal;

/*
** We want to move the sound source to the right
** with increasing values of deltadelay; this means
** we have to de.delay the left channel
*/
//bug in faust (at least up to version 0.9.27)
//rdelay = -deltadelay : max(0);
//ldelay = deltadelay : max(0);
rdelay = select2(deltadelay > 0, -deltadelay, 0);
ldelay = select2(deltadelay < 0, deltadelay, 0);

fx = gain * de.fdelay1s(ldelay), gain * de.fdelay1s(rdelay) : balance(jbal);
process = *(dry), *(dry), (*(wet),*(wet) : fx) :> balance(bal);
