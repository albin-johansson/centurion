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
 * @file centurion.hpp
 *
 * @brief The main header file for the library.
 *
 * @details Provides the `library` and `config` classes, which are related to
 * the initialization of the library.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

/**
 * @defgroup core Core
 *
 * @brief Contains entities considered to be fundamental for the library.
 */

#ifndef CENTURION_HEADER
#define CENTURION_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <optional>

#include "centurion_api.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * @namespace centurion
 *
 * @ingroup core
 *
 * @brief The top-level namespace that all components of the library reside in.
 */
namespace cen {

/**
 * @struct config
 *
 * @ingroup core
 *
 * @brief Used to specify how the library is initialized.
 *
 * @details All fields are initialized to the default values used by the
 * library.
 *
 * @since 4.0.0
 *
 * @var config::initCore
 * Indicates whether or not the SDL2 core is initialized.
 *
 * @var config::initImage
 * Indicates whether or not SDL2_image is initialized.
 *
 * @var config::initMixer
 * Indicates whether or not SDL2_mixer is initialized.
 *
 * @var config::initTTF
 * Indicates whether or not SDL2_ttf is initialized.
 *
 * @var config::coreFlags
 * Flags passed on to `SDL_Init()`, if @ref config.initCore is `true`.
 *
 * @var config::imageFlags
 * Flags passed on to `IMG_Init()`, if @ref config.initImage is
 * `true`.
 *
 * @var config::mixerFlags
 * Flags passed on to `Mix_Init()`, if @ref config.initMixer is
 * `true`.
 *
 * @var config::mixerFreq
 * The frequency used by SDL2_mixer, if @ref config.initMixer is
 * `true`.
 *
 * @var config::mixerFormat
 * The format used by SDL2_mixer, if @ref config.initMixer is `true`.
 *
 * @var config::mixerChannels
 * The amount of channels used by SDL2_mixer, if @ref config.initMixer
 * is `true`.
 *
 * @var config::mixerChunkSize
 * The chunk size used by SDL2_mixer, if @ref config.initMixer is
 * `true`.
 *
 * @headerfile centurion.hpp
 */
struct config final
{
  bool initCore = true;
  bool initImage = true;
  bool initMixer = true;
  bool initTTF = true;

  u32 coreFlags = SDL_INIT_EVERYTHING;

  int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;

  int mixerFlags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID |
                   MIX_INIT_MOD | MIX_INIT_OPUS;

  int mixerFreq = MIX_DEFAULT_FREQUENCY;
  u16 mixerFormat = MIX_DEFAULT_FORMAT;
  int mixerChannels = MIX_DEFAULT_CHANNELS;
  int mixerChunkSize = 4096;
};

/**
 * @class library
 *
 * @ingroup core
 *
 * @brief Used to initialize and de-initialize the library.
 *
 * @note The signature of the main-method must be `ìnt(int, char**)` when
 * using the Centurion library!
 *
 * @since 3.0.0
 *
 * @headerfile centurion.hpp
 */
class library final
{
 public:
  /**
   * @brief Initializes the library.
   *
   * @pre there mustn't exist any other instances of this class at the time of
   * invocation of this constructor.
   *
   * @throws sdl_error if the core SDL2 library can't be initialized.
   * @throws img_error if the SDL2_image library can't be initialized.
   * @throws ttf_error if the SDL2_ttf library can't be initialized.
   * @throws mix_error if the SDL2_mixer library can't be initialized.
   *
   * @since 3.0.0
   */
  CENTURION_API
  library();

  /**
   * @brief Initializes the library according to the supplied configuration.
   *
   * @pre there mustn't exist any other instances of this class at the time of
   * invocation of this constructor.
   *
   * @param cfg the configuration spec, determines what gets initialized.
   *
   * @throws sdl_error if the core SDL2 library can't be initialized.
   * @throws img_error if the SDL2_image library can't be initialized.
   * @throws ttf_error if the SDL2_ttf library can't be initialized.
   * @throws mix_error if the SDL2_mixer library can't be initialized.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit library(const config& cfg);

  library(const library&) = delete;

  library(library&&) = delete;

  auto operator=(const library&) -> library& = delete;

  auto operator=(library&&) -> library& = delete;

 private:
  class sdl final
  {
   public:
    explicit sdl(u32 flags);

    CENTURION_API
    ~sdl() noexcept;
  };

  class sdl_ttf final
  {
   public:
    explicit sdl_ttf();

    CENTURION_API
    ~sdl_ttf() noexcept;
  };

  class sdl_mixer final
  {
   public:
    sdl_mixer(int flags, int freq, u16 format, int nChannels, int chunkSize);

    CENTURION_API
    ~sdl_mixer() noexcept;
  };

  class sdl_image final
  {
   public:
    explicit sdl_image(int flags);

    CENTURION_API
    ~sdl_image() noexcept;
  };

  config m_cfg{};
  std::optional<sdl> m_sdl{};
  std::optional<sdl_image> m_img{};
  std::optional<sdl_ttf> m_ttf{};
  std::optional<sdl_mixer> m_mixer{};

  void init();
};

/**
 * @brief Returns the compile-time version of SDL2_ttf that is being used.
 *
 * @return the compile-time version of SDL2_ttf that is being used.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto ttf_version() noexcept -> SDL_version;

}  // namespace cen

#endif  // CENTURION_HEADER
