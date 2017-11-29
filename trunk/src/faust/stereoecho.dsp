declare name "Stereo Echo";
declare category "Echo / Delay";

import("stdfaust.lib");
import("guitarix.lib");
msec	= ma.SR/1000.0;

lfol = os.oscrs; // sine for left channel

//freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
freq     = hslider("lfobpm[name:LFO Freq][tooltip:LFO in Beats per Minute]",24,24,360,1)/60;
pingpong   = checkbox("invert[enum:linear|pingpong]");

//tl = vslider("time_l", 1, 1, 2000, 1);
releasel = vslider("percent_l[name:Release L]", 0, 0,  100, 0.1);
//tr = vslider("time_r", 1, 1, 2000, 1);
releaser = vslider("percent_r[name:Release R]", 0, 0,  100, 0.1);
tl       = ba.tempo(hslider("lbpm[name:Time L][tooltip:Echo in Beats per Minute]",120,24,360,1));
tr       = ba.tempo(hslider("rbpm[name:Time R][tooltip:Echo in Beats per Minute]",120,24,360,1));
N       = int( 2^19);

echo1  = +~(de.sdelay(N, 1024,  int(tl)-1) * ((releasel/100.0)*(1-(lfol(freq)*pingpong))) );
echo2  = +~(de.sdelay(N, 1024,  int(tr)-1) * ((releaser/100.0)*(1-((-1*lfol(freq))*pingpong))) );
process = echo1,echo2;
