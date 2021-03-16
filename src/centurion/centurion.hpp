/**
 * \defgroup core Core
 * \brief Contains entities considered to be fundamental for the library.
 */

/**
 * \defgroup configuration Configuration
 * \brief Contains the API related to hints/configuration variables.
 */

/**
 * \defgroup event Events
 * \brief Contains entities related to events.
 */

/**
 * \defgroup thread Threads
 * \brief Provides threading utilities for dealing with threads, mutexes, locks,
 * etc.
 */

/**
 * \defgroup input Input
 * \brief Contains components related to input from mice, keyboards,
 * controllers, etc.
 */

/**
 * \defgroup graphics Graphics
 * \brief Contains components related to window-management, rendering, fonts,
 * etc.
 */

/**
 * \defgroup system System
 * \brief Contains various utilities related to system resources.
 */

/**
 * \defgroup compiler Compiler
 * \brief Provides `constexpr` utilities for querying the current compiler.
 * \note There is no guarantee that the compiler checks are mutually exclusive.
 */

/**
 * \defgroup geometry Geometry
 * \brief Contains basic geometric components, used throughout the library.
 */

/**
 * \defgroup audio Audio
 * \brief Contains the audio API, for playing as sound effects and music.
 */

/**
 * \defgroup misc Misc
 * \brief Contains miscellaneous components.
 */

#ifndef CENTURION_CORE_HEADER
#define CENTURION_CORE_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <optional>  // optional

#include "area.hpp"
#include "base_path.hpp"
#include "battery.hpp"
#include "blend_mode.hpp"
#include "button_state.hpp"
#include "byte_order.hpp"
#include "cast.hpp"
#include "centurion_cfg.hpp"
#include "clipboard.hpp"
#include "color.hpp"
#include "condition.hpp"
#include "controller.hpp"
#include "counter.hpp"
#include "cpu.hpp"
#include "cursor.hpp"
#include "czstring.hpp"
#include "event.hpp"
#include "event_dispatcher.hpp"
#include "event_type.hpp"
#include "exception.hpp"
#include "file.hpp"
#include "font.hpp"
#include "font_cache.hpp"
#include "graphics_drivers.hpp"
#include "haptic.hpp"
#include "hints.hpp"
#include "integers.hpp"
#include "joystick.hpp"
#include "key_code.hpp"
#include "key_modifier.hpp"
#include "key_state.hpp"
#include "locale.hpp"
#include "log.hpp"
#include "message_box.hpp"
#include "mouse_button.hpp"
#include "mouse_state.hpp"
#include "music.hpp"
#include "mutex.hpp"
#include "not_null.hpp"
#include "owner.hpp"
#include "pixel_format.hpp"
#include "platform.hpp"
#include "point.hpp"
#include "pref_path.hpp"
#include "ram.hpp"
#include "rect.hpp"
#include "renderer.hpp"
#include "scale_mode.hpp"
#include "scan_code.hpp"
#include "scoped_lock.hpp"
#include "screen.hpp"
#include "sdl_string.hpp"
#include "semaphore.hpp"
#include "sensor.hpp"
#include "shared_object.hpp"
#include "sound_effect.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "texture_access.hpp"
#include "thread.hpp"
#include "time.hpp"
#include "touch.hpp"
#include "try_lock.hpp"
#include "unicode_string.hpp"
#include "vector3.hpp"
#include "window.hpp"
#include "window_utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * \namespace cen
 *
 * \brief The top-level namespace that all components of the library reside in.
 */
