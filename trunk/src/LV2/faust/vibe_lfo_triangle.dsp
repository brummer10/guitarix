import("guitarix.lib");
import("oscillator.lib");

rawsaw_stereo(periodsamps, phasesamps) = rawsaw(periodsamps) <: _, shift(phasesamps) with {
    shift(x) = _+x, periodsamps : fmod;
};

triangle_stereo(periodsamps, phasesamps) = rawsaw_stereo(periodsamps, phasesamps) : triangle with {
    triangleshaper = 2 * _ / periodsamps <: select2(_ > 1, _, 2 - _);
    triangle = triangleshaper, triangleshaper;
};

process = triangle_stereo(periodsamps, phasesamps) with {
    periodsamps = SR/vibe_lfo_ctrl.freq;
    phasesamps = periodsamps * (1 + vibe_lfo_ctrl.phase / (2 * PI));
};
