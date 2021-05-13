#ifndef CENTURION_TEXTURE_ACCESS_HEADER
#define CENTURION_TEXTURE_ACCESS_HEADER

#include <SDL.h>

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum texture_access
 *
 * \brief Represents different texture access modes.
 *
 * \note The `no_lock` enumerator is also referred to as "static" texture access.
 *
 * \since 3.0.0
 *
 * \see `SDL_TextureAccess`
 */
enum class texture_access : int
{
  no_lock = SDL_TEXTUREACCESS_STATIC,  ///< Texture changes rarely, and isn't lockable.
  streaming =
      SDL_TEXTUREACCESS_STREAMING,   ///< Texture changes frequently, and is lockable.
  target = SDL_TEXTUREACCESS_TARGET  ///< Texture can be used as a render target.
};

/**
 * \brief Indicates whether or not the two texture access values are the same.
 *
 * \param lhs the lhs texture access value.
 * \param rhs the rhs texture access value.
 *
 * \return `true` if the texture access values are the same; `false` otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator==(const texture_access lhs,
                                        const SDL_TextureAccess rhs) noexcept -> bool
{
  return static_cast<SDL_TextureAccess>(lhs) == rhs;
}

/// \copydoc operator==(texture_access, SDL_TextureAccess)
[[nodiscard]] constexpr auto operator==(const SDL_TextureAccess lhs,
                                        const texture_access rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two texture access values aren't the same.
 *
 * \param lhs the lhs texture access value.
 * \param rhs the rhs texture access value.
 *
 * \return `true` if the texture access values aren't the same; `false`
 * otherwise.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto operator!=(const texture_access lhs,
                                        const SDL_TextureAccess rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(texture_access, SDL_TextureAccess)
[[nodiscard]] constexpr auto operator!=(const SDL_TextureAccess lhs,
                                        const texture_access rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \}

}  // namespace cen

#endif  // CENTURION_TEXTURE_ACCESS_HEADER
