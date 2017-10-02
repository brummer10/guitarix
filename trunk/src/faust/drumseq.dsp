declare id "seq";
declare name "DrumSequencer";
declare category "Misc";
declare shortname "Drum";
declare description "Simple Drum Step Sequencer";

//https://github.com/josmithiii/faust-jos/tree/master/percussion

ml = library("music.lib");
fl = library("filter.lib");

hat = (vgroup("hat_closed.dsp",component("hat_closed.dsp"))); // hat_closed.dsp
kick = (vgroup("kick.dsp",component("kick.dsp"))); // kick.dsp
snare = (vgroup("snare.dsp",component("snare.dsp"))); // snare.dsp
tom = (vgroup("tom.dsp",component("tom.dsp"))); // tom.dsp
gain  = vslider("gain [tooltip: Volume level in decibels]",-20,-60,40,0.1) : fl.smooth(0.999) : ml.db2linear;
process(x) = hat+kick+snare+tom : *(gain) : +(x) : _;

