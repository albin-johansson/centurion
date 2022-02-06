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
enum class haptic_direction_type : uint8
{
  polar = SDL_HAPTIC_POLAR,
  cartesian = SDL_HAPTIC_CARTESIAN,
  spherical = SDL_HAPTIC_SPHERICAL
};

/// \name Haptic direction type functions
/// \{

[[nodiscard]] constexpr auto to_string(const haptic_direction_type type) -> std::string_view
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

inline auto operator<<(std::ostream& stream, const haptic_direction_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of haptic direction type functions

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_HAPTIC_DIRECTION_TYPE_HPP_
