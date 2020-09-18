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
 * @file renderer_handle.hpp
 *
 * @brief Provides the `renderer_handle` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#include <SDL_video.h>

#include <ostream>
#include <string>
#include <type_traits>

#include "basic_renderer.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class renderer_handle
 *
 * @ingroup graphics
 *
 * @brief Represents a non-owning renderer.
 *
 * @warning It is undefined behaviour to invoke any member methods if the
 * internal renderer is null.
 *
 * @details This class is meant to be used when you want to utilize the same
 * rendering API as with the the `renderer` class, but you don't want the
 * renderer to claim ownership of the SDL renderer. In a nutshell, this class
 * is merely a wrapper around an `SDL_Renderer*`.
 *
 * However, there are some differences in functionality compared to the
 * `renderer` class. Firstly, renderer views don't support storing
 * fonts. Secondly, the translation viewport API isn't available with views.
 *
 * @note Naturally, since instances of this class don't own the associated
 * SDL renderer, you'll have to manually manage the lifetime of the
 * SDL renderer. In general, prefer `renderer` unless you absolutely cannot
 * claim ownership of the SDL renderer.
 *
 * @since 5.0.0
 *
 * @see `renderer`
 *
 * @headerfile renderer.hpp
 */
class renderer_handle final : public basic_renderer<renderer_handle>
{
 public:
  /**
   * @brief Creates a renderer handle instance.
   *
   * @param renderer a pointer to the SDL renderer that will be used, can be
   * null.
   *
   * @since 5.0.0
   */
  CENTURION_API
  renderer_handle(SDL_Renderer* renderer) noexcept;

  /**
   * @brief Creates a handle based on an existing `renderer`.
   *
   * @tparam FontKey the type of the font keys used by the renderer.
   *
   * @param renderer the renderer that will be viewed.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit renderer_handle(renderer& renderer) noexcept;

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
  explicit operator bool() const noexcept
  {
    return static_cast<bool>(m_renderer);
  }

  /**
   * @brief Returns a pointer to the associated SDL_Renderer.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However, it's useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated SDL_Renderer.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Renderer*
  {
    return m_renderer;
  }

 private:
  SDL_Renderer* m_renderer{};
};

static_assert(std::is_final_v<renderer_handle>);
static_assert(std::is_nothrow_destructible_v<renderer_handle>);
static_assert(std::is_nothrow_move_constructible_v<renderer_handle>);
static_assert(std::is_nothrow_move_assignable_v<renderer_handle>);

/**
 * @brief Returns a textual representation of a renderer handle.
 *
 * @ingroup graphics
 *
 * @param handle the renderer handle that will be converted.
 *
 * @return a textual representation of the renderer handle.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const renderer_handle& handle) -> std::string;

/**
 * @brief Prints a textual representation of a renderer handle.
 *
 * @ingroup graphics
 *
 * @param stream the stream that will be used.
 * @param handle the renderer handle that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto operator<<(std::ostream& stream, const renderer_handle& handle)
    -> std::ostream&;

}  // namespace cen
