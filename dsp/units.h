// Copyright 2014 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Conversion from semitones to frequency ratio.

#ifndef STMLIB_DSP_UNITS_H_
#define STMLIB_DSP_UNITS_H_

#include "stmlib/dsp/dsp.h"
#include "stmlib/stmlib.h"
#include "synth/phase_step_table.hh"

namespace stmlib {

inline float SemitonesToRatio(float semitones) {
  const auto t = ToySynth::Synth::PhaseStep::semitones_to_ratio(
      ToySynth::Fixed::from_float(semitones / 128));
  return t / static_cast<float>(1u << 21);
}

inline float SemitonesToRatioSafe(float semitones) {
  float scale = 1.0f;
  while (semitones > 120.0f) {
    semitones -= 120.0f;
    scale *= 1024.0f;
  }
  while (semitones < -120.0f) {
    semitones += 120.0f;
    scale *= 1.0f / 1024.0f;
  }
  return scale * SemitonesToRatio(semitones);
}

inline float Exp2Safe(float value) {
  return SemitonesToRatioSafe(value * 12.0f);
}

} // namespace stmlib

#endif // STMLIB_DSP_UNITS_H_
