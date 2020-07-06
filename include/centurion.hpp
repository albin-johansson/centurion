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

#include "area.hpp"
#include "audio_device_event.hpp"
#include "battery.hpp"
#include "blend_mode.hpp"
#include "button_state.hpp"
#include "centurion_api.hpp"
#include "centurion_cfg.hpp"
#include "centurion_exception.hpp"
#include "centurion_utils.hpp"
#include "color.hpp"
#include "colors.hpp"
#include "common_event.hpp"
#include "controller_axis_event.hpp"
#include "controller_button_event.hpp"
#include "controller_device_event.hpp"
#include "cpu.hpp"
#include "cursor.hpp"
#include "dollar_gesture_event.hpp"
#include "drop_event.hpp"
#include "error.hpp"
#include "event.hpp"
#include "event_type.hpp"
#include "font.hpp"
#include "game_controller.hpp"
#include "hints.hpp"
#include "joy_axis_event.hpp"
#include "joy_ball_event.hpp"
#include "joy_button_event.hpp"
#include "joy_device_event.hpp"
#include "joy_hat_event.hpp"
#include "key.hpp"
#include "key_modifier.hpp"
#include "key_state.hpp"
#include "keyboard_event.hpp"
#include "log.hpp"
#include "message_box.hpp"
#include "mouse_button.hpp"
#include "mouse_button_event.hpp"
#include "mouse_motion_event.hpp"
#include "mouse_state.hpp"
#include "mouse_wheel_event.hpp"
#include "multi_gesture_event.hpp"
#include "music.hpp"
#include "paths.hpp"
#include "pixel_format.hpp"
#include "platform.hpp"
#include "point.hpp"
#include "quit_event.hpp"
#include "ram.hpp"
#include "rect.hpp"
#include "renderer.hpp"
#include "screen.hpp"
#include "sound_effect.hpp"
#include "surface.hpp"
#include "syswm_event.hpp"
#include "text_editing_event.hpp"
#include "text_input_event.hpp"
#include "texture.hpp"
#include "texture_loader.hpp"
#include "timer.hpp"
#include "touch.hpp"
#include "touch_finger_event.hpp"
#include "window.hpp"
#include "window_event.hpp"

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
