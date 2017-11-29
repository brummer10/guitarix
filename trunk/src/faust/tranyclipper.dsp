declare id "tranclip";
declare name "Clip";
declare category "Fuzz";
declare samplerate "96000";

import("stdfaust.lib");
import("trany.lib");

process = tranystage(TB_7199P_68k,86.0,2700.0,3.571981) : tranystage(TB_7199P_68k,86.0,2700.0,3.571981) ;
