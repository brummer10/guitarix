declare id "noampstereo"; // in amp tube ba.selector
declare name "---";

import("stdfaust.lib"); 
import("guitarix.lib");

amp = *(preamp) : *(gain1) with {
    gain1 = ampctrl.gain1;
    preamp = ampctrl.preamp;
};

process = amp, amp;
