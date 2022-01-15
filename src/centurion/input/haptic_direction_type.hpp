#ifndef CENTURION_INPUT_HAPTIC_DIRECTION_TYPE_HPP_
#define CENTURION_INPUT_HAPTIC_DIRECTION_TYPE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../common.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum haptic_direction_type
 *
 * \brief Represents the different types of haptic directions.
 *
 * \since 5.2.0
 */
enum class haptic_direction_type : uint8 {
  polar = SDL_HAPTIC_POLAR,
  cartesian = SDL_HAPTIC_CARTESIAN,
  spherical = SDL_HAPTIC_SPHERICAL
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied haptic direction type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `ToString(haptic_direction_type::polar) == "polar"`.
 *
 * \param type the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws exception if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto ToString(const haptic_direction_type type) -> std::string_view
{
  switch (type) {
    case haptic_direction_type::polar:
      return "polar";

    case haptic_direction_type::cartesian:
      return "cartesian";

    case haptic_direction_type::spherical:
      return "spherical";

    default:
      throw exception{"Did not recognize haptic direction type!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a haptic direction type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the enumerator that will be printed.
 *
 * \see `ToString(haptic_direction_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const haptic_direction_type type) -> std::ostream&
{
  return stream << ToString(type);
}

/// \} End of streaming

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_DIRECTION_TYPE_HPP_
