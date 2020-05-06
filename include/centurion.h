/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_HEADER
#define CENTURION_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// TODO update this list of includes or simply remove the includes

#include "audio.h"
#include "battery.h"
#include "blend_mode.h"
#include "centurion_api.h"
#include "centurion_cfg.h"
#include "centurion_exception.h"
#include "centurion_utils.h"
#include "color.h"
#include "colors.h"
#include "cpu.h"
#include "cursor.h"
#include "error.h"
#include "font.h"
#include "key_state.h"
#include "log.h"
#include "message_box.h"
#include "mouse_state.h"
#include "music.h"
#include "paths.h"
#include "pixel_format.h"
#include "platform.h"
#include "point.h"
#include "ram.h"
#include "rectangle.h"
#include "renderer.h"
#include "screen.h"
#include "sound_effect.h"
#include "surface.h"
#include "texture.h"
#include "texture_loader.h"
#include "timer.h"
#include "window.h"
#include "window_listener.h"

namespace centurion {

/**
 * The CenturionConfig struct is used to specify how the Centurion
 * library is initialized. All fields are initialized to the default values
 * used by the Centurion library.
 *
 * @since 4.0.0
 */
struct CenturionConfig final {
  bool initCore = true;
  bool initImage = true;
  bool initMixer = true;
  bool initTTF = true;

  Uint32 coreFlags = SDL_INIT_EVERYTHING;

  int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;

  int mixerFlags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID |
                   MIX_INIT_MOD | MIX_INIT_OPUS;

  int mixerFreq = MIX_DEFAULT_FREQUENCY;
  Uint16 mixerFormat = MIX_DEFAULT_FORMAT;
  int mixerChannels = MIX_DEFAULT_CHANNELS;
  int mixerChunkSize = 4096;
};

/**
 * The Centurion class is used to initialize and de-initialize the Centurion
 * library.
 *
 * @since 3.0.0
 */
class Centurion final {
 private:
  CenturionConfig cfg;

  /**
   * Initializes the core SDL2 library.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void init_sdl();

  /**
   * Initializes the SDL2_ttf library.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void init_ttf();

  /**
   * Initializes the SDL2_image library.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void init_img();

  /**
   * Initializes the SDL2_mixer library.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void init_mix();

  CENTURION_API
  void init();

  CENTURION_API
  void close() noexcept;

 public:
  /**
   * Initializes the Centurion library. Do NOT ever create more than one
   * instance of this class, or bad things might happen.
   *
   * @throws CenturionException if any of the SDL libraries can't be loaded.
   * @since 3.0.0
   */
  CENTURION_API
  Centurion();

  /**
   * Initializes the Centurion library according to the supplied configuration.
   * Do NOT ever create more than one instance of this class, or bad things
   * might happen.
   *
   * @param cfg the Centurion configuration, determines what gets initialized.
   * @throws CenturionException if any of the SDL libraries can't be loaded.
   * @since 4.0.0
   */
  CENTURION_API
  explicit Centurion(const CenturionConfig& cfg);

  /**
   * Closes the Centurion library.
   *
   * @since 3.0.0
   */
  CENTURION_API
  ~Centurion() noexcept;

  Centurion(const Centurion&) = delete;

  Centurion(Centurion&&) = delete;

  Centurion& operator=(const Centurion&) = delete;

  Centurion& operator=(Centurion&&) = delete;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "centurion.cpp"
#endif

#endif  // CENTURION_HEADER
