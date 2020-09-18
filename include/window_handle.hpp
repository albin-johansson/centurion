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
 * @file window_handle.hpp
 *
 * @brief Provides the `window_handle` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_WINDOW_HANDLE_HEADER
#define CENTURION_WINDOW_HANDLE_HEADER

#include <SDL_video.h>

#include <ostream>
#include <string>
#include <type_traits>

#include "centurion_api.hpp"
#include "window.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class window_handle
 *
 * @ingroup graphics
 *
 * @brief Represents a non-owning window.
 *
 * @details This class is meant to be used when you want to utilize the same
 * window API as with the the `window` class, but you don't want the
 * window to claim ownership of the SDL window. In a nutshell, this class
 * is merely a wrapper around an `SDL_Window*`.
 *
 * @note Naturally, since instances of this class don't own the associated
 * SDL window, you'll have to manually manage the lifetime of the
 * SDL window. In general, prefer `window` unless you absolutely
 * cannot claim ownership of the SDL window.
 *
 * @warning It is undefined behaviour to invoke a member function if the
 * internal pointer is null!
 *
 * @since 5.0.0
 *
 * @see `window`
 *
 * @headerfile window_handle.hpp
 */
class window_handle final : public basic_window<window_handle>
{
 public:
  /**
   * @brief Creates a `window_handle` based on the supplied SDL window pointer.
   *
   * @param window a pointer to an SDL window, can be null.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit window_handle(SDL_Window* window) noexcept;

  /**
   * @brief Creates a `window_handle` based on a `window` instance.
   *
   * @param window the Centurion window that provides the `SDL_Window` pointer.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit window_handle(const window& window) noexcept;

  /**
   * @brief Indicates whether or not the instance holds a non-null pointer.
   *
   * @warning It's undefined behaviour to invoke other member functions that
   * use the internal pointer if this function returns `false`.
   *
   * @return `true` if the instance holds a non-null pointer; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  explicit operator bool() const noexcept;

  /**
   * @brief Returns a pointer to the associated SDL window.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it is useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Window* { return m_window; }

 private:
  SDL_Window* m_window{};
};

static_assert(std::is_final_v<window_handle>);

static_assert(!std::is_default_constructible_v<window_handle>);
static_assert(std::is_nothrow_destructible_v<window_handle>);

static_assert(std::is_nothrow_move_assignable_v<window_handle>);
static_assert(std::is_nothrow_move_constructible_v<window_handle>);

static_assert(std::is_nothrow_copy_assignable_v<window_handle>);
static_assert(std::is_nothrow_copy_constructible_v<window_handle>);

/**
 * @brief Returns a textual representation of a window handle.
 *
 * @ingroup graphics
 *
 * @param handle the window handle that will be converted.
 *
 * @return a textual representation of the window handle.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const window_handle& handle) -> std::string;

/**
 * @brief Prints a textual representation of a window handle.
 *
 * @ingroup graphics
 *
 * @param stream the stream that will be used.
 * @param handle the window handle that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto operator<<(std::ostream& stream, const window_handle& handle)
    -> std::ostream&;

}  // namespace cen

#endif  // CENTURION_WINDOW_HANDLE_HEADER