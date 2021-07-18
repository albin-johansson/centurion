#ifndef CENTURION_JOYSTICK_TYPE_HEADER
#define CENTURION_JOYSTICK_TYPE_HEADER

#include <SDL.h>

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
