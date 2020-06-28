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

/**
 * @brief The main header file for the library.
 *
 * Provides the declaration of the @link centurion::Centurion @endlink and
 * @link centurion::CenturionConfig @endlink classes, and are related to the
 * initialization of the library. This file also includes all other header
 * files in the library.
 *
 * @file centurion.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_HEADER
#define CENTURION_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "area.h"
#include "audio_device_event.h"
#include "battery.h"
#include "blend_mode.h"
#include "button_state.h"
#include "centurion_api.h"
#include "centurion_cfg.h"
#include "centurion_exception.h"
#include "centurion_utils.h"
#include "color.h"
#include "colors.h"
#include "common_event.h"
#include "controller_axis_event.h"
#include "controller_button_event.h"
#include "controller_device_event.h"
#include "cpu.h"
#include "cursor.h"
#include "dollar_gesture_event.h"
#include "drop_event.h"
#include "error.h"
#include "event.h"
#include "event_type.h"
#include "font.h"
#include "game_controller.h"
#include "hints.h"
#include "joy_axis_event.h"
#include "joy_ball_event.h"
#include "joy_button_event.h"
#include "joy_device_event.h"
#include "joy_hat_event.h"
#include "key.h"
#include "key_modifier.h"
#include "key_state.h"
#include "keyboard_event.h"
#include "log.h"
#include "message_box.h"
#include "mouse_button.h"
#include "mouse_button_event.h"
#include "mouse_motion_event.h"
#include "mouse_state.h"
#include "mouse_wheel_event.h"
#include "multi_gesture_event.h"
#include "music.h"
#include "paths.h"
#include "pixel_format.h"
#include "platform.h"
#include "point.h"
#include "quit_event.h"
#include "ram.h"
#include "rect.h"
#include "renderer.h"
#include "screen.h"
#include "sound_effect.h"
#include "surface.h"
#include "syswm_event.h"
#include "text_editing_event.h"
#include "text_input_event.h"
#include "texture.h"
#include "texture_loader.h"
#include "timer.h"
#include "touch.h"
#include "touch_finger_event.h"
#include "window.h"
#include "window_event.h"

/**
 * @brief The top-level namespace that all components of the library reside in.
 *
 * @namespace centurion
 */
namespace centurion {

/**
 * @brief Used to specify how the library is initialized.
 *
 * All fields are initialized to the default values used by the
 * library.
 *
 * @struct CenturionConfig
 * @headerfile centurion.h
 * @since 4.0.0
 *
 * @var CenturionConfig::initCore
 * Indicates whether or not the SDL2 core is initialized.
 *
 * @var CenturionConfig::initImage
 * Indicates whether or not SDL2_image is initialized.
 *
 * @var CenturionConfig::initMixer
 * Indicates whether or not SDL2_mixer is initialized.
 *
 * @var CenturionConfig::initTTF
 * Indicates whether or not SDL2_ttf is initialized.
 *
 * @var CenturionConfig::coreFlags
 * Flags passed on to `SDL_Init()`, if @ref CenturionConfig.initCore is `true`.
 *
 * @var CenturionConfig::imageFlags
 * Flags passed on to `IMG_Init()`, if @ref CenturionConfig.initImage is `true`.
 *
 * @var CenturionConfig::mixerFlags
 * Flags passed on to `MIX_Init()`, if @ref CenturionConfig.initMixer is `true`.
 *
 * @var CenturionConfig::mixerFreq
 * The frequency used by SDL2_mixer, if @ref CenturionConfig.initMixer is
 * `true`.
 *
 * @var CenturionConfig::mixerFormat
 * The format used by SDL2_mixer, if @ref CenturionConfig.initMixer is `true`.
 *
 * @var CenturionConfig::mixerChannels
 * The amount of channels used by SDL2_mixer, if @ref CenturionConfig.initMixer
 * is `true`.
 *
 * @var CenturionConfig::mixerChunkSize
 * The chunk size used by SDL2_mixer, if @ref CenturionConfig.initMixer is
 * `true`.
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
 * @brief Used to initialize and de-initialize the library.
 * @class Centurion
 * @headerfile centurion.h
 * @since 3.0.0
 *
 * @par Examples
 * This is how you should initialize the library.
 * @code{.cpp}
 * #include <centurion.h>
 *
 * using namespace centurion;
 *
 * int main(int, char**)
 * {
 *   Centurion c;
 *
 *   // The library is now initialized, proceed to using it!
 *
 *   return 0;
 * }
 * @endcode
 * You can also manually configure exactly how the library is initialized, using
 * the @link centurion::CenturionConfig @endlink struct.
 * @code{.cpp}
 * #include <centurion.h>
 *
 * using namespace centurion;
 *
 * int main(int, char**)
 * {
 *   CenturionConfig cfg;
 *   cfg.initMixer = false;
 *   // ...
 *
 *   Centurion c{cfg};
 *
 *   // The library is now initialized, proceed to using it!
 *
 *   return 0;
 * }
 * @endcode
 *
 * | Property              | Value                                |
 * | --------------------- | :----------------------------------- |
 * | Default constructible | Yes                                  |
 * | Movable               | No                                   |
 * | Copyable              | No                                   |
 * | Explicit conversions  | None                                 |
 * | Implicit conversions  | None                                 |
 * | Overloaded operators  | None                                 |
 * | Namespace             | @link ::centurion @endlink           |
 */
class Centurion final {
 public:
  /**
   * Initializes the library.
   *
   * @pre there mustn't exist any other instances of this class at the time of
   * invocation of this constructor.
   *
   * @throws CenturionException if any of the SDL libraries can't be loaded.
   * @since 3.0.0
   */
  CENTURION_API Centurion();

  /**
   * Initializes the library according to the supplied configuration.
   *
   * @pre there mustn't exist any other instances of this class at the time of
   * invocation of this constructor.
   *
   * @param cfg the Centurion configuration, determines what gets initialized.
   * @throws CenturionException if any of the SDL libraries can't be loaded.
   * @since 4.0.0
   */
  CENTURION_API explicit Centurion(const CenturionConfig& cfg);

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

 private:
  CenturionConfig cfg;

  CENTURION_API void init_sdl();

  CENTURION_API void init_ttf();

  CENTURION_API void init_img();

  CENTURION_API void init_mix();

  CENTURION_API void init();

  CENTURION_API void close() noexcept;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "centurion.cpp"
#endif

#endif  // CENTURION_HEADER
