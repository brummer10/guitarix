import("guitarix.lib");
import("stdfaust.lib");

trianglewave(periodsamps) = rawsaw(periodsamps) : triangleshaper with {
    triangleshaper = 2 * _ / periodsamps <: select2(_ > 1, _, 2 - _);
};

process = trianglewave(periodsamps) with {
    periodsamps = ma.SR/vibe_mono_lfo_ctrl.freq;
};
