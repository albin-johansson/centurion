#ifndef CENTURION_VERSION_HPP_
#define CENTURION_VERSION_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <cassert>  // assert

/// \addtogroup core
/// \{

/// Expands into the current major version of the library.
#define CENTURION_VERSION_MAJOR 7

/// Expands into the current minor version of the library.
#define CENTURION_VERSION_MINOR 0

/// Expands into the current patch version of the library.
#define CENTURION_VERSION_PATCH 0

/// Expands into a version identifier, e.g. `1.2.3` becomes `1203`
#define CENTURION_MAKE_VERSION_NUMBER(x, y, z) (((x)*1'000) + ((y)*100) + (z))

#define CENTURION_VERSION_NUMBER                         \
  CENTURION_MAKE_VERSION_NUMBER(CENTURION_VERSION_MAJOR, \
                                CENTURION_VERSION_MINOR, \
                                CENTURION_VERSION_PATCH)

#define CENTURION_VERSION_AT_LEAST(x, y, z) \
  CENTURION_VERSION_NUMBER >= CENTURION_MAKE_VERSION_NUMBER(x, y, z)

#define CENTURION_SDL_VERSION_IS(x, y, z) \
  ((SDL_MAJOR_VERSION == (x)) && (SDL_MINOR_VERSION == (y)) && (SDL_PATCHLEVEL == (z)))

namespace cen {

/// \name Centurion version queries
/// \{

/// Provides a snapshot of the current Centurion version.
struct Version final {
  int major{CENTURION_VERSION_MAJOR};
  int minor{CENTURION_VERSION_MINOR};
  int patch{CENTURION_VERSION_PATCH};
};

/// Indicates whether the current Centurion version is greater or equal to another version.
///
/// \param major the major version value.
/// \param minor the minor version value.
/// \param patch the patch version value.
///
/// \return `true` if the version of Centurion is at least the specified version; `false`
/// otherwise.
///
/// \see `CENTURION_VERSION_AT_LEAST`
[[nodiscard]] constexpr auto version_at_least(const int major,
                                              const int minor,
                                              const int patch) noexcept -> bool
{
  return CENTURION_VERSION_AT_LEAST(major, minor, patch);
}

/// \} End of centurion version queries

/// \name SDL version queries
/// \{

[[nodiscard]] constexpr auto GetCurrentSDLVersion() noexcept -> SDL_version
{
  return {SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL};
}

[[nodiscard]] inline auto GetLinkedSDLVersion() noexcept -> SDL_version
{
  SDL_version version{};
  SDL_GetVersion(&version);
  return version;
}

#ifndef CENTURION_NO_SDL_IMAGE

[[nodiscard]] constexpr auto GetCurrentIMGVersion() noexcept -> SDL_version
{
  return {SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_PATCHLEVEL};
}

[[nodiscard]] inline auto GetLinkedIMGVersion() noexcept -> SDL_version
{
  const auto* version = IMG_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

[[nodiscard]] constexpr auto GetCurrentMixVersion() noexcept -> SDL_version
{
  return {SDL_MIXER_MAJOR_VERSION, SDL_MIXER_MINOR_VERSION, SDL_MIXER_PATCHLEVEL};
}

[[nodiscard]] inline auto GetLinkedMixVersion() noexcept -> SDL_version
{
  const auto* version = Mix_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

[[nodiscard]] constexpr auto GetCurrentTTFVersion() noexcept -> SDL_version
{
  return {SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL};
}

[[nodiscard]] inline auto GetLinkedTTFVersion() noexcept -> SDL_version
{
  const auto* version = TTF_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_TTF

/// \} End of SDL version queries

}  // namespace cen

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

/* Workaround for the enum being completely anonymous in SDL 2.0.10. Included here because
   multiple files depend on this definition. */
using SDL_KeyCode = decltype(SDLK_UNKNOWN);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

/// \} End of group core

#endif  // CENTURION_VERSION_HPP_
