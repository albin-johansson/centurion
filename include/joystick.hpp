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
 * @file joystick.hpp
 *
 * @ingroup input
 *
 * @brief Provides the `joystick` class.
 *
 * @author Albin Johansson
 *
 * @copyright MIT License
 *
 * @date 2019-2020
 */

#ifndef CENTURION_JOYSTICK_HEADER
#define CENTURION_JOYSTICK_HEADER

#include <SDL_joystick.h>

#include <memory>

#include "basic_joystick.hpp"
#include "button_state.hpp"
#include "centurion_api.hpp"
#include "detail/utils.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

class joystick;

/**
 * @class joystick_traits<joystick>
 *
 * @brief Provides traits for the `joystick` class.
 *
 * @since 5.0.0
 *
 * @headerfile joystick.hpp
 */
template <>
class joystick_traits<joystick> final
{
 private:
  class deleter final
  {
   public:
    void operator()(SDL_Joystick* joystick) noexcept
    {
      if (SDL_JoystickGetAttached(joystick)) {
        SDL_JoystickClose(joystick);
      }
    }
  };

 public:
  using storage_type = std::unique_ptr<SDL_Joystick, deleter>;
};

/**
 * @class joystick
 *
 * @ingroup input
 *
 * @brief Represents various types of joysticks.
 *
 * @todo Cover `SDL_JoystickGetGUIDString`.
 *
 * @since 4.2.0
 *
 * @see `SDL_Joystick`
 * @see `joystick_handle`
 *
 * @headerfile joystick.hpp
 */
class joystick final : public basic_joystick<joystick>
{
 public:
  /**
   * @brief Creates a `joystick` instance based on an existing `SDL_Joystick*`.
   *
   * @param sdlJoystick a pointer to the `SDL_Joystick` that will be claimed.
   *
   * @throws exception if the supplied pointer is null.
   *
   * @since 4.2.0
   */
  CENTURION_API
  explicit joystick(owner<SDL_Joystick*> sdlJoystick);

  /**
   * @brief Creates a `joystick` instance based on a device index.
   *
   * @warning The device index is not the same as the instance ID used to
   * identify the joystick in future events.
   *
   * @param deviceIndex refers to the N'th joystick that is currently
   * recognized by SDL.
   *
   * @throws exceptions if there are no joysticks.
   * @throws sdl_error if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  CENTURION_API
  explicit joystick(int deviceIndex);

  /**
   * @brief Updates the state of all open joysticks.
   *
   * @note This is done automatically by the event loop if any joystick
   * events are enabled.
   *
   * @since 4.2.0
   */
  CENTURION_API
  static void update() noexcept;

  /**
   * @brief Locks the access to all joysticks.
   *
   * @details If you are using the joystick API from multiple threads you
   * should use this method to restrict access to the joysticks.
   *
   * @see SDL_LockJoysticks
   * @since 4.2.0
   */
  CENTURION_API
  static void lock() noexcept;

  /**
   * @brief Unlocks the access to all joysticks.
   *
   * @see SDL_UnlockJoysticks
   * @since 4.2.0
   */
  CENTURION_API
  static void unlock() noexcept;

  /**
   * @brief Specifies whether or not joystick event polling is enabled.
   *
   * @details If joystick event polling is disabled, then you must manually call
   * `joystick::update()` in order to update the joystick state.
   *
   * @note It's recommended to leave joystick event polling enabled.
   *
   * @warning Calling this function might cause all events currently in
   * the event queue to be deleted.
   *
   * @param enabled `true` if joystick event polling should be enabled;
   * `false` otherwise.
   *
   * @see SDL_JoystickEventState(int)
   *
   * @since 4.2.0
   */
  CENTURION_API
  static void set_polling(bool enabled) noexcept;

  /**
   * @brief Indicates whether or not joystick event polling is enabled.
   *
   * @return `true` if joystick event polling is enabled; `false` otherwise.
   *
   * @since 4.2.0
   */
  CENTURION_API
  static auto is_polling() noexcept -> bool;

