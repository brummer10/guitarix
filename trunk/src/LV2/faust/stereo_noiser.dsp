declare id "withe_noise_stereo"; // 
declare name "withe noise_stereo";

import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");

/****************************************************************
 ** noise to avoid denormals
 */
 

randomr  = +(12345)~*(1103515245);
noiser   = (randomr/2147483647.0) * 0.00000000001;



process = + ( noiser), + ( noiser);
