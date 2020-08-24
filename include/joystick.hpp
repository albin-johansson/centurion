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
#include <type_traits>

#include "basic_joystick.hpp"
#include "button_state.hpp"
#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "detail/centurion_utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

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
class joystick_traits<joystick>
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
   * @typedef uptr
   *
   * @brief Simple alias for a unique pointer to a joystick.
   *
   * @since 5.0.0
   */
  using uptr = std::unique_ptr<joystick>;

  /**
   * @typedef sptr
   *
   * @brief Simple alias for a shared pointer to a joystick.
   *
   * @since 5.0.0
   */
  using sptr = std::shared_ptr<joystick>;

  /**
   * @typedef wptr
   *
   * @brief Simple alias for a weak pointer to a joystick.
   *
   * @since 5.0.0
   */
  using wptr = std::weak_ptr<joystick>;

  /**
   * @brief Creates a `joystick` instance based on an existing `SDL_Joystick*`.
   *
   * @pre `sdlJoystick` must not be null.
   *
   * @param sdlJoystick a pointer to the `SDL_Joystick` that will be claimed.
   *
   * @since 4.2.0
   */
  CENTURION_API
  explicit joystick(nn_owner<SDL_Joystick*> sdlJoystick) noexcept;

  /**
   * @brief Creates a `joystick` instance based on a device index.
   *
   * @warning The device index is not the same as the instance ID used to
   * identify the joystick in future events.
   *
   * @param deviceIndex refers to the N'th joystick that is currently
   * recognized by SDL.
   *
   * @throws centurion_exceptions if there are no joysticks.
   * @throws sdl_error if the joystick cannot be created.
   *
   * @since 4.2.0
   */
  CENTURION_API
  explicit joystick(int deviceIndex);

  /**
   * @copydoc joystick(int)
   */
  CENTURION_QUERY
  static auto unique(int deviceIndex) -> uptr;

  /**
   * @copydoc joystick(nn_owner<SDL_Joystick*>)
   */
  CENTURION_QUERY
  static auto unique(nn_owner<SDL_Joystick*> sdlJoystick) -> uptr;

  /**
   * @copydoc joystick(int)
   */
  CENTURION_QUERY
  static auto shared(int deviceIndex) -> sptr;

  /**
   * @copydoc joystick(nn_owner<SDL_Joystick*>)
   */
  CENTURION_QUERY
  static auto shared(nn_owner<SDL_Joystick*> sdlJoystick) -> sptr;
};

static_assert(std::is_final_v<joystick>);
static_assert(std::is_nothrow_move_constructible_v<joystick>);
static_assert(std::is_nothrow_move_assignable_v<joystick>);
static_assert(!std::is_copy_constructible_v<joystick>);
static_assert(!std::is_copy_assignable_v<joystick>);

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

}  // namespace centurion

#endif  // CENTURION_JOYSTICK_HEADER