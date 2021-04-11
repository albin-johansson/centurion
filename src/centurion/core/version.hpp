#ifndef CENTURION_VERSION_HEADER
#define CENTURION_VERSION_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cassert>  // assert

namespace cen {

/// \addtogroup core
/// \{

/// \name Centurion version queries
/// \{

#define CENTURION_VERSION_MAJOR 6
#define CENTURION_VERSION_MINOR 0
#define CENTURION_VERSION_PATCH 0

#define CENTURION_MAKE_VERSION_NUMBER(x, y, z) (((x)*1'000) + ((y)*100) + (z))

#define CENTURION_VERSION_NUMBER                         \
  CENTURION_MAKE_VERSION_NUMBER(CENTURION_VERSION_MAJOR, \
                                CENTURION_VERSION_MINOR, \
                                CENTURION_VERSION_PATCH)

#define CENTURION_VERSION_AT_LEAST(x, y, z) \
  CENTURION_VERSION_NUMBER >= CENTURION_MAKE_VERSION_NUMBER(x, y, z)

struct version final
{
  int major{CENTURION_VERSION_MAJOR};
  int minor{CENTURION_VERSION_MINOR};
  int patch{CENTURION_VERSION_PATCH};
};

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
 * \brief Returns the version of SDL2_image that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of
 * SDL2_image that the program was compiled against.
 *
 * \return the linked version of SDL2_image.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto sdl_image_linked_version() noexcept -> SDL_version
{
  const auto* version = IMG_Linked_Version();
  assert(version);  // Sanity check
  return *version;
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
 * \brief Returns the version of SDL2_mixer that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of
 * SDL2_mixer that the program was compiled against.
 *
 * \return the linked version of SDL2_mixer.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto sdl_mixer_linked_version() noexcept -> SDL_version
{
  const auto* version = Mix_Linked_Version();
  assert(version);  // Sanity check
  return *version;
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
 * \brief Returns the version of SDL2_ttf that is linked against the program.
 *
 * \note The linked version isn't necessarily the same as the version of
 * SDL2_ttf that the program was compiled against.
 *
 * \return the linked version of SDL2_ttf.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto sdl_ttf_linked_version() noexcept -> SDL_version
{
  const auto* version = TTF_Linked_Version();
  assert(version);  // Sanity check
  return *version;
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

#endif  // CENTURION_VERSION_HEADER
