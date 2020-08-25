/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file game_controller.hpp
 *
 * @brief Provides the game controller API.
 *
 * @todo Expand the game controller API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_GAME_CONTROLLER_HEADER
#define CENTURION_GAME_CONTROLLER_HEADER

#include <SDL.h>

#include <cstring>
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>

#include "button_state.hpp"
#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "joystick_handle.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/// @addtogroup input
/// @{

/**
 * @enum gamepad_axis
 *
 * @brief Mirrors the values of the `SDL_GameControllerAxis` enum.
 *
 * @see `SDL_GameControllerAxis`
 *
 * @since 4.0.0
 *
 * @headerfile game_controller.hpp
 */
enum class gamepad_axis {
  invalid = SDL_CONTROLLER_AXIS_INVALID,
  left_x = SDL_CONTROLLER_AXIS_LEFTX,
  left_y = SDL_CONTROLLER_AXIS_LEFTY,
  right_x = SDL_CONTROLLER_AXIS_RIGHTX,
  right_y = SDL_CONTROLLER_AXIS_RIGHTY,
  trigger_left = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
  max = SDL_CONTROLLER_AXIS_MAX
};

/**
 * @enum gamepad_button
 *
 * @brief Mirrors the values of the `SDL_GameControllerButton` enum.
 *
 * @since 4.0.0
 *
 * @headerfile game_controller.hpp
 */
enum class gamepad_button {
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
  max = SDL_CONTROLLER_BUTTON_MAX
};

struct game_controller_traits final
{
 private:
  struct deleter final
  {
    void operator()(SDL_GameController* controller) noexcept
    {
      SDL_GameControllerClose(controller);
    }
  };

 public:
  using storage_type = std::unique_ptr<SDL_GameController*, deleter>;
  using owning = std::true_type;
};

struct game_controller_handle_traits final
{
  using storage_type = SDL_GameController*;
  using owning = std::false_type;
};

/**
 * @class basic_game_controller
 *
 * @brief Represents a game controller, e.g. an xbox-controller.
 *
 * @since 5.0.0
 *
 * @headerfile game_controller.hpp
 */
template <typename T>
class basic_game_controller final
{
  using owning = typename T::owning;
  using storage_type = typename T::storage_type;
  using pointer_argument = std::conditional_t<owning::value,
                                              nn_owner<SDL_GameController*>,
                                              not_null<SDL_GameController*>>;

 public:
  /**
   * @brief Attempts to create a game controller.
   *
   * @details The joystick index is the same as the device index passed to the
   * `joystick` constructor. The index passed as an argument refers to the
   * n'th game controller on the system.
   *
   * @note The supplied index is not the value which will identify the
   * controller in controller events. Instead, the joystick's instance id
   * (`SDL_JoystickID`) will be used.
   *
   * @param index the device index, can't be >= than the amount of number of
   * joysticks.
   *
   * @throws sdl_error if the game controller cannot be opened.
   *
   * @since 5.0.0
   */
  template <typename = std::enable_if_t<owning::value>>
  explicit basic_game_controller(int index)
      : m_controller{SDL_GameControllerOpen(index)}
  {
    if (!m_controller) {
      throw sdl_error{"Failed to open game controller!"};
    }
  }

  explicit basic_game_controller(pointer_argument controller) noexcept
      : m_controller{controller}
  {}

  template <typename = std::enable_if_t<owning::value>>
  static auto from_joystick(SDL_JoystickID id) -> basic_game_controller<T>
  {
    if (auto* controller = SDL_GameControllerFromInstanceID(id)) {
      return basic_game_controller<T>{controller};
    } else {
      throw sdl_error{"Failed to create game_controller from joystick ID!"};
    }
  }

  [[nodiscard]] auto is_connected() const noexcept -> bool
  {
    return static_cast<bool>(SDL_GameControllerGetAttached(ptr()));
  }

  [[nodiscard]] auto name() const noexcept -> czstring
  {
    return SDL_GameControllerName(ptr());
  }

  [[nodiscard]] auto get_state(gamepad_button button) const noexcept
      -> button_state
  {
    const auto state = SDL_GameControllerGetButton(
        ptr(), static_cast<SDL_GameControllerButton>(button));
    return static_cast<button_state>(state);
  }

  [[nodiscard]] auto is_pressed(gamepad_button button) const noexcept -> bool
  {
    return get_state(button) == button_state::pressed;
  }

  [[nodiscard]] auto is_released(gamepad_button button) const noexcept -> bool
  {
    return get_state(button) == button_state::released;
  }

  [[nodiscard]] auto get_axis(gamepad_axis axis) const noexcept -> i32
  {
    return SDL_GameControllerGetAxis(ptr(),
                                     static_cast<SDL_GameControllerAxis>(axis));
  }

  //  [[nodiscard]] auto get_bind(axis axis) const
  //  {
  //    const auto result = SDL_GameControllerGetBindForAxis(
  //        ptr(), static_cast<SDL_GameControllerAxis>(axis));
  //
  //    result.value
  //
  //  }

