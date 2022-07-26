/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_INITIALIZATION_HPP_
#define CENTURION_INITIALIZATION_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional

#include "common.hpp"
#include "features.hpp"

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

namespace cen {

/// Used to specify how the core SDL library is initialized.
struct sdl_cfg final
{
  uint32 flags{SDL_INIT_EVERYTHING};
};

/**
 * Used to load and subsequently unload the core SDL library.
 *
 * \see img
 * \see mix
 * \see ttf
 */
class sdl final
{
 public:
  CENTURION_NODISCARD_CTOR explicit sdl(const sdl_cfg& cfg = {})
  {
    if (SDL_Init(cfg.flags) < 0) {
      throw sdl_error{};
    }
  }

  ~sdl() noexcept { SDL_Quit(); }
};

#ifndef CENTURION_NO_SDL_IMAGE

/// Used to specify how the SDL_image library is initialized.
struct img_cfg final
{
  int flags{IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP};
};

/// Used to load and subsequently unload the SDL_image library.
class img final
{
 public:
  CENTURION_NODISCARD_CTOR explicit img(const img_cfg& cfg = {})
  {
    if (!IMG_Init(cfg.flags)) {
      throw img_error{};
    }
  }

  ~img() noexcept { IMG_Quit(); }
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

/// Used to specify how the SDL_mixer library is initialized.
struct mix_cfg final
{
  int flags{MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID | MIX_INIT_MOD |
            MIX_INIT_OPUS};
  int frequency{MIX_DEFAULT_FREQUENCY};
  uint16 format{MIX_DEFAULT_FORMAT};
  int channels{MIX_DEFAULT_CHANNELS};
  int chunk_size{4096};
};

/// Used to load and subsequently unload the SDL_mixer library.
class mix final
{
 public:
  CENTURION_NODISCARD_CTOR explicit mix(const mix_cfg& cfg = {})
  {
    if (!Mix_Init(cfg.flags)) {
      throw mix_error{};
    }

    if (Mix_OpenAudio(cfg.frequency, cfg.format, cfg.channels, cfg.chunk_size) == -1) {
      throw mix_error{};
    }
  }

  ~mix() noexcept
  {
    Mix_CloseAudio();
    Mix_Quit();
  }
};

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

/// Used to load and subsequently unload the SDL_ttf library.
class ttf final
{
 public:
  CENTURION_NODISCARD_CTOR ttf()
  {
    if (TTF_Init() == -1) {
      throw ttf_error{};
    }
  }

  ~ttf() noexcept { TTF_Quit(); }
};

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen

#endif  // CENTURION_INITIALIZATION_HPP_
