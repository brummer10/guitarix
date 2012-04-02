import("guitarix.lib");
import("oscillator.lib");

process = oscrq(vibe_lfo_ctrl.freq) : phase_shift(vibe_lfo_ctrl.phase) <: scale, scale with {
    phase_shift(p, x, y) = x, x * cos(p) + y * sin(p);
    scale = (1 + _) / 2;
};
