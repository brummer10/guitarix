declare id     "dcblocker";
declare name   "dcblocker";
declare shortname "dcblocker";
declare category "Tone Control";

declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2020";

import("stdfaust.lib"); 


process = fi.dcblockerat(1.0);
