// Auto-generated file. Do not edit!
//   Template: src/f32-spmm/scalar-pipelined.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <xnnpack/math.h>
#include <xnnpack/spmm.h>


void xnn_f32_spmm_minmax_ukernel_4x1__scalar_pipelined(
    size_t batch_size,
    size_t output_channels,
    const float*restrict input,
    const float*restrict weights,
    const int32_t*restrict widx_dmap,
    const uint32_t*restrict nidx_nnzmap,
    float*restrict output,
    const union xnn_f32_minmax_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch_size != 0);
  assert(batch_size % sizeof(float) == 0);
  assert(output_channels != 0);

  const float vmin = params->scalar.min;
  const float vmax = params->scalar.max;
  size_t output_decrement = batch_size * output_channels - 4 * sizeof(float);
  size_t n = batch_size;
  while XNN_LIKELY(n >= 4 * sizeof(float)) {
    const float*restrict w = weights;
    const int32_t* dmap = widx_dmap;
    const uint32_t* nnzmap = nidx_nnzmap;
    float vw = *w++;
    intptr_t diff = *dmap++;
    float vi0 = input[0];
    float vi1 = input[1];
    float vi2 = input[2];
    float vi3 = input[3];
    size_t c = output_channels;
    do {
      uint32_t nnz = *nnzmap++;
      float vacc0 = vw;
      float vacc1 = vw;
      float vacc2 = vw;
      float vacc3 = vw;
      vw = *w++;
      if XNN_LIKELY(nnz != 0) {
        do {
          vacc0 += vi0 * vw;
          vacc1 += vi1 * vw;
          vacc2 += vi2 * vw;
          vacc3 += vi3 * vw;
          input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);

          diff = *dmap++;
          vw = *w++;
          vi0 = input[0];
          vi1 = input[1];
          vi2 = input[2];
          vi3 = input[3];
        } while (--nnz != 0);
      }
      float vout0 = math_min_f32(vacc0, vmax);
      float vout1 = math_min_f32(vacc1, vmax);
      float vout2 = math_min_f32(vacc2, vmax);
      float vout3 = math_min_f32(vacc3, vmax);
      vout0 = math_max_f32(vout0, vmin);
      vout1 = math_max_f32(vout1, vmin);
      vout2 = math_max_f32(vout2, vmin);
      vout3 = math_max_f32(vout3, vmin);
      output[0] = vout0;
      output[1] = vout1;
      output[2] = vout2;
      output[3] = vout3;
      output = (float*restrict) ((uintptr_t) output + batch_size);
    } while (--c != 0);
    output = (float*restrict) ((uintptr_t) output - output_decrement);
    input += 4;
    n -= 4 * sizeof(float);
  }
  if XNN_UNLIKELY(n != 0) {
    output_decrement += 2 * sizeof(float);
    if (n & (2 * sizeof(float))) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      float vw = *w++;
      intptr_t diff = *dmap++;
      float vi0 = input[0];
      float vi1 = input[1];
      size_t c = output_channels;
      do {
        uint32_t nnz = *nnzmap++;
        float vacc0 = vw;
        float vacc1 = vw;
        vw = *w++;
        if XNN_LIKELY(nnz != 0) {
          do {
            vacc0 += vi0 * vw;
            vacc1 += vi1 * vw;
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);

            diff = *dmap++;
            vw = *w++;
            vi0 = input[0];
            vi1 = input[1];
          } while (--nnz != 0);
        }
        float vout0 = math_min_f32(vacc0, vmax);
        float vout1 = math_min_f32(vacc1, vmax);
        vout0 = math_max_f32(vout0, vmin);
        vout1 = math_max_f32(vout1, vmin);
        output[0] = vout0;
        output[1] = vout1;
        output = (float*restrict) ((uintptr_t) output + batch_size);
      } while (--c != 0);
      const size_t output_decrement = batch_size * output_channels - 2 * sizeof(float);
      output = (float*restrict) ((uintptr_t) output - output_decrement);
      input += 2;
    }
    output_decrement += 1 * sizeof(float);
    if (n & (1 * sizeof(float))) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      float vw = *w++;
      intptr_t diff = *dmap++;
      float vi0 = input[0];
      size_t c = output_channels;
      do {
        uint32_t nnz = *nnzmap++;
        float vacc0 = vw;
        vw = *w++;
        if XNN_LIKELY(nnz != 0) {
          do {
            vacc0 += vi0 * vw;
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);

            diff = *dmap++;
            vw = *w++;
            vi0 = input[0];
          } while (--nnz != 0);
        }
        float vout0 = math_min_f32(vacc0, vmax);
        vout0 = math_max_f32(vout0, vmin);
        output[0] = vout0;
        output = (float*restrict) ((uintptr_t) output + batch_size);
      } while (--c != 0);
      const size_t output_decrement = batch_size * output_channels - 1 * sizeof(float);
      output = (float*restrict) ((uintptr_t) output - output_decrement);
      input += 1;
    }
  }
}