namespace cen {

/// \addtogroup core
/// \{

/**
 * \struct config
 *
 * \brief Used to specify how the library is initialized.
 *
 * \details All fields are initialized to the default values used by the
 * library.
 *
 * \since 4.0.0
 *
 * \var config::initCore
 * Indicates whether or not the SDL2 core is initialized.
 *
 * \var config::initImage
 * Indicates whether or not SDL2_image is initialized.
 *
 * \var config::initMixer
 * Indicates whether or not SDL2_mixer is initialized.
 *
 * \var config::initTTF
 * Indicates whether or not SDL2_ttf is initialized.
 *
 * \var config::coreFlags
 * Flags passed on to `SDL_Init()`, if \ref config.initCore is `true`.
 *
 * \var config::imageFlags
 * Flags passed on to `IMG_Init()`, if \ref config.initImage is
 * `true`.
 *
 * \var config::mixerFlags
 * Flags passed on to `Mix_Init()`, if \ref config.initMixer is
 * `true`.
 *
 * \var config::mixerFreq
 * The frequency used by SDL2_mixer, if \ref config.initMixer is
 * `true`.
 *
 * \var config::mixerFormat
 * The format used by SDL2_mixer, if \ref config.initMixer is `true`.
 *
 * \var config::mixerChannels
 * The amount of channels used by SDL2_mixer, if \ref config.initMixer
 * is `true`.
 *
 * \var config::mixerChunkSize
 * The chunk size used by SDL2_mixer, if \ref config.initMixer is
 * `true`.
 *
 * \headerfile centurion.hpp
 */
struct config final
{
  bool initCore{true};
  bool initImage{true};
  bool initMixer{true};
  bool initTTF{true};

  u32 coreFlags{SDL_INIT_EVERYTHING};

  int imageFlags{IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP};

  int mixerFlags{MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID |
                 MIX_INIT_MOD | MIX_INIT_OPUS};

  int mixerFreq{MIX_DEFAULT_FREQUENCY};
  u16 mixerFormat{MIX_DEFAULT_FORMAT};
  int mixerChannels{MIX_DEFAULT_CHANNELS};
  int mixerChunkSize{4096};
};

/**
 * \class library
 *
 * \brief Used to initialize and de-initialize the library.
 *
 * \note The signature of the main-method must be `ìnt(int, char**)` when
 * using the Centurion library!
 *
 * \since 3.0.0
 *
 * \headerfile centurion.hpp
 */
class library final
{
 public:
  /**
   * \brief Initializes the library.
   *
   * \note Make sure to have the `library` instance as a local variable that
   * will outlive the duration of your main program. It's not sufficient to just
   * call the constructor but not store the result as a variable.
   *
   * \pre there mustn't exist any other instances of this class at the time of
   * invocation of this constructor.
   *
   * \throws sdl_error if the core SDL2 library can't be initialized.
   * \throws img_error if the SDL2_image library can't be initialized.
   * \throws ttf_error if the SDL2_ttf library can't be initialized.
   * \throws mix_error if the SDL2_mixer library can't be initialized.
   *
   * \since 3.0.0
   */
  library()
  {
    init();
  }

  /**
   * \brief Initializes the library according to the supplied configuration.
   *
   * \pre there mustn't exist any other instances of this class at the time of
   * invocation of this constructor.
   *
   * \param cfg the configuration spec, determines what gets initialized.
   *
   * \throws sdl_error if the core SDL2 library can't be initialized.
   * \throws img_error if the SDL2_image library can't be initialized.
   * \throws ttf_error if the SDL2_ttf library can't be initialized.
   * \throws mix_error if the SDL2_mixer library can't be initialized.
   *
   * \since 4.0.0
   */
  explicit library(const config& cfg) : m_cfg{cfg}
  {
    init();
  }

  library(const library&) = delete;

  library(library&&) = delete;

  auto operator=(const library&) -> library& = delete;

  auto operator=(library&&) -> library& = delete;

 private:
  class sdl final
  {
   public:
    explicit sdl(const u32 flags)
    {
      const auto result = SDL_Init(flags);
      if (result < 0)
      {
        throw sdl_error{};
      }
    }

    ~sdl() noexcept
    {
      SDL_Quit();
    }
  };

