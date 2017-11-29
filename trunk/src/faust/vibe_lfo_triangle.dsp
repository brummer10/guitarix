import("guitarix.lib");
import("stdfaust.lib");

rawsaw_stereo(periodsamps, phasesamps) = rawsaw(periodsamps) <: _, shift(phasesamps) with {
    shift(x) = _+x, periodsamps : fmod;
};

triangle_stereo(periodsamps, phasesamps) = rawsaw_stereo(periodsamps, phasesamps) : os.triangle with {
    triangleshaper = 2 * _ / periodsamps <: select2(_ > 1, _, 2 - _);
    os.triangle = triangleshaper, triangleshaper;
};

process = triangle_stereo(periodsamps, phasesamps) with {
    periodsamps = ma.SR/vibe_lfo_ctrl.freq;
    phasesamps = periodsamps * (1 + vibe_lfo_ctrl.phase / (2 * ma.PI));
};