  /**
   * @brief Returns a pointer to an `SDL_Joystick` associated with the ID.
   *
   * @param id the joystick ID associated with the desired joystick.
   *
   * @return a pointer to an `SDL_Joystick` instance if there is a joystick
   * associated with the supplied ID; null otherwise.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto from_instance_id(SDL_JoystickID id) noexcept -> SDL_Joystick*;

  /**
   * @brief Returns a pointer to the joystick associated with the specified
   * player index.
   *
   * @param playerIndex the player index of the desired joystick.
   *
   * @return a pointer to the associated joystick; `nullptr` if there is none.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto from_player_index(int playerIndex) noexcept -> SDL_Joystick*;

  /**
   * @brief Returns the amount of currently available joysticks.
   *
   * @return the current amount of available joysticks; `nothing` if
   * something goes wrong.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto amount() noexcept -> std::optional<int>;

  /**
   * @brief Returns the GUID for the joystick associated with the specified
   * device index.
   *
   * @note The GUID is implementation-dependent.
   * @note This function can be called before any joysticks are opened.
   *
   * @param deviceIndex refers to the N'th joystick that is currently recognized
   * by SDL.
   *
   * @return the GUID of the joystick associated with the device index.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto guid(int deviceIndex) noexcept -> SDL_JoystickGUID;

  /**
   * @brief Returns the player index of the joystick associated with the
   * specified device index.
   *
   * @note This method can be called before any joysticks are opened.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the player index of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto player_index(int deviceIndex) noexcept -> std::optional<int>;

  /**
   * @brief Returns the USB vendor ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the USB vendor ID of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto vendor(int deviceIndex) noexcept -> std::optional<u16>;

  /**
   * @brief Returns the USB product ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the USB product ID of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto product(int deviceIndex) noexcept -> std::optional<u16>;

  /**
   * @brief Returns the product version for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the product version of the desired joystick; `nothing` if it
   * can't be obtained.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto product_version(int deviceIndex) noexcept -> std::optional<u16>;

  /**
   * @brief Returns the type of the joystick associated with the specified
   * device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the type of the specified joystick.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto get_type(int deviceIndex) noexcept -> type;

  /**
   * @brief Returns the instance ID for the joystick associated with the
   * specified device index.
   *
   * @param deviceIndex the device index of the joystick that will be queried.
   *
   * @return the instance ID of the desired joystick; `nothing` if it can't
   * be obtained.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto instance_id(int deviceIndex) noexcept
      -> std::optional<SDL_JoystickID>;

  /**
   * @brief Returns the associated with the joystick with the specified
   * device index.
   *
   * @param deviceIndex refers to the N'th joystick that is currently recognized
   * by SDL.
   *
   * @return the name associated with the joystick; `nullptr` if no name is
   * found.
   *
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto name(int deviceIndex) noexcept -> czstring;

  /**
   * @brief Returns a joystick GUID based on the supplied string.
   *
   * @param str the string used to obtain the GUID, can't be null.
   *
   * @return the obtained GUID.
   *
   * @see `SDL_JoystickGetGUIDFromString`
   * @since 4.2.0
   */
  CENTURION_QUERY
  static auto guid_from_string(nn_czstring str) noexcept -> SDL_JoystickGUID;

  /**
   * @brief Returns the maximum possible value of an axis control on a joystick.
   *
   * @return the maximum possible value of an axis control.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static constexpr auto axis_max() noexcept -> i16
  {
    return SDL_JOYSTICK_AXIS_MAX;
  }

  /**
   * @brief Returns the minimum possible value of an axis control on a joystick.
   *
   * @return the minimum possible value of an axis control.
   *
   * @since 4.2.0
   */
  [[nodiscard]] static constexpr auto axis_min() noexcept -> i16
  {
    return SDL_JOYSTICK_AXIS_MIN;
  }
};

/**
 * @brief Indicates whether or not two joystick power values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(
    joystick::power lhs,
    SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return static_cast<SDL_JoystickPowerLevel>(lhs) == rhs;
}

/**
 * @brief Indicates whether or not two joystick power values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(SDL_JoystickPowerLevel lhs,
                                               joystick::power rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two joystick power values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(
    joystick::power lhs,
    SDL_JoystickPowerLevel rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two joystick power values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side power type.
 * @param rhs the right-hand side power type.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_JoystickPowerLevel lhs,
                                               joystick::power rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two joystick type values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(joystick::type lhs,
                                               SDL_JoystickType rhs) noexcept
    -> bool
{
  return static_cast<SDL_JoystickType>(lhs) == rhs;
}

/**
 * @brief Indicates whether or not two joystick type values are the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values are the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator==(SDL_JoystickType lhs,
                                               joystick::type rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two joystick type values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(joystick::type lhs,
                                               SDL_JoystickType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not two joystick type values aren't the same.
 *
 * @ingroup input
 *
 * @param lhs the left-hand side joystick type value.
 * @param rhs the right-hand side joystick type value.
 *
 * @return `true` if the values aren't the same; `false` otherwise.
 *
 * @since 4.3.0
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_JoystickType lhs,
                                               joystick::type rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HEADER