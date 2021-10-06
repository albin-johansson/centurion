/// \defgroup core Core
/// \brief Contains entities considered to be fundamental for the library.

/**
 * \defgroup hints Hints
 *
 * \brief Contains the API related to hints (configuration variables).
 *
 * \details Refer to the official SDL2 wiki or the `SDL_hints.hpp` header for details
 * regarding any specific hint type.
 *
 * \todo `WindowsIntResourceIcon`, `WindowsIntResourceIconSmall`, `X11WindowVisualID` are
 * string hints because the types of their values isn't known. Should be fixed if the type
 * isn't actually string.
 */

/// \defgroup event Events
/// \brief Contains entities related to events.

/// \defgroup thread Threads
/// \brief Provides threading utilities such as threads, mutexes, locks, etc.

/// \defgroup input Input
/// \brief Contains components related to input from mice, keyboards,
/// controllers, etc.

/// \defgroup video Video
/// \brief Contains components related to window-management, rendering, fonts,
/// etc.

/// \defgroup filesystem Filesystem
/// \brief Contains utilities related to files and directories.

/// \defgroup system System
/// \brief Contains various utilities related to system resources.

/// \defgroup compiler Compiler
/// \brief Provides `constexpr` utilities for querying the current compiler.
/// \note There is no guarantee that the compiler checks are mutually exclusive.

/// \defgroup math Math
/// \brief Contains basic mathematical components, used throughout the library.

/// \defgroup audio Audio
/// \brief Contains the audio API, for playing as sound effects and music.

#ifndef CENTURION_LIBRARY_HEADER
#define CENTURION_LIBRARY_HEADER

#include <SDL.h>

#include "../compiler/features.hpp"

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <cassert>   // assert
#include <optional>  // optional

#include "exception.hpp"
#include "integers.hpp"

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
 * \details All fields are initialized to the default values used by the library.
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
 * Flags passed on to `IMG_Init()`, if \ref config.initImage is `true`.
 *
 * \var config::mixerFlags
 * Flags passed on to `Mix_Init()`, if \ref config.initMixer is `true`.
 *
 * \var config::mixerFreq
 * The frequency used by SDL2_mixer, if \ref config.initMixer is `true`.
 *
 * \var config::mixerFormat
 * The format used by SDL2_mixer, if \ref config.initMixer is `true`.
 *
 * \var config::mixerChannels
 * The amount of channels used by SDL2_mixer, if \ref config.initMixer is `true`.
 *
 * \var config::mixerChunkSize
 * The chunk size used by SDL2_mixer, if \ref config.initMixer is `true`.
 */
struct config final
{
  bool initCore{true};
  bool initImage{true};
  bool initMixer{true};
  bool initTTF{true};

  u32 coreFlags{SDL_INIT_EVERYTHING};

#ifndef CENTURION_NO_SDL_IMAGE
  int imageFlags{IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP};
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
  int mixerFlags{MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID | MIX_INIT_MOD |
                 MIX_INIT_OPUS};
  int mixerFreq{MIX_DEFAULT_FREQUENCY};
  u16 mixerFormat{MIX_DEFAULT_FORMAT};
  int mixerChannels{MIX_DEFAULT_CHANNELS};
  int mixerChunkSize{4096};
#endif  // CENTURION_NO_SDL_MIXER
};

/**
 * \class library
 *
 * \brief Used to initialize and de-initialize the library.
 *
 * \details The following is how you should use this class.
 * \code{cpp}
 *   #include <centurion.hpp>
 *
 *   int main(int argc, char** argv)
 *   {
 *     cen::library centurion;
 *
 *     // ...
 *
 *     return 0;
 *   }
 * \endcode
 *
 * \note The signature of the main-function must be `ìnt(int, char**)` when
 * using the Centurion library!
 *
 * \since 3.0.0
 */
class library final
{
 public:
  /**
   * \brief Initializes the library.
   *
   * \note Make sure to have the `library` instance as a local variable that will outlive
   * the duration of your main program. It's not sufficient to just call the constructor
   * but not store the result as a variable.
   *
   * \pre there mustn't exist any other instances of this class at the time of invocation
   * of this constructor.
   *
   * \throws sdl_error if the core SDL2 library can't be initialized.
   * \throws img_error if the SDL2_image library can't be initialized.
   * \throws ttf_error if the SDL2_ttf library can't be initialized.
   * \throws mix_error if the SDL2_mixer library can't be initialized.
   *
   * \since 3.0.0
   */
  CENTURION_NODISCARD_CTOR library()
  {
    init();
  }

  /**
   * \brief Initializes the library according to the supplied configuration.
   *
   * \pre there mustn't exist any other instances of this class at the time of invocation
   * of this constructor.
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
  CENTURION_NODISCARD_CTOR explicit library(const config& cfg) : m_cfg{cfg}
  {
    init();
  }

  library(const library&) = delete;

  library(library&&) = delete;

  auto operator=(const library&) -> library& = delete;

  auto operator=(library&&) -> library& = delete;

 private:
  struct sdl final
  {
    explicit sdl(const u32 flags)
    {
      if (SDL_Init(flags) < 0) {
        throw sdl_error{};
      }
    }

    ~sdl() noexcept
    {
      SDL_Quit();
    }
  };

#ifndef CENTURION_NO_SDL_TTF

  struct sdl_ttf final
  {
    explicit sdl_ttf()
    {
      if (TTF_Init() == -1) {
        throw ttf_error{};
      }
    }

    ~sdl_ttf() noexcept
    {
      TTF_Quit();
    }
  };

#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER

  struct sdl_mixer final
  {
    sdl_mixer(const int flags,
              const int freq,
              const u16 format,
              const int nChannels,
              const int chunkSize)
    {
      if (!Mix_Init(flags)) {
        throw mix_error{};
      }

      if (Mix_OpenAudio(freq, format, nChannels, chunkSize) == -1) {
        throw mix_error{};
      }
    }

    ~sdl_mixer() noexcept
    {
      Mix_CloseAudio();
      Mix_Quit();
    }
  };

#endif  // #ifndef CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_IMAGE

  struct sdl_image final
  {
    explicit sdl_image(const int flags)
    {
      if (!IMG_Init(flags)) {
        throw img_error{};
      }
    }

    ~sdl_image() noexcept
    {
      IMG_Quit();
    }
  };

#endif  // CENTURION_NO_SDL_IMAGE

  config m_cfg;
  std::optional<sdl> m_sdl;

#ifndef CENTURION_NO_SDL_IMAGE
  std::optional<sdl_image> m_img;
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF
  std::optional<sdl_ttf> m_ttf;
#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER
  std::optional<sdl_mixer> m_mixer;
#endif  // CENTURION_NO_SDL_MIXER

  void init()
  {
    if (m_cfg.initCore) {
      m_sdl.emplace(m_cfg.coreFlags);
    }

#ifndef CENTURION_NO_SDL_IMAGE
    if (m_cfg.initImage) {
      m_img.emplace(m_cfg.imageFlags);
    }
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF
    if (m_cfg.initTTF) {
      m_ttf.emplace();
    }
#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER
    if (m_cfg.initMixer) {
      m_mixer.emplace(m_cfg.mixerFlags,
                      m_cfg.mixerFreq,
                      m_cfg.mixerFormat,
                      m_cfg.mixerChannels,
                      m_cfg.mixerChunkSize);
    }
#endif  // CENTURION_NO_SDL_MIXER
  }
};

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_LIBRARY_HEADER
