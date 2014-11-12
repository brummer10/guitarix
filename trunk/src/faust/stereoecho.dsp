declare name "Stereo Echo";
declare category "Echo / Delay";

import("music.lib");
import("guitarix.lib");
msec	= SR/1000.0;


lfol = component("oscillator.lib").oscrs; // sine for left channel

//freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
freq     = hslider("lfobpm[name:LFO freq (bpm)][tooltip:LFO in Beats per Minute]",24,24,360,1)/60;
pingpong   = checkbox("invert[enum:linear|pingpong]");

//tl = vslider("time_l", 1, 1, 2000, 1);
releasel = vslider("percent_l", 0, 0,  100, 0.1);
//tr = vslider("time_r", 1, 1, 2000, 1);
releaser = vslider("percent_r", 0, 0,  100, 0.1);
tl       = tempo(hslider("lbpm[name:time (bpm)][tooltip:Echo in Beats per Minute]",120,24,360,1));
tr       = tempo(hslider("rbpm[name:time (bpm)][tooltip:Echo in Beats per Minute]",120,24,360,1));
N       = int( 2^19);

echo1  = +~(sdelay(N, 1024,  int(tl)-1) * ((releasel/100.0)*(1-(lfol(freq)*pingpong))) );
echo2  = +~(sdelay(N, 1024,  int(tr)-1) * ((releaser/100.0)*(1-((-1*lfol(freq))*pingpong))) );
process = echo1,echo2;
