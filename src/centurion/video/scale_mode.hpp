#ifndef CENTURION_SCALE_MODE_HEADER
#define CENTURION_SCALE_MODE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup video
/// \{

#if SDL_VERSION_ATLEAST(2, 0, 12)

/**
 * \enum scale_mode
 *
 * \brief Represents different texture scale modes.
 *
 * \since 4.0.0
 *
 * \see `SDL_ScaleMode`
 */
enum class scale_mode
{
  nearest = SDL_ScaleModeNearest,  ///< Represents nearest pixel sampling.
  linear = SDL_ScaleModeLinear,    ///< Represents linear filtering.
  best = SDL_ScaleModeBest         ///< Represents anisotropic filtering.
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied scale mode.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(scale_mode::linear) == "linear"`.
 *
 * \param mode the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const scale_mode mode) -> std::string_view
{
  switch (mode) {
    case scale_mode::nearest:
      return "nearest";

    case scale_mode::linear:
      return "linear";

    case scale_mode::best:
      return "best";

    default:
      throw cen_error{"Did not recognize scale mode!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a scale mode enumerator.
 *
 * \param stream the output stream that will be used.
 * \param mode the enumerator that will be printed.
 *
 * \see `to_string(scale_mode)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const scale_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

/// \} End of streaming

/// \name Scale mode comparison operators
/// \{

/**
 * \brief Indicates whether or not the two scale mode values are the same.
 *
 * \param lhs the lhs scale mode value.
 * \param rhs the rhs scale mode value.
 *
 * \return `true` if the scale mode values are the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const scale_mode lhs, const SDL_ScaleMode rhs) noexcept
    -> bool
{
  return static_cast<SDL_ScaleMode>(lhs) == rhs;
}

/// \copydoc operator==(scale_mode, SDL_ScaleMode)
[[nodiscard]] constexpr auto operator==(const SDL_ScaleMode lhs, const scale_mode rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two scale mode values aren't the same.
 *
 * \param lhs the lhs scale mode value.
 * \param rhs the rhs scale mode value.
 *
 * \return `true` if the scale mode values aren't the same; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const scale_mode lhs, const SDL_ScaleMode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(scale_mode, SDL_ScaleMode)
[[nodiscard]] constexpr auto operator!=(const SDL_ScaleMode lhs, const scale_mode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of scale mode comparison operators

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_SCALE_MODE_HEADER
