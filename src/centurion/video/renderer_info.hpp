/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_VIDEO_RENDERER_INFO_HPP_
#define CENTURION_VIDEO_RENDERER_INFO_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>      // assert
#include <cmath>        // floor, sqrt
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string>       // string, string_literals
#include <string_view>  // string_view
#include <utility>      // pair

#include "../common/math.hpp"
#include "../common/primitives.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"
#include "color.hpp"
#include "renderer.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode_string.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

[[nodiscard]] inline auto render_driver_count() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

[[nodiscard]] inline auto video_driver_count() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

/// Provides information about a renderer.
class renderer_info final {
  template <typename T>
  friend auto get_info(const basic_renderer<T>& renderer) noexcept -> maybe<renderer_info>;

 public:
  using size_type = usize;

  [[nodiscard]] auto supported_flags() const noexcept -> uint32 { return mInfo.flags; }

  [[nodiscard]] auto has_vsync() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_PRESENTVSYNC;
  }

  [[nodiscard]] auto has_target_textures() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_TARGETTEXTURE;
  }

  [[nodiscard]] auto is_accelerated() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_ACCELERATED;
  }

  [[nodiscard]] auto is_software() const noexcept -> bool
  {
    return supported_flags() & SDL_RENDERER_SOFTWARE;
  }

  [[nodiscard]] auto format_count() const noexcept -> size_type
  {
    return static_cast<size_type>(mInfo.num_texture_formats);
  }

  [[nodiscard]] auto get_format(const size_type index) const -> pixel_format
  {
    if (index < format_count()) {
      return static_cast<pixel_format>(mInfo.texture_formats[index]);
    }
    else {
      throw exception {"Invalid pixel format index!"};
    }
  }

  [[nodiscard]] auto max_texture_size() const noexcept -> iarea
  {
    return {mInfo.max_texture_width, mInfo.max_texture_height};
  }

  [[nodiscard]] auto max_texture_width() const noexcept -> int
  {
    return mInfo.max_texture_width;
  }

  [[nodiscard]] auto max_texture_height() const noexcept -> int
  {
    return mInfo.max_texture_height;
  }

  [[nodiscard]] auto name() const noexcept -> const char* { return mInfo.name; }

 private:
  SDL_RendererInfo mInfo;

  explicit renderer_info(const SDL_RendererInfo info) noexcept : mInfo {info} {}
};

template <typename T>
[[nodiscard]] auto get_info(const basic_renderer<T>& renderer) noexcept -> maybe<renderer_info>
{
  SDL_RendererInfo info {};
  if (SDL_GetRendererInfo(renderer.get(), &info) == 0) {
    return renderer_info {info};
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto to_string(const renderer_info& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("renderer_info(name: '{}')", str_or_na(info.name()));
#else
  using namespace std::string_literals;
  return "renderer_info(name: '"s + str_or_na(info.name()) + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const renderer_info& info) -> std::ostream&
{
  return stream << to_string(info);
}

}  // namespace cen

#endif  // CENTURION_VIDEO_RENDERER_INFO_HPP_
