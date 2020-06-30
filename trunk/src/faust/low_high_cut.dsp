declare id     "low_highcut";
declare name   "low high cut";
declare shortname "L/H/Filter";
declare category "Tone Control";

import("stdfaust.lib"); 
import("guitarix.lib");

process = +(anti_denormal_ac) : ef.speakerbp(23.,999.);
