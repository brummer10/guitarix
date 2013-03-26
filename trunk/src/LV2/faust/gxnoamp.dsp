declare id "noamp"; // in amp tube selector
declare name "---";

import("guitarix.lib");

process = *(gain1) with {
    gain1 = ampctrl.gain1;
};
