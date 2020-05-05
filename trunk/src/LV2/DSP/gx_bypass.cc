/*
 * Copyright (C) 2020 Hermann Meyer, Andreas Degert, Steve Poskitt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 */


class GxBypass {
private:
    // bypass ramping
    uint32_t        bypass_;

    bool            needs_ramp_down;
    bool            needs_ramp_up;
    bool            bypassed;
    float           ramp_down;
    float           ramp_up;
    float           ramp_up_step;
    float           ramp_down_step;
public:
    inline void init_bypass(uint32_t rate);
    inline bool pre_check_bypass(float *bypass, float *buf, float *input, uint32_t n_samples);
    inline void post_check_bypass(float *buf, float *output, uint32_t n_samples);
    inline bool pre_check_bypass(float *bypass, float *buf, float *buf1, float *input, float *input1, uint32_t n_samples);
    inline void post_check_bypass(float *buf, float *buf1, float *output, float *output1, uint32_t n_samples);
    GxBypass();
    ~GxBypass() {};
};

GxBypass::GxBypass() :
    bypass_(2),
    needs_ramp_down(false),
    needs_ramp_up(false),
    bypassed(false) {};


inline void GxBypass::init_bypass(uint32_t rate) {
    // set values for internal ramping
    ramp_down_step = 32 * (256 * rate) / 48000; 
    ramp_up_step = ramp_down_step;
    ramp_down = ramp_down_step;
    ramp_up = 0.0;
}
//mono
inline bool GxBypass::pre_check_bypass(float *bypass, float *buf, float *input, uint32_t n_samples) {

    if (bypass_ != static_cast<uint32_t>(*(bypass))) {
        bypass_ = static_cast<uint32_t>(*(bypass));
        if (!bypass_) {
            needs_ramp_down = true;
            needs_ramp_up = false;
        } else {
            needs_ramp_down = false;
            needs_ramp_up = true;
            bypassed = false;
        }
    }
    if (needs_ramp_down || needs_ramp_up) {
        memcpy(buf, input, n_samples*sizeof(float));
    }
    return bypassed;
}
//mono
inline void GxBypass::post_check_bypass(float *buf, float *output, uint32_t n_samples) {

    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<n_samples; i++) {
            if (ramp_down >= 0.0) {
                --ramp_down; 
            }
            fade = max(0.0,ramp_down) /ramp_down_step ;
            output[i] = output[i] * fade + buf[i] * (1.0 - fade);
        }

        if (ramp_down <= 0.0) {
            needs_ramp_down = false;
            bypassed = true;
            ramp_down = ramp_down_step;
            ramp_up = 0.0;
        } else {
            ramp_up = ramp_down;
        }

    } else if (needs_ramp_up) {
        float fade = 0;
        for (uint32_t i=0; i<n_samples; i++) {
            if (ramp_up < ramp_up_step) {
                ++ramp_up ;
            }
            fade = min(ramp_up_step,ramp_up) /ramp_up_step ;
            output[i] = output[i] * fade + buf[i] * (1.0 - fade);
            }

        if (ramp_up >= ramp_up_step) {
            needs_ramp_up = false;
            ramp_up = 0.0;
            ramp_down = ramp_down_step;
        } else {
            ramp_down = ramp_up;
        }
    }
}
// stereo
inline bool GxBypass::pre_check_bypass(float *bypass, float *buf, float *buf1, float *input, float *input1, uint32_t n_samples) {

    if (bypass_ != static_cast<uint32_t>(*(bypass))) {
        bypass_ = static_cast<uint32_t>(*(bypass));
        if (!bypass_) {
            needs_ramp_down = true;
            needs_ramp_up = false;
        } else {
            needs_ramp_down = false;
            needs_ramp_up = true;
            bypassed = false;
        }
    }
    if (needs_ramp_down || needs_ramp_up) {
        memcpy(buf, input, n_samples*sizeof(float));
        memcpy(buf1, input1, n_samples*sizeof(float));
    }
    return bypassed;
}
// stereo
inline void GxBypass::post_check_bypass(float *buf, float *buf1, float *output, float *output1, uint32_t n_samples) {

    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<n_samples; i++) {
            if (ramp_down >= 0.0) {
                --ramp_down; 
            }
            fade = max(0.0,ramp_down) /ramp_down_step ;
            output[i] = output[i] * fade + buf[i] * (1.0 - fade);
            output1[i] = output1[i] * fade + buf1[i] * (1.0 - fade);
        }

        if (ramp_down <= 0.0) {
            needs_ramp_down = false;
            bypassed = true;
            ramp_down = ramp_down_step;
            ramp_up = 0.0;
        } else {
            ramp_up = ramp_down;
        }

    } else if (needs_ramp_up) {
        float fade = 0;
        for (uint32_t i=0; i<n_samples; i++) {
            if (ramp_up < ramp_up_step) {
                ++ramp_up ;
            }
            fade = min(ramp_up_step,ramp_up) /ramp_up_step ;
            output[i] = output[i] * fade + buf[i] * (1.0 - fade);
            output1[i] = output1[i] * fade + buf1[i] * (1.0 - fade);
            }

        if (ramp_up >= ramp_up_step) {
            needs_ramp_up = false;
            ramp_up = 0.0;
            ramp_down = ramp_down_step;
        } else {
            ramp_down = ramp_up;
        }
    }
}
