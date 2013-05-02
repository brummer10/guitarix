declare id     "low_highcut";
declare name   "low high cut";
declare shortname "L/H/Filter";
declare category "Tone control";

import("effect.lib"); 
import("guitarix.lib");


process = +(anti_denormal_ac) : speakerbp(30.,988.) : highpass(1,100);
