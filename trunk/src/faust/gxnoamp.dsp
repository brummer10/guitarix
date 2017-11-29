declare id "noamp"; // in amp tube ba.selector
declare name "---";

import("stdfaust.lib");
import("guitarix.lib");

process = *(gain1) with {
    gain1 = ampctrl.gain1;
};
