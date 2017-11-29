import("guitarix.lib");
import("stdfaust.lib");

process = os.oscs(vibe_mono_lfo_ctrl.freq) : scale with {
    scale = (1 + _) / 2;
};
