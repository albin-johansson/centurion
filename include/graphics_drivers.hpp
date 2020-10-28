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

#ifndef CENTURION_VIDEO_HEADER
#define CENTURION_VIDEO_HEADER

#include <SDL_render.h>
#include <SDL_video.h>

#include <memory>
#include <optional>
#include <string>
#include <type_traits>

#include "centurion_api.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \brief Returns the number of available rendering drivers.
 *
 * \ingroup graphics
 *
 * \note Usually there is only one available rendering driver.
 *
 * \return the number of available rendering drivers.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto num_render_drivers() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

/**
 * \brief Returns the number of available video drivers compiled into SDL.
 *
 * \ingroup graphics
 *
 * \return the number of available video drivers compiled into SDL.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto num_video_drivers() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

/**
 * \brief Returns the information associated with a rendering driver.
 *
 * \ingroup graphics
 *
 * \param index the index of the rendering driver to query.
 *
 * \return information about the specified rendering driver; `std::nullopt` if
 * something went wrong.
 *
 * \since 5.0.0
 */
CENTURION_QUERY
auto get_render_driver_info(int index) noexcept
    -> std::optional<SDL_RendererInfo>;

}  // namespace cen

#endif  // CENTURION_VIDEO_HEADER
