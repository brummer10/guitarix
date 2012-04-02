import("guitarix.lib");
import("oscillator.lib");

process = oscs(vibe_mono_lfo_ctrl.freq) : scale with {
    scale = (1 + _) / 2;
};