  class sdl_ttf final
  {
   public:
    explicit sdl_ttf()
    {
      const auto result = TTF_Init();
      if (result == -1)
      {
        throw ttf_error{};
      }
    }

    ~sdl_ttf() noexcept
    {
      TTF_Quit();
    }
  };

  class sdl_mixer final
  {
   public:
    sdl_mixer(const int flags,
              const int freq,
              const u16 format,
              const int nChannels,
              const int chunkSize)
    {
      if (!Mix_Init(flags))
      {
        throw mix_error{};
      }

      if (Mix_OpenAudio(freq, format, nChannels, chunkSize) == -1)
      {
        throw mix_error{};
      }
    }

    ~sdl_mixer() noexcept
    {
      Mix_CloseAudio();
      Mix_Quit();
    }
  };

  class sdl_image final
  {
   public:
    explicit sdl_image(const int flags)
    {
      if (!IMG_Init(flags))
      {
        throw img_error{};
      }
    }

    ~sdl_image() noexcept
    {
      IMG_Quit();
    }
  };

  config m_cfg;
  std::optional<sdl> m_sdl;
  std::optional<sdl_image> m_img;
  std::optional<sdl_ttf> m_ttf;
  std::optional<sdl_mixer> m_mixer;

  void init()
  {
    if (m_cfg.initCore)
    {
      m_sdl.emplace(m_cfg.coreFlags);
    }

    if (m_cfg.initImage)
    {
      m_img.emplace(m_cfg.imageFlags);
    }

    if (m_cfg.initTTF)
    {
      m_ttf.emplace();
    }

    if (m_cfg.initMixer)
    {
      m_mixer.emplace(m_cfg.mixerFlags,
                      m_cfg.mixerFreq,
                      m_cfg.mixerFormat,
                      m_cfg.mixerChannels,
                      m_cfg.mixerChunkSize);
    }
  }
};

/// \name SDL version queries
/// \{

/**
 * \brief Returns the version of SDL2 that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of SDL
 * that the program was compiled against.
 *
 * \return the linked version of SDL2.
 *
 * \since 5.2.0
 */
[[nodiscard]] inline auto sdl_linked_version() noexcept -> SDL_version
{
  SDL_version version;
  SDL_GetVersion(&version);
  return version;
}

/**
 * \brief Returns the compile-time version of SDL2 that is being used.
 *
 * \return the compile-time version of SDL2 that is being used.
 *
 * \since 5.1.0
 */
[[nodiscard]] constexpr auto sdl_version() noexcept -> SDL_version
{
  return {SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL};
}

/**
 * \brief Returns the compile-time version of SDL2_image that is being used.
 *
 * \return the compile-time version of SDL2_image that is being used.
 *
 * \since 5.1.0
 */
[[nodiscard]] constexpr auto sdl_image_version() noexcept -> SDL_version
{
  return {SDL_IMAGE_MAJOR_VERSION,
          SDL_IMAGE_MINOR_VERSION,
          SDL_IMAGE_PATCHLEVEL};
}

/**
 * \brief Returns the compile-time version of SDL2_mixer that is being used.
 *
 * \return the compile-time version of SDL2_mixer that is being used.
 *
 * \since 5.1.0
 */
[[nodiscard]] constexpr auto sdl_mixer_version() noexcept -> SDL_version
{
  return {SDL_MIXER_MAJOR_VERSION,
          SDL_MIXER_MINOR_VERSION,
          SDL_MIXER_PATCHLEVEL};
}

/**
 * \brief Returns the compile-time version of SDL2_ttf that is being used.
 *
 * \return the compile-time version of SDL2_ttf that is being used.
 *
 * \since 5.1.0
 */
[[nodiscard]] constexpr auto sdl_ttf_version() noexcept -> SDL_version
{
  return {SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL};
}

/// \} End of SDL version queries
/// \} End of group core

}  // namespace cen

#endif  // CENTURION_CORE_HEADER
