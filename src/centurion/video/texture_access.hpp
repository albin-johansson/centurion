#ifndef CENTURION_TEXTURE_ACCESS_HEADER
#define CENTURION_TEXTURE_ACCESS_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

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
  // clang-format off
  no_lock = SDL_TEXTUREACCESS_STATIC,       ///< Texture changes rarely and isn't lockable.
  streaming = SDL_TEXTUREACCESS_STREAMING,  ///< Texture changes frequently and is lockable.
  target = SDL_TEXTUREACCESS_TARGET         ///< Texture can be used as a render target.
  // clang-format on
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied texture access.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(texture_access::streaming) == "streaming"`.
 *
 * \param access the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const texture_access access) -> std::string_view
{
  switch (access) {
    case texture_access::no_lock:
      return "no_lock";

    case texture_access::streaming:
      return "streaming";

    case texture_access::target:
      return "target";

    default:
      throw cen_error{"Did not recognize texture access!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a texture access enumerator.
 *
 * \param stream the output stream that will be used.
 * \param access the enumerator that will be printed.
 *
 * \see `to_string(texture_access)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const texture_access access) -> std::ostream&
{
  return stream << to_string(access);
}

/// \} End of streaming

/// \name Texture access comparison operators
/// \{

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

/// \} End of texture access comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_TEXTURE_ACCESS_HEADER
