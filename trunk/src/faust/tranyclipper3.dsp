declare id "tranclip";
declare name "Clip";
declare category "Fuzz";
declare samplerate "96000";

import("stdfaust.lib");
import("trany.lib");

process = tranystage(TB_KT88_68k,86.0,2700.0,5.562895) : tranystage(TB_KT88_68k,86.0,2700.0,5.562895) ;
