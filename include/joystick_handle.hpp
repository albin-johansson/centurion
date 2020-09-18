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
 * @file joystick_handle.hpp
 *
 * @ingroup input
 *
 * @brief Provides the `joystick_handle` class.
 *
 * @author Albin Johansson
 *
 * @copyright MIT License
 *
 * @date 2019-2020
 */

#ifndef CENTURION_JOYSTICK_HANDLE_HEADER
#define CENTURION_JOYSTICK_HANDLE_HEADER

#include <SDL_joystick.h>

#include <type_traits>

#include "basic_joystick.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

class joystick_handle;

/**
 * @class joystick_traits<joystick_handle>
 *
 * @ingroup input
 *
 * @brief Provides traits for the `joystick_handle` class.
 *
 * @since 5.0.0
 *
 * @headerfile joystick.hpp
 */
template <>
class joystick_traits<joystick_handle>
{
 public:
  using storage_type = SDL_Joystick*;
};

/**
 * @class joystick_handle
 *
 * @ingroup input
 *
 * @brief Represents a non-owning joystick.
 *
 * @details This class is designed to be used where using `joystick` would be
 * impossible or unsuitable. It features the same joystick API as
 * the `joystick` class, the only difference being that a `joystick_handle`
 * doesn't manage the lifetime of the associated `SDL_Joystick*`.
 *
 * @note In the vast majority of cases, you'll want to use the `joystick`
 * class instead.
 *
 * @since 5.0.0
 *
 * @see `joystick`
 *
 * @headerfile joystick.hpp
 */
class joystick_handle final : public basic_joystick<joystick_handle>
{
 public:
  /**
   * @brief Creates a handle to a joystick.
   *
   * @param sdlJoystick the pointer to the SDL joystick, can safely be null.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit joystick_handle(SDL_Joystick* sdlJoystick) noexcept;

  /**
   * @brief Creates a handle based on the supplied `joystick` instance.
   *
   * @param joystick the joystick whose internal pointer will be copied.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit joystick_handle(joystick& joystick) noexcept;

  /**
   * @brief Indicates whether or not the handle holds a non-null pointer.
   *
   * @return `true` if the internal pointer is non-null; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  explicit operator bool() const noexcept;
};

/**
 * @brief Returns a handle to the joystick associated with the specified ID.
 *
 * @ingroup input
 *
 * @param id the joystick ID associated with the desired joystick.
 *
 * @return a handle to the joystick associated with the supplied ID, might be
 * empty.
 *
 * @since 4.2.0
 */
CENTURION_QUERY
auto joystick_from_instance_id(SDL_JoystickID id) noexcept -> joystick_handle;

/**
 * @brief Returns a handle to the joystick associated with the specified
 * player index.
 *
 * @ingroup input
 *
 * @param playerIndex the player index of the desired joystick.
 *
 * @return a handle to the associated joystick, which might be empty.
 *
 * @since 4.2.0
 */
CENTURION_QUERY
auto joystick_from_player_index(int playerIndex) noexcept -> joystick_handle;

static_assert(std::is_final_v<joystick_handle>);
static_assert(std::is_nothrow_move_constructible_v<joystick_handle>);
static_assert(std::is_nothrow_move_assignable_v<joystick_handle>);
static_assert(std::is_nothrow_copy_constructible_v<joystick_handle>);
static_assert(std::is_nothrow_copy_assignable_v<joystick_handle>);

}  // namespace cen

#endif  // CENTURION_JOYSTICK_HANDLE_HEADER
