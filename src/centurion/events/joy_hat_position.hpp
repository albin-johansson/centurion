#ifndef CENTURION_JOY_HAT_POSITION_HEADER
#define CENTURION_JOY_HAT_POSITION_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \enum joy_hat_position
 *
 * \brief Serves as a wrapper for the `SDL_HAT_x` macro values.
 *
 * \see `joy_hat_position_count()`
 *
 * \since 4.0.0
 */
enum class joy_hat_position : u8
{
  left_up = SDL_HAT_LEFTUP,
  left = SDL_HAT_LEFT,
  left_down = SDL_HAT_LEFTDOWN,
  up = SDL_HAT_UP,
  centered = SDL_HAT_CENTERED,
  down = SDL_HAT_DOWN,
  right_up = SDL_HAT_RIGHTUP,
  right = SDL_HAT_RIGHT,
  right_down = SDL_HAT_RIGHTDOWN
};

/**
 * \brief Returns the number of enumerators for the `joy_hat_position` enum.
 *
 * \return the number of enumerators.
 *
 * \since 6.3.0
 */
[[nodiscard]] constexpr auto joy_hat_position_count() noexcept -> int
{
  return 9;
}

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied joystick hat position.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(joy_hat_position::down) == "down"`.
 *
 * \param position the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const joy_hat_position position) -> std::string_view
{
  switch (position) {
    case joy_hat_position::left_up:
      return "left_up";

    case joy_hat_position::left:
      return "left";

    case joy_hat_position::left_down:
      return "left_down";

    case joy_hat_position::up:
      return "up";

    case joy_hat_position::centered:
      return "centered";

    case joy_hat_position::down:
      return "down";

    case joy_hat_position::right_up:
      return "right_up";

    case joy_hat_position::right:
      return "right";

    case joy_hat_position::right_down:
      return "right_down";

    default:
      throw cen_error{"Did not recognize joystick hat position!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a joystick hat position enumerator.
 *
 * \param stream the output stream that will be used.
 * \param position the enumerator that will be printed.
 *
 * \see `to_string(joy_hat_position)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const joy_hat_position position) -> std::ostream&
{
  return stream << to_string(position);
}

/// \} End of streaming

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_JOY_HAT_POSITION_HEADER
