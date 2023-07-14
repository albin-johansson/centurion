/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_INITIALIZATION_SDL_MIXER_HPP_
#define CENTURION_INITIALIZATION_SDL_MIXER_HPP_

#if CEN_USE_SDL_MIXER

#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>

#include <centurion/common/errors.hpp>
#include <centurion/common/macros.hpp>
#include <centurion/common/primitives.hpp>

namespace cen {

struct SDLMixerConfig final {
  int flags {MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID |
             MIX_INIT_OPUS | MIX_INIT_WAVPACK};
  int frequency {MIX_DEFAULT_FREQUENCY};
  uint16 format {MIX_DEFAULT_FORMAT};
  int channels {MIX_DEFAULT_CHANNELS};
  int chunk_size {4096};
};

class SDLMixer final {
 public:
  CEN_CANNOT_COPY(SDLMixer);
  CEN_CANNOT_MOVE(SDLMixer);

  [[nodiscard]] explicit SDLMixer(const SDLMixerConfig& cfg = {})
  {
    if (Mix_Init(cfg.flags) == 0) {
      throw SDLMixerError {};
    }

    if (Mix_OpenAudio(cfg.frequency, cfg.format, cfg.channels, cfg.chunk_size) != 0) {
      throw SDLMixerError {};
    }
  }

  ~SDLMixer() noexcept
  {
    Mix_CloseAudio();
    Mix_Quit();
  }
};

}  // namespace cen

#endif  // CEN_USE_SDL_MIXER
#endif  // CENTURION_INITIALIZATION_SDL_MIXER_HPP_
