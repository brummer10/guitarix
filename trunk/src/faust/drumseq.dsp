declare id "seq";
declare name "DrumSequencer";
declare category "Misc";
declare shortname "Drum";
declare description "Simple Drum Step Sequencer";

//https://github.com/josmithiii/faust-jos/tree/master/percussion

import("stdfaust.lib");

hat = (vgroup("hat_closed.dsp",component("hat_closed.dsp"))); // hat_closed.dsp
kick = (vgroup("kick.dsp",component("kick.dsp"))); // kick.dsp
snare = (vgroup("snare.dsp",component("snare.dsp"))); // snare.dsp
tom = (vgroup("tom.dsp",component("tom.dsp"))); // tom.dsp
gain  = vslider("gain [tooltip: Volume level in decibels]",-20,-60,40,0.1) : si.smooth(0.999) : ba.db2linear;
process(x) = hat+kick+snare+tom : *(gain) : +(x) : _;