  [[nodiscard]] auto get_joystick() noexcept -> joystick_handle
  {
    return joystick_handle{SDL_GameControllerGetJoystick(ptr())};
  }

  static void update() { SDL_GameControllerUpdate(); }

  static void set_polling(bool polling) noexcept
  {
    SDL_GameControllerEventState(polling ? SDL_ENABLE : SDL_DISABLE);
  }

  [[nodiscard]] static auto is_polling() noexcept -> bool
  {
    return SDL_GameControllerEventState(SDL_QUERY);
  }

  [[nodiscard]] static auto get_axis(nn_czstring str) -> gamepad_axis
  {
    return static_cast<gamepad_axis>(SDL_GameControllerGetAxisFromString(str));
  }

 private:
  storage_type m_controller;

  [[nodiscard]] auto ptr() noexcept -> SDL_GameController*
  {
    if constexpr (std::is_pointer_v<storage_type>) {
      return m_controller;
    } else {
      return m_controller.get();
    }
  }
};

using gamepad = basic_game_controller<game_controller_traits>;
using gamepad_handle = basic_game_controller<game_controller_handle_traits>;

namespace gamecontroller {

inline auto add_mapping(nn_czstring mapping) -> bool
{
  const auto result = SDL_GameControllerAddMapping(mapping);
  if (result == 1) {
    return true;
  } else if (result == 0) {
    return false;
  } else {
    throw sdl_error{"Failed to add game controller mapping!"};
  }
}

/**
 * @brief Loads a set of game controller mappings from a file.
 *
 * @details A collection of game controller mappings can be found at <a
 * href="https://github.com/gabomdq/SDL_GameControllerDB">here</a>. New
 * mappings for previously known GUIDs will overwrite the previous mappings.
 * Furthermore, mappings for different platforms than the current platform
 * will be ignored.
 *
 * @remarks It's possible to call this function several times to use multiple
 * mapping files.
 *
 * @note The text database is stored entirely in memory during processing.
 *
 * @param file the path of the mapping file.
 *
 * @return the amount of mappings added.
 *
 * @throws sdl_error if the mapping couldn't be added.
 *
 * @since 5.0.0
 */
inline auto load_mappings(nn_czstring file) -> int
{
  const auto result = SDL_GameControllerAddMappingsFromFile(file);
  if (result != -1) {
    return result;
  } else {
    throw sdl_error{"Failed to add game controller mappings from file!"};
  }
}

[[nodiscard]] inline auto is_supported(int index) noexcept -> bool
{
  return static_cast<bool>(SDL_IsGameController(index));
}

}  // namespace gamecontroller

template <typename T>
[[nodiscard]] auto to_string(const basic_game_controller<T>& controller)
    -> std::string
{
  using namespace std::string_literals;
  czstring name = controller.name();

  if constexpr (std::is_same_v<T, gamepad>) {
    return "[gamepad | name: "s + (name ? name : "N/A") + "]"s;
  } else {
    return "[gamepad_handle | name: "s + (name ? name : "N/A") + "]"s;
  }
}

template <typename T>
auto operator<<(std::ostream& stream,
                const basic_game_controller<T>& controller) -> std::ostream&
{
  stream << to_string(controller);
  return stream;
}

/**
 * @brief Indicates whether or not two game controller axis values are the same.
 *
 * @param lhs the left-hand-side game controller axis value.
 * @param rhs the right-hand-side game controller axis value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    gamepad_axis lhs,
    SDL_GameControllerAxis rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerAxis>(lhs) == rhs;
}

/**
 * @copydoc operator==(gamepad_axis, SDL_GameControllerAxis)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_GameControllerAxis lhs,
                                               gamepad_axis rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two game controller axis values aren't the
 * same.
 *
 * @param lhs the left-hand-side game controller axis value.
 * @param rhs the right-hand-side game controller axis value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    gamepad_axis lhs,
    SDL_GameControllerAxis rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(gamepad_axis, SDL_GameControllerAxis)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_GameControllerAxis lhs,
                                               gamepad_axis rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two game controller button values are the
 * same.
 *
 * @param lhs the left-hand side game controller button value.
 * @param rhs the right-hand side game controller button value.
 *
 * @return `true` if the game controller button values are the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(
    gamepad_button lhs,
    SDL_GameControllerButton rhs) noexcept -> bool
{
  return static_cast<SDL_GameControllerButton>(lhs) == rhs;
}

/**
 * @copydoc operator==(gamepad_button, SDL_GameControllerButton)
 */
[[nodiscard]] inline constexpr auto operator==(SDL_GameControllerButton lhs,
                                               gamepad_button rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two game controller button values aren't the
 * same.
 *
 * @param lhs the left-hand side game controller button value.
 * @param rhs the right-hand side game controller button value.
 *
 * @return `true` if the game controller button values aren't the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    gamepad_button lhs,
    SDL_GameControllerButton rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(gamepad_button, SDL_GameControllerButton)
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_GameControllerButton lhs,
                                               gamepad_button rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// @}

}  // namespace centurion

#endif  // CENTURION_GAME_CONTROLLER_HEADER
