declare id       "antyfizz";
declare name     "Fizz Remover";
//declare category "Tone Control";
declare license  "BSD";

import("stdfaust.lib");

process = fi.peak_eq_cq(-8.5,5556,8.5), fi.peak_eq_cq(-8.5,5556,8.5);
