declare id "withe_noise_stereo"; // 
declare name "withe noise_stereo";

import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** no.noise to avoid denormals
 */
 

randomr  = +(12345)~*(1103515245);
noiser   = (randomr/2147483647.0) * 0.00000000001;

process = + ( noiser), + ( noiser);
