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

/**
 * \brief Expands into the current major version of the library.
 */
#define CENTURION_VERSION_MAJOR 7

/**
 * \brief Expands into the current minor version of the library.
 */
#define CENTURION_VERSION_MINOR 0

/**
 * \brief Expands into the current patch version of the library.
 */
#define CENTURION_VERSION_PATCH 0

#define CENTURION_MAKE_VERSION_NUMBER(X, Y, Z) (((X)*1'000) + ((Y)*100) + (Z))

#define CENTURION_VERSION_NUMBER                         \
  CENTURION_MAKE_VERSION_NUMBER(CENTURION_VERSION_MAJOR, \
                                CENTURION_VERSION_MINOR, \
                                CENTURION_VERSION_PATCH)

#define CENTURION_VERSION_AT_LEAST(X, Y, Z) \
  CENTURION_VERSION_NUMBER >= CENTURION_MAKE_VERSION_NUMBER(X, Y, Z)

#define CENTURION_SDL_VERSION_IS(X, Y, Z) \
  ((SDL_MAJOR_VERSION == (X)) && (SDL_MINOR_VERSION == (Y)) && (SDL_PATCHLEVEL == (Z)))

namespace cen {

/// \name Centurion version queries
/// \{

/**
 * \brief Represents a simple major/minor/patch version identifier.
 *
 * \ingroup versioning
 */
struct version final
{
  int major{};
  int minor{};
  int patch{};
};

/**
 * \brief Returns the current Centurion version.
 *
 * \return the current version of Centurion.
 */
[[nodiscard]] constexpr auto current_version() noexcept -> version
{
  return {CENTURION_VERSION_MAJOR, CENTURION_VERSION_MINOR, CENTURION_VERSION_PATCH};
}

/**
 * \brief Indicates whether the current Centurion version is at least the specific version.
 *
 * \param major the major version value.
 * \param minor the minor version value.
 * \param patch the patch version value.
 *
 * \return `true` if the Centurion version is at least the specific version; `false` otherwise.
 *
 * \see `CENTURION_VERSION_AT_LEAST`
 */
[[nodiscard]] constexpr auto version_at_least(const int major,
                                              const int minor,
                                              const int patch) noexcept -> bool
{
  return CENTURION_VERSION_AT_LEAST(major, minor, patch);
}

/// \} End of centurion version queries

/// \name SDL version queries
/// \{

/**
 * \brief Returns the compile-time version of SDL2 that is being used.
 *
 * \return the compile-time version of SDL2 that is being used.
 */
[[nodiscard]] constexpr auto sdl_version() noexcept -> SDL_version
{
  return {SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL};
}

/**
 * \brief Returns the version of SDL2 that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of SDL2 that the
 * program was compiled against.
 *
 * \return the linked version of SDL2.
 */
[[nodiscard]] inline auto sdl_linked_version() noexcept -> SDL_version
{
  SDL_version version{};
  SDL_GetVersion(&version);
  return version;
}

#ifndef CENTURION_NO_SDL_IMAGE

/**
 * \brief Returns the compile-time version of SDL2_image that is being used.
 *
 * \return the compile-time version of SDL2_image that is being used.
 */
[[nodiscard]] constexpr auto sdl_image_version() noexcept -> SDL_version
{
  return {SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_PATCHLEVEL};
}

/**
 * \brief Returns the version of SDL2_image that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of SDL2_image that the
 * program was compiled against.
 *
 * \return the linked version of SDL2_image.
 */
[[nodiscard]] inline auto sdl_image_linked_version() noexcept -> SDL_version
{
  const auto* version = IMG_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

/**
 * \brief Returns the compile-time version of SDL2_mixer that is being used.
 *
 * \return the compile-time version of SDL2_mixer that is being used.
 */
[[nodiscard]] constexpr auto sdl_mixer_version() noexcept -> SDL_version
{
  return {SDL_MIXER_MAJOR_VERSION, SDL_MIXER_MINOR_VERSION, SDL_MIXER_PATCHLEVEL};
}

/**
 * \brief Returns the version of SDL2_mixer that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of SDL2_mixer that the
 * program was compiled against.
 *
 * \return the linked version of SDL2_mixer.
 */
[[nodiscard]] inline auto sdl_mixer_linked_version() noexcept -> SDL_version
{
  const auto* version = Mix_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

/**
 * \brief Returns the compile-time version of SDL2_ttf that is being used.
 *
 * \return the compile-time version of SDL2_ttf that is being used.
 */
[[nodiscard]] constexpr auto sdl_ttf_version() noexcept -> SDL_version
{
  return {SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL};
}

/**
 * \brief Returns the version of SDL2_ttf that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of SDL2_ttf that the
 * program was compiled against.
 *
 * \return the linked version of SDL2_ttf.
 */
[[nodiscard]] inline auto sdl_ttf_linked_version() noexcept -> SDL_version
{
  const auto* version = TTF_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_TTF

/// \} End of SDL version queries

}  // namespace cen

#endif  // CENTURION_VERSION_HPP_
