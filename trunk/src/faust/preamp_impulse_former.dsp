//declare name "Preamp Impulse Former";
declare id "pre";

import("stdfaust.lib");
import("guitarix.lib");

gain = vslider("Level[name:Level][tooltip:Level][alias]", 1, 0.1, 2.1, 0.1) ;

bass_gain	= vslider("bass[name:Bass][tooltip:Bass][alias]", 0, -10, 10, 0.5);

treble_gain	= vslider("treble[name:Treble][tooltip:Treble][alias]", 0, -10, 10, 0.5);

tone = component("tone.dsp").gxlow_shelf(300,bass_gain):
		component("tone.dsp").gxhigh_shelf(2400,treble_gain);

process = tone : *(gain * pow(10, -0.1 * gain)); // FIXME
