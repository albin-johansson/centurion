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

/**
 * \ingroup common
 * \defgroup initialization Initialization
 *
 * \brief Contains components related to SDL initialization.
 */

/// \addtogroup initialization
/// \{

/**
 * \brief Used to specify how the core SDL library is initialized.
 */
struct sdl_cfg final {
  /// \brief Controls which SDL subsystems are initialized, see `SDL_INIT_` macros.
  uint32 flags{SDL_INIT_EVERYTHING};
};

/**
 * \brief Used to load and subsequently unload the core SDL library.
 *
 * \see `img`
 * \see `mix`
 * \see `ttf`
 */
class sdl final {
 public:
  /**
   * \brief Loads the core SDL library.
   *
   * \param cfg the configuration that will be used.
   *
   * \throws sdl_error if the SDL library cannot be initialized.
   */
  CENTURION_NODISCARD_CTOR explicit sdl(const sdl_cfg& cfg = {})
  {
    if (SDL_Init(cfg.flags) < 0) {
      throw sdl_error{};
    }
  }

  ~sdl() noexcept { SDL_Quit(); }
};

#ifndef CENTURION_NO_SDL_IMAGE

/**
 * \brief Used to specify how the SDL_image library is initialized.
 */
struct img_cfg final {
  /// \brief Controls which image formats to support, see `IMG_INIT_` macros.
  int flags{IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP};
};

/**
 * \brief Used to load and subsequently unload the SDL_image library.
 */
class img final {
 public:
  /**
   * \brief Loads the SDL_image library.
   *
   * \param cfg the configuration that will be used.
   *
   * \throws img_error if the SDL_image library cannot be initialized.
   */
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

/**
 * \brief Used to specify how the SDL_mixer library is initialized.
 */
struct mix_cfg final {
  /// \brief Controls which file formats to be supported, see `MIX_INIT_` macros.
  int flags{MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MID | MIX_INIT_MOD |
            MIX_INIT_OPUS};

  /// \brief The mixer frequency.
  int frequency{MIX_DEFAULT_FREQUENCY};

  /// \brief The mixer format.
  uint16 format{MIX_DEFAULT_FORMAT};

  /// \brief The amount of mixer channels.
  int channels{MIX_DEFAULT_CHANNELS};

  /// \brief The mixer chunk size, in bytes.
  int chunk_size{4096};
};

/**
 * \brief Used to load and subsequently unload the SDL_mixer library.
 */
class mix final {
 public:
  /**
   * \brief Loads the SDL_mixer library.
   *
   * \param cfg the configuration that will be used.
   *
   * \throws mix_error if the SDL_mixer library cannot be initialized or if the audio device
   * couldn't be opened.
   */
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

/**
 * \brief Used to load and subsequently unload the SDL_ttf library.
 */
class ttf final {
 public:
  /**
   * \brief Loads the SDL_ttf library.
   *
   * \param cfg the configuration that will be used.
   *
   * \throws ttf_error if the SDL_ttf library cannot be initialized.
   */
  CENTURION_NODISCARD_CTOR ttf()
  {
    if (TTF_Init() == -1) {
      throw ttf_error{};
    }
  }

  ~ttf() noexcept { TTF_Quit(); }
};

#endif  // CENTURION_NO_SDL_TTF

/// \} End of group initialization

}  // namespace cen

#endif  // CENTURION_INITIALIZATION_HPP_
