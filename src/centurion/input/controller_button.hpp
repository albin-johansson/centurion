#ifndef CENTURION_CONTROLLER_BUTTON_HEADER
#define CENTURION_CONTROLLER_BUTTON_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum controller_button
 *
 * \brief Represents different game controller buttons.
 *
 * \see `SDL_GameControllerButton`
 *
 * \since 4.0.0
 */
enum class controller_button
{
  invalid = SDL_CONTROLLER_BUTTON_INVALID,
  a = SDL_CONTROLLER_BUTTON_A,
  b = SDL_CONTROLLER_BUTTON_B,
  x = SDL_CONTROLLER_BUTTON_X,
  y = SDL_CONTROLLER_BUTTON_Y,
  back = SDL_CONTROLLER_BUTTON_BACK,
  guide = SDL_CONTROLLER_BUTTON_GUIDE,
  start = SDL_CONTROLLER_BUTTON_START,
  left_stick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
  right_stick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
  left_shoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
  right_shoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
  dpad_up = SDL_CONTROLLER_BUTTON_DPAD_UP,
  dpad_down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
  dpad_left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
  dpad_right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,

#if SDL_VERSION_ATLEAST(2, 0, 14)

  // clang-format off
  misc1 = SDL_CONTROLLER_BUTTON_MISC1, ///< Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button
  // clang-format on

  paddle1 = SDL_CONTROLLER_BUTTON_PADDLE1,    ///< Xbox Elite paddle P1
  paddle2 = SDL_CONTROLLER_BUTTON_PADDLE2,    ///< Xbox Elite paddle P3
  paddle3 = SDL_CONTROLLER_BUTTON_PADDLE3,    ///< Xbox Elite paddle P2
  paddle4 = SDL_CONTROLLER_BUTTON_PADDLE4,    ///< Xbox Elite paddle P4
  touchpad = SDL_CONTROLLER_BUTTON_TOUCHPAD,  ///< PS4/PS5 touchpad button

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  max = SDL_CONTROLLER_BUTTON_MAX
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied controller button.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(controller_button::start) == "start"`.
 *
 * \param button the controller button that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const controller_button button) -> std::string_view
{
  switch (button) {
    case controller_button::invalid:
      return "invalid";

    case controller_button::a:
      return "a";

    case controller_button::b:
      return "b";

    case controller_button::x:
      return "x";

    case controller_button::y:
      return "y";

    case controller_button::back:
      return "back";

    case controller_button::guide:
      return "guide";

    case controller_button::start:
      return "start";

    case controller_button::left_stick:
      return "left_stick";

    case controller_button::right_stick:
      return "right_stick";

    case controller_button::left_shoulder:
      return "left_shoulder";

    case controller_button::right_shoulder:
      return "right_shoulder";

    case controller_button::dpad_up:
      return "dpad_up";

    case controller_button::dpad_down:
      return "dpad_down";

    case controller_button::dpad_left:
      return "dpad_left";

    case controller_button::dpad_right:
      return "dpad_right";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case controller_button::misc1:
      return "misc1";

    case controller_button::paddle1:
      return "paddle1";

    case controller_button::paddle2:
      return "paddle2";

    case controller_button::paddle3:
      return "paddle3";

    case controller_button::paddle4:
      return "paddle4";

    case controller_button::touchpad:
      return "touchpad";

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case controller_button::max:
      return "max";

    default:
      throw cen_error{"Did not recognize controller button!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a controller button enumerator.
 *
 * \param stream the output stream that will be used.
 * \param button the controller button that will be printed.
 *
 * \see `to_string(controller_button)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const controller_button button) -> std::ostream&
{
  return stream << to_string(button);
}

/// \} End of streaming

/// \name Controller button comparison operators
/// \{

/**
 * \brief Indicates whether or not two game controller button values are the
 * same.
 *
 * \param lhs the left-hand side game controller button value.
 * \param rhs the right-hand side game controller button value.
 *
 * \return `true` if the game controller button values are the same; `false`
 * otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(const controller_button lhs,
                                        const SDL_GameControllerButton rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerButton>(lhs) == rhs;
}

/// \copydoc operator==(controller_button, SDL_GameControllerButton)
[[nodiscard]] constexpr auto operator==(const SDL_GameControllerButton lhs,
                                        const controller_button rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two game controller button values aren't the
 * same.
 *
 * \param lhs the left-hand side game controller button value.
 * \param rhs the right-hand side game controller button value.
 *
 * \return `true` if the game controller button values aren't the same; `false`
 * otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(const controller_button lhs,
                                        const SDL_GameControllerButton rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(controller_button, SDL_GameControllerButton)
[[nodiscard]] constexpr auto operator!=(const SDL_GameControllerButton lhs,
                                        const controller_button rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of controller button comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_CONTROLLER_BUTTON_HEADER
