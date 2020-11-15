// Auto-generated file. Do not edit!
//   Template: src/f32-spmm/neon-blocked.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/spmm.h>


void xnn_f32_spmm_minmax_ukernel_16x4__neonfma(
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

  const float32x4_t vmin = vld1q_dup_f32(&params->scalar.min);
  const float32x4_t vmax = vld1q_dup_f32(&params->scalar.max);
  size_t output_decrement = batch_size * output_channels - 16 * sizeof(float);
  size_t n = batch_size;
  while XNN_LIKELY(n >= 16 * sizeof(float)) {
    const float*restrict w = weights;
    const int32_t* dmap = widx_dmap;
    const uint32_t* nnzmap = nidx_nnzmap;
    size_t c = output_channels;
    while (c >= 4) {
      uint32_t nnz = *nnzmap++;
      float32x4_t vacc0123c0 = vld1q_dup_f32(w); w += 1;
      float32x4_t vacc4567c0 = vacc0123c0;
      float32x4_t vacc89ABc0 = vacc0123c0;
      float32x4_t vaccCDEFc0 = vacc0123c0;
      float32x4_t vacc0123c1 = vld1q_dup_f32(w); w += 1;
      float32x4_t vacc4567c1 = vacc0123c1;
      float32x4_t vacc89ABc1 = vacc0123c1;
      float32x4_t vaccCDEFc1 = vacc0123c1;
      float32x4_t vacc0123c2 = vld1q_dup_f32(w); w += 1;
      float32x4_t vacc4567c2 = vacc0123c2;
      float32x4_t vacc89ABc2 = vacc0123c2;
      float32x4_t vaccCDEFc2 = vacc0123c2;
      float32x4_t vacc0123c3 = vld1q_dup_f32(w); w += 1;
      float32x4_t vacc4567c3 = vacc0123c3;
      float32x4_t vacc89ABc3 = vacc0123c3;
      float32x4_t vaccCDEFc3 = vacc0123c3;
      if XNN_LIKELY(nnz != 0) {
        do {
          const intptr_t diff = *dmap++;
          const float32x4_t vi0123 = vld1q_f32(input);
          const float32x4_t vi4567 = vld1q_f32(input + 4);
          const float32x4_t vi89AB = vld1q_f32(input + 8);
          const float32x4_t viCDEF = vld1q_f32(input + 12);
          input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
          __builtin_prefetch(input + 16);
          const float32x4_t vw = vld1q_f32(w); w += 4;
          __builtin_prefetch(w + 32);
          vacc0123c0 = vfmaq_laneq_f32(vacc0123c0, vi0123, vw, 0);
          vacc4567c0 = vfmaq_laneq_f32(vacc4567c0, vi4567, vw, 0);
          vacc89ABc0 = vfmaq_laneq_f32(vacc89ABc0, vi89AB, vw, 0);
          vaccCDEFc0 = vfmaq_laneq_f32(vaccCDEFc0, viCDEF, vw, 0);
          vacc0123c1 = vfmaq_laneq_f32(vacc0123c1, vi0123, vw, 1);
          vacc4567c1 = vfmaq_laneq_f32(vacc4567c1, vi4567, vw, 1);
          vacc89ABc1 = vfmaq_laneq_f32(vacc89ABc1, vi89AB, vw, 1);
          vaccCDEFc1 = vfmaq_laneq_f32(vaccCDEFc1, viCDEF, vw, 1);
          vacc0123c2 = vfmaq_laneq_f32(vacc0123c2, vi0123, vw, 2);
          vacc4567c2 = vfmaq_laneq_f32(vacc4567c2, vi4567, vw, 2);
          vacc89ABc2 = vfmaq_laneq_f32(vacc89ABc2, vi89AB, vw, 2);
          vaccCDEFc2 = vfmaq_laneq_f32(vaccCDEFc2, viCDEF, vw, 2);
          vacc0123c3 = vfmaq_laneq_f32(vacc0123c3, vi0123, vw, 3);
          vacc4567c3 = vfmaq_laneq_f32(vacc4567c3, vi4567, vw, 3);
          vacc89ABc3 = vfmaq_laneq_f32(vacc89ABc3, vi89AB, vw, 3);
          vaccCDEFc3 = vfmaq_laneq_f32(vaccCDEFc3, viCDEF, vw, 3);
        } while (--nnz != 0);
      }
      float32x4_t vout0123c0 = vminq_f32(vacc0123c0, vmax);
      float32x4_t vout4567c0 = vminq_f32(vacc4567c0, vmax);
      float32x4_t vout89ABc0 = vminq_f32(vacc89ABc0, vmax);
      float32x4_t voutCDEFc0 = vminq_f32(vaccCDEFc0, vmax);
      float32x4_t vout0123c1 = vminq_f32(vacc0123c1, vmax);
      float32x4_t vout4567c1 = vminq_f32(vacc4567c1, vmax);
      float32x4_t vout89ABc1 = vminq_f32(vacc89ABc1, vmax);
      float32x4_t voutCDEFc1 = vminq_f32(vaccCDEFc1, vmax);
      float32x4_t vout0123c2 = vminq_f32(vacc0123c2, vmax);
      float32x4_t vout4567c2 = vminq_f32(vacc4567c2, vmax);
      float32x4_t vout89ABc2 = vminq_f32(vacc89ABc2, vmax);
      float32x4_t voutCDEFc2 = vminq_f32(vaccCDEFc2, vmax);
      float32x4_t vout0123c3 = vminq_f32(vacc0123c3, vmax);
      float32x4_t vout4567c3 = vminq_f32(vacc4567c3, vmax);
      float32x4_t vout89ABc3 = vminq_f32(vacc89ABc3, vmax);
      float32x4_t voutCDEFc3 = vminq_f32(vaccCDEFc3, vmax);

      vout0123c0 = vmaxq_f32(vout0123c0, vmin);
      vout4567c0 = vmaxq_f32(vout4567c0, vmin);
      vout89ABc0 = vmaxq_f32(vout89ABc0, vmin);
      voutCDEFc0 = vmaxq_f32(voutCDEFc0, vmin);
      vout0123c1 = vmaxq_f32(vout0123c1, vmin);
      vout4567c1 = vmaxq_f32(vout4567c1, vmin);
      vout89ABc1 = vmaxq_f32(vout89ABc1, vmin);
      voutCDEFc1 = vmaxq_f32(voutCDEFc1, vmin);
      vout0123c2 = vmaxq_f32(vout0123c2, vmin);
      vout4567c2 = vmaxq_f32(vout4567c2, vmin);
      vout89ABc2 = vmaxq_f32(vout89ABc2, vmin);
      voutCDEFc2 = vmaxq_f32(voutCDEFc2, vmin);
      vout0123c3 = vmaxq_f32(vout0123c3, vmin);
      vout4567c3 = vmaxq_f32(vout4567c3, vmin);
      vout89ABc3 = vmaxq_f32(vout89ABc3, vmin);
      voutCDEFc3 = vmaxq_f32(voutCDEFc3, vmin);

      vst1q_f32(output + 0, vout0123c0);
      vst1q_f32(output + 4, vout4567c0);
      vst1q_f32(output + 8, vout89ABc0);
      vst1q_f32(output + 12, voutCDEFc0);
      output = (float*restrict) ((uintptr_t) output + batch_size);
      vst1q_f32(output + 0, vout0123c1);
      vst1q_f32(output + 4, vout4567c1);
      vst1q_f32(output + 8, vout89ABc1);
      vst1q_f32(output + 12, voutCDEFc1);
      output = (float*restrict) ((uintptr_t) output + batch_size);
      vst1q_f32(output + 0, vout0123c2);
      vst1q_f32(output + 4, vout4567c2);
      vst1q_f32(output + 8, vout89ABc2);
      vst1q_f32(output + 12, voutCDEFc2);
      output = (float*restrict) ((uintptr_t) output + batch_size);
      vst1q_f32(output + 0, vout0123c3);
      vst1q_f32(output + 4, vout4567c3);
      vst1q_f32(output + 8, vout89ABc3);
      vst1q_f32(output + 12, voutCDEFc3);
      output = (float*restrict) ((uintptr_t) output + batch_size);
      c -= 4;
    }

    // clean up loop, fall back to nr=1
    if XNN_UNLIKELY(c != 0) {
      do {
        uint32_t nnz = *nnzmap++;
        float32x4_t vacc0123 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc4567 = vacc0123;
        float32x4_t vacc89AB = vacc0123;
        float32x4_t vaccCDEF = vacc0123;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float32x4_t vi0123 = vld1q_f32(input);
            const float32x4_t vi4567 = vld1q_f32(input + 4);
            const float32x4_t vi89AB = vld1q_f32(input + 8);
            const float32x4_t viCDEF = vld1q_f32(input + 12);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            __builtin_prefetch(input + 16);
            const float32x4_t vw = vld1q_dup_f32(w); w += 1;
            __builtin_prefetch(w + 32);
            vacc0123 = vfmaq_f32(vacc0123, vi0123, vw);
            vacc4567 = vfmaq_f32(vacc4567, vi4567, vw);
            vacc89AB = vfmaq_f32(vacc89AB, vi89AB, vw);
            vaccCDEF = vfmaq_f32(vaccCDEF, viCDEF, vw);
          } while (--nnz != 0);
        }
        float32x4_t vout0123 = vminq_f32(vacc0123, vmax);
        float32x4_t vout4567 = vminq_f32(vacc4567, vmax);
        float32x4_t vout89AB = vminq_f32(vacc89AB, vmax);
        float32x4_t voutCDEF = vminq_f32(vaccCDEF, vmax);

        vout0123 = vmaxq_f32(vout0123, vmin);
        vout4567 = vmaxq_f32(vout4567, vmin);
        vout89AB = vmaxq_f32(vout89AB, vmin);
        voutCDEF = vmaxq_f32(voutCDEF, vmin);

        vst1q_f32(output + 0, vout0123);
        vst1q_f32(output + 4, vout4567);
        vst1q_f32(output + 8, vout89AB);
        vst1q_f32(output + 12, voutCDEF);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        c -= 1;
      } while (c != 0);
    }
    output = (float*restrict) ((uintptr_t) output - output_decrement);
    input += 16;
    n -= 16 * sizeof(float);
  }
  if XNN_UNLIKELY(n != 0) {
    output_decrement += 8 * sizeof(float);
    if (n & (8 * sizeof(float))) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      while (c >= 4) {
        uint32_t nnz = *nnzmap++;
        float32x4_t vacc0123c0 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc4567c0 = vacc0123c0;
        float32x4_t vacc0123c1 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc4567c1 = vacc0123c1;
        float32x4_t vacc0123c2 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc4567c2 = vacc0123c2;
        float32x4_t vacc0123c3 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc4567c3 = vacc0123c3;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float32x4_t vi0123 = vld1q_f32(input);
            const float32x4_t vi4567 = vld1q_f32(input + 4);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const float32x4_t vw = vld1q_f32(w); w += 4;

            vacc0123c0 = vfmaq_laneq_f32(vacc0123c0, vi0123, vw, 0);
            vacc4567c0 = vfmaq_laneq_f32(vacc4567c0, vi4567, vw, 0);
            vacc0123c1 = vfmaq_laneq_f32(vacc0123c1, vi0123, vw, 1);
            vacc4567c1 = vfmaq_laneq_f32(vacc4567c1, vi4567, vw, 1);
            vacc0123c2 = vfmaq_laneq_f32(vacc0123c2, vi0123, vw, 2);
            vacc4567c2 = vfmaq_laneq_f32(vacc4567c2, vi4567, vw, 2);
            vacc0123c3 = vfmaq_laneq_f32(vacc0123c3, vi0123, vw, 3);
            vacc4567c3 = vfmaq_laneq_f32(vacc4567c3, vi4567, vw, 3);
          } while (--nnz != 0);
        }
        float32x4_t vout0123c0 = vminq_f32(vacc0123c0, vmax);
        float32x4_t vout4567c0 = vminq_f32(vacc4567c0, vmax);
        float32x4_t vout0123c1 = vminq_f32(vacc0123c1, vmax);
        float32x4_t vout4567c1 = vminq_f32(vacc4567c1, vmax);
        float32x4_t vout0123c2 = vminq_f32(vacc0123c2, vmax);
        float32x4_t vout4567c2 = vminq_f32(vacc4567c2, vmax);
        float32x4_t vout0123c3 = vminq_f32(vacc0123c3, vmax);
        float32x4_t vout4567c3 = vminq_f32(vacc4567c3, vmax);

        vout0123c0 = vmaxq_f32(vout0123c0, vmin);
        vout4567c0 = vmaxq_f32(vout4567c0, vmin);
        vout0123c1 = vmaxq_f32(vout0123c1, vmin);
        vout4567c1 = vmaxq_f32(vout4567c1, vmin);
        vout0123c2 = vmaxq_f32(vout0123c2, vmin);
        vout4567c2 = vmaxq_f32(vout4567c2, vmin);
        vout0123c3 = vmaxq_f32(vout0123c3, vmin);
        vout4567c3 = vmaxq_f32(vout4567c3, vmin);

        vst1q_f32(output + 0, vout0123c0);
        vst1q_f32(output + 4, vout4567c0);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1q_f32(output + 0, vout0123c1);
        vst1q_f32(output + 4, vout4567c1);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1q_f32(output + 0, vout0123c2);
        vst1q_f32(output + 4, vout4567c2);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1q_f32(output + 0, vout0123c3);
        vst1q_f32(output + 4, vout4567c3);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        c -= 4;
      }

      // clean up loop, fall back to nr=1
      if XNN_UNLIKELY(c != 0) {
        do {
          uint32_t nnz = *nnzmap++;
          float32x4_t vacc0123 = vld1q_dup_f32(w); w += 1;
          float32x4_t vacc4567 = vacc0123;
          if XNN_LIKELY(nnz != 0) {
            do {
              const intptr_t diff = *dmap++;
              const float32x4_t vi0123 = vld1q_f32(input);
              const float32x4_t vi4567 = vld1q_f32(input + 4);
              input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
              const float32x4_t vw = vld1q_dup_f32(w); w += 1;
              vacc0123 = vfmaq_f32(vacc0123, vi0123, vw);
              vacc4567 = vfmaq_f32(vacc4567, vi4567, vw);
            } while (--nnz != 0);
          }
          float32x4_t vout0123 = vminq_f32(vacc0123, vmax);
          float32x4_t vout4567 = vminq_f32(vacc4567, vmax);

          vout0123 = vmaxq_f32(vout0123, vmin);
          vout4567 = vmaxq_f32(vout4567, vmin);

          vst1q_f32(output + 0, vout0123);
          vst1q_f32(output + 4, vout4567);
          output = (float*restrict) ((uintptr_t) output + batch_size);
          c -= 1;
        } while (c != 0);
      }
      output = (float*restrict) ((uintptr_t) output - output_decrement);
      input += 8;
    }
    output_decrement += 4 * sizeof(float);
    if (n & (4 * sizeof(float))) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      while (c >= 4) {
        uint32_t nnz = *nnzmap++;
        float32x4_t vacc0123c0 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc0123c1 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc0123c2 = vld1q_dup_f32(w); w += 1;
        float32x4_t vacc0123c3 = vld1q_dup_f32(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float32x4_t vi0123 = vld1q_f32(input);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const float32x4_t vw = vld1q_f32(w); w += 4;

            vacc0123c0 = vfmaq_laneq_f32(vacc0123c0, vi0123, vw, 0);
            vacc0123c1 = vfmaq_laneq_f32(vacc0123c1, vi0123, vw, 1);
            vacc0123c2 = vfmaq_laneq_f32(vacc0123c2, vi0123, vw, 2);
            vacc0123c3 = vfmaq_laneq_f32(vacc0123c3, vi0123, vw, 3);
          } while (--nnz != 0);
        }
        float32x4_t vout0123c0 = vminq_f32(vacc0123c0, vmax);
        float32x4_t vout0123c1 = vminq_f32(vacc0123c1, vmax);
        float32x4_t vout0123c2 = vminq_f32(vacc0123c2, vmax);
        float32x4_t vout0123c3 = vminq_f32(vacc0123c3, vmax);

        vout0123c0 = vmaxq_f32(vout0123c0, vmin);
        vout0123c1 = vmaxq_f32(vout0123c1, vmin);
        vout0123c2 = vmaxq_f32(vout0123c2, vmin);
        vout0123c3 = vmaxq_f32(vout0123c3, vmin);

        vst1q_f32(output + 0, vout0123c0);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1q_f32(output + 0, vout0123c1);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1q_f32(output + 0, vout0123c2);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1q_f32(output + 0, vout0123c3);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        c -= 4;
      }

      // clean up loop, fall back to nr=1
      if XNN_UNLIKELY(c != 0) {
        do {
          uint32_t nnz = *nnzmap++;
          float32x4_t vacc0123 = vld1q_dup_f32(w); w += 1;
          if XNN_LIKELY(nnz != 0) {
            do {
              const intptr_t diff = *dmap++;
              const float32x4_t vi0123 = vld1q_f32(input);
              input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
              const float32x4_t vw = vld1q_dup_f32(w); w += 1;
              vacc0123 = vfmaq_f32(vacc0123, vi0123, vw);
            } while (--nnz != 0);
          }
          float32x4_t vout0123 = vminq_f32(vacc0123, vmax);

          vout0123 = vmaxq_f32(vout0123, vmin);

          vst1q_f32(output + 0, vout0123);
          output = (float*restrict) ((uintptr_t) output + batch_size);
          c -= 1;
        } while (c != 0);
      }
      output = (float*restrict) ((uintptr_t) output - output_decrement);
      input += 4;
    }
    output_decrement += 2 * sizeof(float);
    if (n & (2 * sizeof(float))) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      while (c >= 4) {
        uint32_t nnz = *nnzmap++;
        float32x2_t vacc01c0 = vld1_dup_f32(w); w += 1;
        float32x2_t vacc01c1 = vld1_dup_f32(w); w += 1;
        float32x2_t vacc01c2 = vld1_dup_f32(w); w += 1;
        float32x2_t vacc01c3 = vld1_dup_f32(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float32x2_t vi01 = vld1_f32(input);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const float32x4_t vw = vld1q_f32(w); w += 4;

            vacc01c0 = vfma_laneq_f32(vacc01c0, vi01, vw, 0);
            vacc01c1 = vfma_laneq_f32(vacc01c1, vi01, vw, 1);
            vacc01c2 = vfma_laneq_f32(vacc01c2, vi01, vw, 2);
            vacc01c3 = vfma_laneq_f32(vacc01c3, vi01, vw, 3);
          } while (--nnz != 0);
        }
        float32x2_t vout01c0 = vmin_f32(vacc01c0, vget_low_f32(vmax));
        float32x2_t vout01c1 = vmin_f32(vacc01c1, vget_low_f32(vmax));
        float32x2_t vout01c2 = vmin_f32(vacc01c2, vget_low_f32(vmax));
        float32x2_t vout01c3 = vmin_f32(vacc01c3, vget_low_f32(vmax));

        vout01c0 = vmax_f32(vout01c0, vget_low_f32(vmin));
        vout01c1 = vmax_f32(vout01c1, vget_low_f32(vmin));
        vout01c2 = vmax_f32(vout01c2, vget_low_f32(vmin));
        vout01c3 = vmax_f32(vout01c3, vget_low_f32(vmin));

        vst1_f32(output + 0, vout01c0);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1_f32(output + 0, vout01c1);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1_f32(output + 0, vout01c2);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1_f32(output + 0, vout01c3);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        c -= 4;
      }

      // clean up loop, fall back to nr=1
      if XNN_UNLIKELY(c != 0) {
        do {
          uint32_t nnz = *nnzmap++;
          float32x2_t vacc01 = vld1_dup_f32(w); w += 1;
          if XNN_LIKELY(nnz != 0) {
            do {
              const intptr_t diff = *dmap++;
              const float32x2_t vi01 = vld1_f32(input);
              input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
              const float32x2_t vw = vld1_dup_f32(w); w += 1;
              vacc01 = vfma_f32(vacc01, vi01, vw);
            } while (--nnz != 0);
          }
          float32x2_t vout01 = vmin_f32(vacc01, vget_low_f32(vmax));
          vout01 = vmax_f32(vout01, vget_low_f32(vmin));

          vst1_f32(output, vout01);
          output = (float*restrict) ((uintptr_t) output + batch_size);
          c -= 1;
        } while (c != 0);
      }
      output = (float*restrict) ((uintptr_t) output - output_decrement);
      input += 2;
    }
    output_decrement += 1 * sizeof(float);
    if (n & (1 * sizeof(float))) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      while (c >= 4) {
        uint32_t nnz = *nnzmap++;
        float32x2_t vacc0c0 = vld1_dup_f32(w); w += 1;
        float32x2_t vacc0c1 = vld1_dup_f32(w); w += 1;
        float32x2_t vacc0c2 = vld1_dup_f32(w); w += 1;
        float32x2_t vacc0c3 = vld1_dup_f32(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float32x2_t vi0 = vld1_dup_f32(input);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const float32x4_t vw = vld1q_f32(w); w += 4;

            vacc0c0 = vfma_laneq_f32(vacc0c0, vi0, vw, 0);
            vacc0c1 = vfma_laneq_f32(vacc0c1, vi0, vw, 1);
            vacc0c2 = vfma_laneq_f32(vacc0c2, vi0, vw, 2);
            vacc0c3 = vfma_laneq_f32(vacc0c3, vi0, vw, 3);
          } while (--nnz != 0);
        }
        float32x2_t vout0c0 = vmin_f32(vacc0c0, vget_low_f32(vmax));
        float32x2_t vout0c1 = vmin_f32(vacc0c1, vget_low_f32(vmax));
        float32x2_t vout0c2 = vmin_f32(vacc0c2, vget_low_f32(vmax));
        float32x2_t vout0c3 = vmin_f32(vacc0c3, vget_low_f32(vmax));

        vout0c0 = vmax_f32(vout0c0, vget_low_f32(vmin));
        vout0c1 = vmax_f32(vout0c1, vget_low_f32(vmin));
        vout0c2 = vmax_f32(vout0c2, vget_low_f32(vmin));
        vout0c3 = vmax_f32(vout0c3, vget_low_f32(vmin));

        vst1_lane_f32(output + 0, vout0c0, 0);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1_lane_f32(output + 0, vout0c1, 0);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1_lane_f32(output + 0, vout0c2, 0);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        vst1_lane_f32(output + 0, vout0c3, 0);
        output = (float*restrict) ((uintptr_t) output + batch_size);
        c -= 4;
      }

      // clean up loop, fall back to nr=1
      if XNN_UNLIKELY(c != 0) {
        do {
          uint32_t nnz = *nnzmap++;
          float32x2_t vacc0 = vld1_dup_f32(w); w += 1;
          if XNN_LIKELY(nnz != 0) {
            do {
              const intptr_t diff = *dmap++;
              const float32x2_t vi0 = vld1_dup_f32(input);
              input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
              const float32x2_t vw = vld1_dup_f32(w); w += 1;
              vacc0 = vfma_f32(vacc0, vi0, vw);
            } while (--nnz != 0);
          }
          float32x2_t vout0 = vmin_f32(vacc0, vget_low_f32(vmax));
          vout0 = vmax_f32(vout0, vget_low_f32(vmin));

          vst1_lane_f32(output, vout0, 1);
          output = (float*restrict) ((uintptr_t) output + batch_size);
          c -= 1;
        } while (c != 0);
      }
      output = (float*restrict) ((uintptr_t) output - output_decrement);
      input += 1;
    }
    }
}
