/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_RENDER_HPP_
#define CENTURION_RENDER_HPP_

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

#include "color.hpp"
#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class renderer_flip
{
  none = SDL_FLIP_NONE,
  horizontal = SDL_FLIP_HORIZONTAL,
  vertical = SDL_FLIP_VERTICAL
};

[[nodiscard]] constexpr auto to_string(const renderer_flip flip) -> std::string_view
{
  switch (flip) {
    case renderer_flip::none:
      return "none";

    case renderer_flip::horizontal:
      return "horizontal";

    case renderer_flip::vertical:
      return "vertical";

    default:
      throw exception{"Did not recognize renderer flip value!"};
  }
}

inline auto operator<<(std::ostream& stream, const renderer_flip flip) -> std::ostream&
{
  return stream << to_string(flip);
}

struct renderer_scale final
{
  float x{};
  float y{};
};

template <typename T>
class basic_renderer;

using renderer = basic_renderer<detail::owner_tag>;
using renderer_handle = basic_renderer<detail::handle_tag>;

/**
 * Provides the primary 2D rendering API.
 *
 * Note, each window is associated with at most one renderer.
 *
 * \see renderer
 * \see renderer_handle
 * \see renderer_info
 */
template <typename T>
class basic_renderer final
{
 public:
  enum renderer_flags : uint32
  {
    software = SDL_RENDERER_SOFTWARE,              ///< Software renderer.
    accelerated = SDL_RENDERER_ACCELERATED,        ///< Hardware-accelerated.
    target_textures = SDL_RENDERER_TARGETTEXTURE,  ///< Supports target textures.
    vsync = SDL_RENDERER_PRESENTVSYNC              ///< Uses VSync.
  };

