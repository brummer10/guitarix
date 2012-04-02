import("guitarix.lib");
import("oscillator.lib");

trianglewave(periodsamps) = rawsaw(periodsamps) : triangleshaper with {
    triangleshaper = 2 * _ / periodsamps <: select2(_ > 1, _, 2 - _);
};

process = trianglewave(periodsamps) with {
    periodsamps = SR/vibe_mono_lfo_ctrl.freq;
};
