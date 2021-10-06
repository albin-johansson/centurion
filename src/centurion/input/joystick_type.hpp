#ifndef CENTURION_JOYSTICK_TYPE_HEADER
#define CENTURION_JOYSTICK_TYPE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum joystick_type
 *
 * \brief Provides values that represent different types of "joysticks".
 *
 * \since 4.2.0
 */
enum class joystick_type
{
  unknown = SDL_JOYSTICK_TYPE_UNKNOWN,
  game_controller = SDL_JOYSTICK_TYPE_GAMECONTROLLER,
  wheel = SDL_JOYSTICK_TYPE_WHEEL,
  arcade_stick = SDL_JOYSTICK_TYPE_ARCADE_STICK,
  flight_stick = SDL_JOYSTICK_TYPE_FLIGHT_STICK,
  dance_pad = SDL_JOYSTICK_TYPE_DANCE_PAD,
  guitar = SDL_JOYSTICK_TYPE_GUITAR,
  drum_kit = SDL_JOYSTICK_TYPE_DRUM_KIT,
  arcade_pad = SDL_JOYSTICK_TYPE_ARCADE_PAD,
  throttle = SDL_JOYSTICK_TYPE_THROTTLE
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied joystick type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(joystick_type::guitar) == "guitar"`.
 *
 * \param type the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const joystick_type type) -> std::string_view
{
  switch (type) {
    case joystick_type::unknown:
      return "unknown";

    case joystick_type::game_controller:
      return "game_controller";

    case joystick_type::wheel:
      return "wheel";

    case joystick_type::arcade_stick:
      return "arcade_stick";

    case joystick_type::flight_stick:
      return "flight_stick";

    case joystick_type::dance_pad:
      return "dance_pad";

    case joystick_type::guitar:
      return "guitar";

    case joystick_type::drum_kit:
      return "drum_kit";

    case joystick_type::arcade_pad:
      return "arcade_pad";

    case joystick_type::throttle:
      return "throttle";

    default:
      throw cen_error{"Did not recognize joystick type!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a joystick type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the enumerator that will be printed.
 *
 * \see `to_string(joystick_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const joystick_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of streaming

/// \name Joystick type comparison operators
/// \{

/**
 * \brief Indicates whether or not two joystick type values are the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const joystick_type lhs,
                                        const SDL_JoystickType rhs) noexcept -> bool
{
  return static_cast<SDL_JoystickType>(lhs) == rhs;
}

/**
 * \brief Indicates whether or not two joystick type values are the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator==(const SDL_JoystickType lhs,
                                        const joystick_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two joystick type values aren't the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const joystick_type lhs,
                                        const SDL_JoystickType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * \brief Indicates whether or not two joystick type values aren't the same.
 *
 * \param lhs the left-hand side joystick type value.
 * \param rhs the right-hand side joystick type value.
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 4.3.0
 */
[[nodiscard]] constexpr auto operator!=(const SDL_JoystickType lhs,
                                        const joystick_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of joystick type comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_JOYSTICK_TYPE_HEADER
