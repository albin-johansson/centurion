/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
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

#pragma once

#include <cstdint>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "centurion_api.h"
#include "blend_mode.h"
#include "bool_converter.h"
#include "centurion_exception.h"
#include "centurion_utils.h"
#include "color.h"
#include "colors.h"
#include "error.h"
#include "font.h"
#include "image.h"
#include "image_generator.h"
#include "key_state.h"
#include "log.h"
#include "message_box.h"
#include "mouse_state.h"
#include "music.h"
#include "paths.h"
#include "point.h"
#include "rectangle.h"
#include "renderer.h"
#include "sound_effect.h"
#include "system.h"
#include "timer.h"
#include "window.h"
#include "window_listener.h"

namespace centurion {

/**
 * The Centurion class is used to initialize and de-initialize the Centurion library.
 *
 * @since 3.0.0
 */
class CENTURION_API Centurion final {
 private:
  static constexpr int img_flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
  static constexpr int mix_flags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID
      | MIX_INIT_MOD | MIX_INIT_OPUS;

  static inline bool wasInit = false;

  /**
   * Initializes the core SDL2 library.
   *
   * @since 3.0.0
   */
  CENTURION_API static void init_sdl();


  /**
   * Initializes the SDL2_ttf library.
   *
   * @since 3.0.0
   */
  CENTURION_API static void init_ttf();

  /**
   * Initializes the SDL2_image library.
   *
   * @since 3.0.0
   */
  CENTURION_API static void init_img();

  /**
   * Initializes the SDL2_mixer library.
   *
   * @since 3.0.0
   */
  CENTURION_API static void init_mix();

  CENTURION_API static void init();

  CENTURION_API static void close() noexcept;

 public:
  /**
   * Initializes the Centurion library. Creating more than one instance of this class is never
   * necessary, but doing so is safe.
   *
   * @throws CenturionException if any of the SDL libraries can't be loaded.
   * @since 3.0.0
   */
  CENTURION_API Centurion();

  /**
   * Closes the Centurion library.
   *
   * @since 3.0.0
   */
  CENTURION_API ~Centurion() noexcept;

  Centurion(const Centurion&) = delete;

  Centurion(Centurion&&) = delete;

  Centurion& operator=(const Centurion&) = delete;

  Centurion& operator=(Centurion&&) = delete;
};

}