  explicit basic_renderer(maybe_owner<SDL_Renderer*> renderer) noexcept(detail::is_handle<T>)
      : mRenderer{renderer}
  {
    if constexpr (detail::is_owner<T>) {
      if (!get()) {
        throw exception{"Cannot create renderer from null pointer!"};
      }
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_renderer(const renderer& owner) noexcept : mRenderer{owner.get()}
  {}

  template <typename X>
  [[nodiscard]] auto make_texture(const basic_surface<X>& surface) const -> texture
  {
    if (auto* ptr = SDL_CreateTextureFromSurface(get(), surface.get())) {
      return texture{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

  [[nodiscard]] auto make_texture(const iarea& size,
                                  const pixel_format format,
                                  const texture_access access) const -> texture
  {
    if (auto* ptr = SDL_CreateTexture(get(),
                                      to_underlying(format),
                                      to_underlying(access),
                                      size.width,
                                      size.height)) {
      return texture{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

#ifndef CENTURION_NO_SDL_IMAGE

  [[nodiscard]] auto make_texture(const char* path) const -> texture
  {
    assert(path);
    if (auto* ptr = IMG_LoadTexture(get(), path)) {
      return texture{ptr};
    }
    else {
      throw img_error{};
    }
  }

  [[nodiscard]] auto make_texture(const std::string& path) const -> texture
  {
    return make_texture(path.c_str());
  }

#endif  // CENTURION_NO_SDL_IMAGE

  auto clear() noexcept -> result { return SDL_RenderClear(get()) == 0; }

  void clear_with(const color& color) noexcept
  {
    const auto previous = get_color();
    set_color(color);
    clear();
    set_color(previous);
  }

  void present() noexcept { SDL_RenderPresent(get()); }

  void fill() noexcept
  {
    cen::irect rect;
    rect.set_size(output_size());
    fill_rect(rect);
  }

  void fill_with(const color& color) noexcept
  {
    const auto previous = get_color();

    set_color(color);
    fill();

    set_color(previous);
  }

  template <typename X>
  auto draw_rect(const basic_rect<X>& rect) noexcept -> result
  {
    if constexpr (basic_rect<X>::integral) {
      return SDL_RenderDrawRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderDrawRectF(get(), rect.data()) == 0;
    }
  }

  template <typename X>
  auto fill_rect(const basic_rect<X>& rect) noexcept -> result
  {
    if constexpr (basic_rect<X>::integral) {
      return SDL_RenderFillRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderFillRectF(get(), rect.data()) == 0;
    }
  }

  template <typename X>
  auto draw_line(const basic_point<X>& start, const basic_point<X>& end) noexcept -> result
  {
    if constexpr (basic_point<X>::integral) {
      return SDL_RenderDrawLine(get(), start.x(), start.y(), end.x(), end.y()) == 0;
    }
    else {
      return SDL_RenderDrawLineF(get(), start.x(), start.y(), end.x(), end.y()) == 0;
    }
  }

  template <typename Container>
  auto draw_lines(const Container& container) noexcept -> result
  {
    using point_t = typename Container::value_type;  // a point of int or float
    using value_t = typename point_t::value_type;    // either int or float

    if (!container.empty()) {
      const auto& front = container.front();
      const auto* first = front.data();

      if constexpr (std::is_same_v<value_t, int>) {
        return SDL_RenderDrawLines(get(), first, isize(container)) == 0;
      }
      else {
        return SDL_RenderDrawLinesF(get(), first, isize(container)) == 0;
      }
    }
    else {
      return failure;
    }
  }

  template <typename X>
  auto draw_point(const basic_point<X>& point) noexcept -> result
  {
    if constexpr (basic_point<X>::integral) {
      return SDL_RenderDrawPoint(get(), point.x(), point.y()) == 0;
    }
    else {
      return SDL_RenderDrawPointF(get(), point.x(), point.y()) == 0;
    }
  }

  template <typename X>
  void draw_circle(const basic_point<X>& position, const float radius) noexcept
  {
    using value_t = typename basic_point<X>::value_type;

    auto error = -radius;
    auto x = radius - 0.5f;
    auto y = 0.5f;

    const auto cx = static_cast<float>(position.x()) - 0.5f;
    const auto cy = static_cast<float>(position.y()) - 0.5f;

    while (x >= y) {
      draw_point<value_t>({static_cast<value_t>(cx + x), static_cast<value_t>(cy + y)});
      draw_point<value_t>({static_cast<value_t>(cx + y), static_cast<value_t>(cy + x)});

      if (x != 0) {
        draw_point<value_t>({static_cast<value_t>(cx - x), static_cast<value_t>(cy + y)});
        draw_point<value_t>({static_cast<value_t>(cx + y), static_cast<value_t>(cy - x)});
      }

      if (y != 0) {
        draw_point<value_t>({static_cast<value_t>(cx + x), static_cast<value_t>(cy - y)});
        draw_point<value_t>({static_cast<value_t>(cx - y), static_cast<value_t>(cy + x)});
      }

      if (x != 0 && y != 0) {
        draw_point<value_t>({static_cast<value_t>(cx - x), static_cast<value_t>(cy - y)});
        draw_point<value_t>({static_cast<value_t>(cx - y), static_cast<value_t>(cy - x)});
      }

      error += y;
      ++y;
      error += y;

      if (error >= 0) {
        --x;
        error -= x;
        error -= x;
      }
    }
  }

  template <typename X>
  void fill_circle(const basic_point<X>& center, const float radius)
  {
    const auto cx = static_cast<float>(center.x());
    const auto cy = static_cast<float>(center.y());

    for (auto dy = 1.0f; dy <= radius; dy += 1.0f) {
      const auto dx = std::floor(std::sqrt((2.0f * radius * dy) - (dy * dy)));
      draw_line<float>({cx - dx, cy + dy - radius}, {cx + dx, cy + dy - radius});
      draw_line<float>({cx - dx, cy - dy + radius}, {cx + dx, cy - dy + radius});
    }
  }

  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture, const basic_point<Y>& pos) noexcept -> result
  {
    if constexpr (basic_point<Y>::floating) {
      const auto size = texture.size().as_f();
      const SDL_FRect dst{pos.x(), pos.y(), size.width, size.height};
      return SDL_RenderCopyF(get(), texture.get(), nullptr, &dst) == 0;
    }
    else {
      const SDL_Rect dst{pos.x(), pos.y(), texture.width(), texture.height()};
      return SDL_RenderCopy(get(), texture.get(), nullptr, &dst) == 0;
    }
  }

  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture, const basic_rect<Y>& dst) noexcept -> result
  {
    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), nullptr, dst.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), nullptr, dst.data()) == 0;
    }
  }

  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture,
              const irect& src,
              const basic_rect<Y>& dst) noexcept -> result
  {
    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), src.data(), dst.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), src.data(), dst.data()) == 0;
    }
  }

  template <typename X, typename Y>
  auto render(const basic_texture<X>& texture,
              const irect& src,
              const basic_rect<Y>& dst,
              const double angle) noexcept -> result
  {
    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyExF(get(),
                               texture.get(),
                               src.data(),
                               dst.data(),
                               angle,
                               nullptr,
                               SDL_FLIP_NONE) == 0;
    }
    else {
      return SDL_RenderCopyEx(get(),
                              texture.get(),
                              src.data(),
                              dst.data(),
                              angle,
                              nullptr,
                              SDL_FLIP_NONE) == 0;
    }
  }

  template <typename X, typename Y, typename Z>
  auto render(const basic_texture<X>& texture,
              const irect& src,
              const basic_rect<Y>& dst,
              const double angle,
              const basic_point<Z>& center,
              const renderer_flip flip) noexcept -> result
  {
    static_assert(std::is_same_v<typename basic_rect<Y>::value_type,
                                 typename basic_point<Z>::value_type>,
                  "Destination rectangle and center point must have the same "
                  "value types (int or float)!");

    if constexpr (basic_rect<Y>::floating) {
      return SDL_RenderCopyExF(get(),
                               texture.get(),
                               src.data(),
                               dst.data(),
                               angle,
                               center.data(),
                               static_cast<SDL_RendererFlip>(flip)) == 0;
    }
    else {
      return SDL_RenderCopyEx(get(),
                              texture.get(),
                              src.data(),
                              dst.data(),
                              angle,
                              center.data(),
                              static_cast<SDL_RendererFlip>(flip)) == 0;
    }
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  template <usize Size>
  auto render_geo(bounded_array_ref<const SDL_Vertex, Size> vertices) noexcept -> result
  {
    return SDL_RenderGeometry(mRenderer,
                              nullptr,
                              vertices,
                              static_cast<int>(Size),
                              nullptr,
                              0) == 0;
  }

  template <usize VertexCount, usize IndexCount>
  auto render_geo(bounded_array_ref<const SDL_Vertex, VertexCount> vertices,
                  bounded_array_ref<const int, IndexCount> indices) noexcept -> result
  {
    static_assert(IndexCount <= VertexCount);
    return SDL_RenderGeometry(mRenderer,
                              nullptr,
                              vertices,
                              static_cast<int>(VertexCount),
                              indices,
                              static_cast<int>(IndexCount)) == 0;
  }

  template <typename X, usize Size>
  auto render_geo(const basic_texture<X>& texture,
                  bounded_array_ref<const SDL_Vertex, Size> vertices) noexcept -> result
  {
    return SDL_RenderGeometry(mRenderer,
                              texture.get(),
                              vertices,
                              static_cast<int>(Size),
                              nullptr,
                              0) == 0;
  }

  template <typename X, usize VertexCount, usize IndexCount>
  auto render_geo(const basic_texture<X>& texture,
                  bounded_array_ref<const SDL_Vertex, VertexCount>& vertices,
                  bounded_array_ref<const int, IndexCount>& indices) noexcept -> result
  {
    static_assert(IndexCount <= VertexCount);
    return SDL_RenderGeometry(mRenderer,
                              texture.get(),
                              vertices,
                              static_cast<int>(VertexCount),
                              indices,
                              static_cast<int>(IndexCount)) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  auto reset_target() noexcept -> result { return SDL_SetRenderTarget(get(), nullptr) == 0; }

  template <typename X>
  auto set_target(basic_texture<X>& target) noexcept -> result
  {
    assert(target.is_target());
    return SDL_SetRenderTarget(get(), target.get()) == 0;
  }

  [[nodiscard]] auto get_target() noexcept -> texture_handle
  {
    return texture_handle{SDL_GetRenderTarget(get())};
  }

  auto reset_clip() noexcept -> result { return SDL_RenderSetClipRect(get(), nullptr) == 0; }

  auto set_clip(const irect& area) noexcept -> result
  {
    return SDL_RenderSetClipRect(get(), area.data()) == 0;
  }

  [[nodiscard]] auto clip() const noexcept -> maybe<irect>
  {
    irect rect;
    SDL_RenderGetClipRect(get(), rect.data());
    if (rect.has_area()) {
      return rect;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto is_clipping_enabled() const noexcept -> bool
  {
    return SDL_RenderIsClipEnabled(get());
  }

  auto set_logical_size(const iarea size) noexcept -> result
  {
    assert(size.width >= 0);
    assert(size.height >= 0);
    return SDL_RenderSetLogicalSize(get(), size.width, size.height) == 0;
  }

  auto set_logical_integer_scaling(const bool enabled) noexcept -> result
  {
    return SDL_RenderSetIntegerScale(get(), enabled ? SDL_TRUE : SDL_FALSE) == 0;
  }

  [[nodiscard]] auto logical_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_RenderGetLogicalSize(get(), &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto using_integer_logical_scaling() const noexcept -> bool
  {
    return SDL_RenderGetIntegerScale(get());
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto to_logical(const int realX, const int realY) const noexcept -> fpoint
  {
    float logicalX{};
    float logicalY{};
    SDL_RenderWindowToLogical(get(), realX, realY, &logicalX, &logicalY);
    return {logicalX, logicalY};
  }

  [[nodiscard]] auto to_logical(const ipoint& real) const noexcept -> fpoint
  {
    return to_logical(real.x(), real.y());
  }

  [[nodiscard]] auto from_logical(const float logicalX, const float logicalY) const noexcept
      -> ipoint
  {
    int realX{};
    int realY{};
    SDL_RenderLogicalToWindow(get(), logicalX, logicalY, &realX, &realY);
    return {realX, realY};
  }

  [[nodiscard]] auto from_logical(const fpoint& logical) const noexcept -> ipoint
  {
    return from_logical(logical.x(), logical.y());
  }

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 18)

  auto set_color(const color& color) noexcept -> result
  {
    return SDL_SetRenderDrawColor(get(),
                                  color.red(),
                                  color.green(),
                                  color.blue(),
                                  color.alpha()) == 0;
  }

  auto set_blend_mode(const blend_mode mode) noexcept -> result
  {
    return SDL_SetRenderDrawBlendMode(get(), static_cast<SDL_BlendMode>(mode)) == 0;
  }

  auto set_viewport(const irect& viewport) noexcept -> result
  {
    return SDL_RenderSetViewport(get(), viewport.data()) == 0;
  }

  auto set_scale(const renderer_scale scale) noexcept -> result
  {
    assert(scale.x > 0);
    assert(scale.y > 0);
    return SDL_RenderSetScale(get(), scale.x, scale.y) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  auto set_vsync(const bool enabled) noexcept -> result
  {
    return SDL_RenderSetVSync(get(), enabled ? 1 : 0) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto get_color() const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    uint8 alpha{};
    SDL_GetRenderDrawColor(get(), &red, &green, &blue, &alpha);
    return {red, green, blue, alpha};
  }

  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetRenderDrawBlendMode(get(), &mode);
    return static_cast<blend_mode>(mode);
  }

  [[nodiscard]] auto viewport() const noexcept -> irect
  {
    irect viewport{};
    SDL_RenderGetViewport(get(), viewport.data());
    return viewport;
  }

  [[nodiscard]] auto scale() const noexcept -> renderer_scale
  {
    renderer_scale scale;
    SDL_RenderGetScale(get(), &scale.x, &scale.y);
    return scale;
  }

  [[nodiscard]] auto capture(const pixel_format format) const -> surface
  {
    surface image{output_size(), format};

    if (!image.lock()) {
      throw sdl_error{};
    }

    if (const auto res =
            SDL_RenderReadPixels(get(), nullptr, 0, image.pixel_data(), image.pitch());
        res == -1) {
      throw sdl_error{};
    }

    image.unlock();
    return image;
  }

  [[nodiscard]] auto output_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetRendererOutputSize(get(), &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Renderer* { return mRenderer.get(); }

  /// Indicates whether a handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mRenderer != nullptr;
  }

  [[nodiscard]] constexpr static auto default_flags() noexcept -> uint32
  {
    return accelerated | vsync;
  }

 private:
  detail::pointer<T, SDL_Renderer> mRenderer;
};

template <typename T>
[[nodiscard]] auto to_string(const basic_renderer<T>& renderer) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("renderer(data: {})", detail::address_of(renderer.get()));
#else
  return "renderer(data: " + detail::address_of(renderer.get()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_renderer<T>& renderer) -> std::ostream&
{
  return stream << to_string(renderer);
}

/// Provides information about a renderer.
class renderer_info final
{
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
      throw exception{"Invalid pixel format index!"};
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

  explicit renderer_info(const SDL_RendererInfo info) noexcept : mInfo{info} {}
};

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

template <typename T>
[[nodiscard]] auto get_info(const basic_renderer<T>& renderer) noexcept -> maybe<renderer_info>
{
  SDL_RendererInfo info{};
  if (SDL_GetRendererInfo(renderer.get(), &info) == 0) {
    return renderer_info{info};
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto render_driver_count() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

[[nodiscard]] inline auto video_driver_count() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

}  // namespace cen

#endif  // CENTURION_RENDER_HPP_
