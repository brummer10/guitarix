/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * --------------------------------------------------------------------------
 */
#pragma once

#ifndef SRC_HEADERS_GX_FAUST_INCLUDES_H_
#define SRC_HEADERS_GX_FAUST_INCLUDES_H_

// forward declaration of compute methodes
namespace gx_engine {
namespace gx_effects {
namespace jconv_post {
extern void compute(int count, float* output0, float* output1, float* conv_out0, float* conv_out1,
               float* output2, float* output3);
} /* end of jconv_post namespace */
namespace gx_outputlevel {
extern void compute(int count, float* output0, float* output1, float* output2, float* output3);
} /* end of gx_outputlevel namespace */
namespace balance1 {
extern void compute(int count, float*input1, float*output0, float*output1);
} /* end of balance1 namespace */
} /* end of gx_effects namespace */

// define engine pointer typs
typedef void (*chainorder)
             (int count, float *output, float *output1);

typedef void (*stereochainorder)
             (int count, float* input, float* input1, float *output, float *output1);

// pointer to the choosen tonestack default setting
extern chainorder tonestack_ptr;

// pointer to the choosen amp default setting
extern chainorder amp_ptr;

// mono rack (pre/post) order pointer
extern chainorder pre_rack_order_ptr[];
extern chainorder post_rack_order_ptr[];

// stereo rack order pointer
extern stereochainorder stereo_rack_order_ptr[];

// check valid effect buffers
void check_effect_buffer();
void check_stereo_effect_buffer();

// engine helper threads
gboolean gx_reorder_rack(gpointer args);
gboolean gx_check_engine_state(gpointer args);

// cabinet pre processing
void init_non_rt_processing();
void non_rt_processing(int count, float* input, float* output0);

// register vars to param and init
void register_faust_parameters();
void faust_init(int samplingFreq);
} /* end of gx_engine namespace */
#endif  // SRC_HEADERS_GX_FAUST_INCLUDES_H_

