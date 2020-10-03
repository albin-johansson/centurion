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
 * @file window_utils.hpp
 *
 * @brief Provides utilities related to windows.
 *
 * @author Albin Johansson
 *
 * @todo SDL_GetKeyboardFocus()
 * @todo SDL_GetMouseFocus()
 * @todo SDL_GetWindowSurface(window) -> surface_handle
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_WINDOW_UTILS_HEADER
#define CENTURION_WINDOW_UTILS_HEADER

#include <SDL_video.h>

#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "renderer.hpp"
#include "window.hpp"

namespace cen {

/// @addtogroup graphics
/// @{

/**
 * @brief Returns a handle to the currently grabbed window.
 *
 * @return a handle to the currently grabbed window, might not refer to a
 * valid window if there is no grabbed window.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto get_grabbed_window() noexcept -> window_handle
{
  return window_handle{SDL_GetGrabbedWindow()};
}

/**
 * @brief Returns a handle to the window associated with the specified ID.
 *
 * @param id the ID associated with the desired window.
 *
 * @return a handle to the window associated with the ID, might not refer to a
 * valid window if there no matching window.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto get_window_from_id(u32 id) noexcept -> window_handle
{
  return window_handle{SDL_GetWindowFromID(id)};
}

/**
 * @brief Returns a handle to the renderer associated with a window.
 *
 * @details The returned handle will be null if the supplied window doesn't
 * have an associated renderer.
 *
 * @note You should always check whether or not the returned handle contains
 * a valid renderer pointer before using it!
 *
 * @tparam T the type of the derived window.
 *
 * @param window the window associated with the desired renderer.
 *
 * @return a handle to the associated renderer, might not contain a valid
 * renderer pointer.
 *
 * @since 5.0.0
 */
template <typename T>
[[nodiscard]] auto get_renderer(const basic_window<T>& window) noexcept
    -> renderer_handle
{
  return renderer_handle{SDL_GetRenderer(window.get())};
}

/// @}

}  // namespace cen

#endif  // CENTURION_WINDOW_UTILS_HEADER