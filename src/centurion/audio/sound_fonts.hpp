#ifndef CENTURION_SOUND_FONTS_HEADER
#define CENTURION_SOUND_FONTS_HEADER

#ifndef CENTURION_NO_SDL_MIXER

#include <SDL.h>
#include <SDL_mixer.h>

#include "../core/result.hpp"
#include "../core/str.hpp"

namespace cen {

/// \addtogroup audio
/// \{

using sound_font_visit_callback = int(SDLCALL*)(str, void*) noexcept;

/**
 * \brief Sets the paths to the available SoundFont files.
 *
 * \param paths a string of SoundFont paths, separated by semicolons.
 *
 * \return `success` if the operation was successful; `failure` otherwise.
 *
 * \see `Mix_SetSoundFonts`
 *
 * \since 6.0.0
 */
inline auto set_sound_fonts(const str paths) noexcept -> result
{
  return Mix_SetSoundFonts(paths) != 0;
}

/**
 * \brief Returns a path to a SoundFont file.
 *
 * \return a path to a SoundFonts file; can be null.
 *
 * \see `Mix_GetSoundFonts`
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto get_sound_fonts() noexcept -> str
{
  return Mix_GetSoundFonts();
}

/**
 * \brief Visits each available SoundFont path.
 *
 * \tparam T the type of the associated data.
 *
 * \param callable the callable that will be invoked for each SoundFont path.
 * \param data optional user data.
 *
 * \return `success` if the operation was successful; `failure` otherwise.
 *
 * \see `Mix_EachSoundFont`
 *
 * \since 6.0.0
 */
template <typename T = void>
auto each_sound_font(sound_font_visit_callback callable, T* data = nullptr) noexcept -> result
{
  return Mix_EachSoundFont(callable, static_cast<void*>(data)) != 0;
}

/// \} End of group audio

}  // namespace cen

#endif  // CENTURION_NO_SDL_MIXER
#endif  // CENTURION_SOUND_FONTS_HEADER
