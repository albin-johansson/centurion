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
 * @file basic_renderer.ipp
 *
 * @brief Provides the implementation of the `basic_renderer` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_BASIC_RENDERER_IMPLEMENTATION
#define CENTURION_BASIC_RENDERER_IMPLEMENTATION

#include <type_traits>  // is_same_v

#include "centurion_api.hpp"

// clang-format off
#include "basic_renderer.hpp"
// clang-format on

#include "font.hpp"
#include "font_cache.hpp"
#include "surface.hpp"
#include "unicode_string.hpp"
#include "texture.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

template <typename Derived>
void basic_renderer<Derived>::clear() noexcept
{
  SDL_RenderClear(ptr());
}

template <typename Derived>
void basic_renderer<Derived>::clear_with(const color& color) noexcept
{
  const auto oldColor = get_color();

  set_color(color);
  clear();

  set_color(oldColor);
}

template <typename Derived>
void basic_renderer<Derived>::present() noexcept
{
  SDL_RenderPresent(ptr());
}

template <typename Derived>
template <typename T>
void basic_renderer<Derived>::draw_rect(const basic_rect<T>& rect) noexcept
{
  if constexpr (basic_rect<T>::isIntegral) {
    SDL_RenderDrawRect(ptr(), static_cast<const SDL_Rect*>(rect));
  } else {
    SDL_RenderDrawRectF(ptr(), static_cast<const SDL_FRect*>(rect));
  }
}

template <typename Derived>
template <typename T>
void basic_renderer<Derived>::fill_rect(const basic_rect<T>& rect) noexcept
{
  if constexpr (basic_rect<T>::isIntegral) {
    SDL_RenderFillRect(ptr(), static_cast<const SDL_Rect*>(rect));
  } else {
    SDL_RenderFillRectF(ptr(), static_cast<const SDL_FRect*>(rect));
  }
}

template <typename Derived>
template <typename T>
void basic_renderer<Derived>::draw_line(const basic_point<T>& start,
                                        const basic_point<T>& end) noexcept
{
  if constexpr (basic_point<T>::isIntegral) {
    SDL_RenderDrawLine(ptr(), start.x(), start.y(), end.x(), end.y());
  } else {
    SDL_RenderDrawLineF(ptr(), start.x(), start.y(), end.x(), end.y());
  }
}

template <typename Derived>
template <typename Container>
void basic_renderer<Derived>::draw_lines(const Container& container) noexcept
{
  using point_t = typename Container::value_type;  // a point of int or float
  using value_t = typename point_t::value_type;    // either int or float

  if (!container.empty()) {
    const auto& front = container.front();

    if constexpr (std::is_same_v<value_t, int>) {
      const auto* first = static_cast<const SDL_Point*>(front);
      SDL_RenderDrawLines(ptr(), first, static_cast<int>(container.size()));
    } else {
      const auto* first = static_cast<const SDL_FPoint*>(front);
      SDL_RenderDrawLinesF(ptr(), first, static_cast<int>(container.size()));
    }
  }
}

template <typename Derived>
auto basic_renderer<Derived>::render_text(owner<SDL_Surface*> s) -> texture
{
  surface surface{s};
  texture texture{SDL_CreateTextureFromSurface(ptr(), surface.get())};
  return texture;
}

template <typename Derived>
auto basic_renderer<Derived>::render_blended_utf8(nn_czstring str,
                                                  const font& font) -> texture
{
  return render_text(TTF_RenderUTF8_Blended(
      font.get(), str, static_cast<SDL_Color>(get_color())));
}

template <typename Derived>
auto basic_renderer<Derived>::render_blended_wrapped_utf8(nn_czstring str,
                                                          const font& font,
                                                          u32 wrap) -> texture
{
  return render_text(TTF_RenderUTF8_Blended_Wrapped(
      font.get(), str, static_cast<SDL_Color>(get_color()), wrap));
}

template <typename Derived>
auto basic_renderer<Derived>::render_shaded_utf8(nn_czstring str,
                                                 const font& font,
                                                 const color& background)
    -> texture
{
  return render_text(TTF_RenderUTF8_Shaded(font.get(),
                                           str,
                                           static_cast<SDL_Color>(get_color()),
                                           static_cast<SDL_Color>(background)));
}

template <typename Derived>
auto basic_renderer<Derived>::render_solid_utf8(nn_czstring str,
                                                const font& font) -> texture
{
  return render_text(TTF_RenderUTF8_Solid(
      font.get(), str, static_cast<SDL_Color>(get_color())));
}

template <typename Derived>
auto basic_renderer<Derived>::render_blended_latin1(nn_czstring str,
                                                    const font& font) -> texture
{
  return render_text(TTF_RenderText_Blended(
      font.get(), str, static_cast<SDL_Color>(get_color())));
}

template <typename Derived>
auto basic_renderer<Derived>::render_blended_wrapped_latin1(nn_czstring str,
                                                            const font& font,
                                                            u32 wrap) -> texture
{
  return render_text(TTF_RenderText_Blended_Wrapped(
      font.get(), str, static_cast<SDL_Color>(get_color()), wrap));
}

template <typename Derived>
auto basic_renderer<Derived>::render_shaded_latin1(nn_czstring str,
                                                   const font& font,
                                                   const color& background)
    -> texture
{
  return render_text(TTF_RenderText_Shaded(font.get(),
                                           str,
                                           static_cast<SDL_Color>(get_color()),
                                           static_cast<SDL_Color>(background)));
}

template <typename Derived>
auto basic_renderer<Derived>::render_solid_latin1(nn_czstring str,
                                                  const font& font) -> texture
{
  return render_text(TTF_RenderText_Solid(
      font.get(), str, static_cast<SDL_Color>(get_color())));
}

template <typename Derived>
auto basic_renderer<Derived>::render_blended_unicode(const unicode_string& str,
                                                     const font& font)
    -> texture
{
  return render_text(TTF_RenderUNICODE_Blended(
      font.get(), str.data(), static_cast<SDL_Color>(get_color())));
}

template <typename Derived>
auto basic_renderer<Derived>::render_blended_wrapped_unicode(
    const unicode_string& str,
    const font& font,
    u32 wrap) -> texture
{
  return render_text(TTF_RenderUNICODE_Blended_Wrapped(
      font.get(), str.data(), static_cast<SDL_Color>(get_color()), wrap));
}

template <typename Derived>
auto basic_renderer<Derived>::render_shaded_unicode(const unicode_string& str,
                                                    const font& font,
                                                    const color& background)
    -> texture
{
  return render_text(
      TTF_RenderUNICODE_Shaded(font.get(),
                               str.data(),
                               static_cast<SDL_Color>(get_color()),
                               static_cast<SDL_Color>(background)));
}

template <typename Derived>
auto basic_renderer<Derived>::render_solid_unicode(const unicode_string& str,
                                                   const font& font) -> texture
{
  return render_text(TTF_RenderUNICODE_Solid(
      font.get(), str.data(), static_cast<SDL_Color>(get_color())));
}

template <typename Derived>
auto basic_renderer<Derived>::render_glyph(const font_cache& cache,
                                           unicode glyph,
                                           const ipoint& position) -> int
{
  const auto& [texture, glyphMetrics] = cache.at(glyph);

  const auto outline = cache.get_font().outline();

  // SDL_ttf handles the y-axis alignment
  const auto x = position.x() + glyphMetrics.minX - outline;
  const auto y = position.y() - outline;

  render(texture, ipoint{x, y});

  return x + glyphMetrics.advance;
}

template <typename Derived>
template <typename String>
void basic_renderer<Derived>::render_text(const font_cache& cache,
                                          const String& str,
                                          ipoint position)
{
  const auto originalX = position.x();
  for (const unicode glyph : str) {
    if (glyph == '\n') {
      position.set_x(originalX);
      position.set_y(position.y() + cache.get_font().line_skip());
    } else {
      const auto x = render_glyph(cache, glyph, position);
      position.set_x(x);
    }
  }
}

template <typename Derived>
template <typename T>
void basic_renderer<Derived>::render(const texture& texture,
                                     const basic_point<T>& position) noexcept
{
  if constexpr (basic_point<T>::isFloating) {
    const SDL_FRect dst{position.x(),
                        position.y(),
                        static_cast<float>(texture.width()),
                        static_cast<float>(texture.height())};
    SDL_RenderCopyF(ptr(), texture.get(), nullptr, &dst);
  } else {
    const SDL_Rect dst{
        position.x(), position.y(), texture.width(), texture.height()};
    SDL_RenderCopy(ptr(), texture.get(), nullptr, &dst);
  }
}

template <typename Derived>
template <typename T>
void basic_renderer<Derived>::render(const texture& texture,
                                     const basic_rect<T>& destination) noexcept
{
  if constexpr (basic_rect<T>::isFloating) {
    SDL_RenderCopyF(ptr(),
                    texture.get(),
                    nullptr,
                    static_cast<const SDL_FRect*>(destination));
  } else {
    SDL_RenderCopy(ptr(),
                   texture.get(),
                   nullptr,
                   static_cast<const SDL_Rect*>(destination));
  }
}

template <typename Derived>
template <typename T>
void basic_renderer<Derived>::render(const texture& texture,
                                     const irect& source,
                                     const basic_rect<T>& destination) noexcept
{
  if constexpr (basic_rect<T>::isFloating) {
    SDL_RenderCopyF(ptr(),
                    texture.get(),
                    static_cast<const SDL_Rect*>(source),
                    static_cast<const SDL_FRect*>(destination));
  } else {
    SDL_RenderCopy(ptr(),
                   texture.get(),
                   static_cast<const SDL_Rect*>(source),
                   static_cast<const SDL_Rect*>(destination));
  }
}

template <typename Derived>
template <typename T>
void basic_renderer<Derived>::render(const texture& texture,
                                     const irect& source,
                                     const basic_rect<T>& destination,
                                     double angle) noexcept
{
  if constexpr (basic_rect<T>::isFloating) {
    SDL_RenderCopyExF(ptr(),
                      texture.get(),
                      static_cast<const SDL_Rect*>(source),
                      static_cast<const SDL_FRect*>(destination),
                      angle,
                      nullptr,
                      SDL_FLIP_NONE);
  } else {
    SDL_RenderCopyEx(ptr(),
                     texture.get(),
                     static_cast<const SDL_Rect*>(source),
                     static_cast<const SDL_Rect*>(destination),
                     angle,
                     nullptr,
                     SDL_FLIP_NONE);
  }
}

template <typename Derived>
template <typename R, typename P>
void basic_renderer<Derived>::render(const texture& texture,
                                     const irect& source,
                                     const basic_rect<R>& destination,
                                     double angle,
                                     const basic_point<P>& center) noexcept
{
  static_assert(std::is_same_v<typename basic_rect<R>::value_type,
                               typename basic_point<P>::value_type>,
                "Destination rectangle and center point must have the same "
                "value types (int or float)!");

  if constexpr (basic_rect<R>::isFloating) {
    SDL_RenderCopyExF(ptr(),
                      texture.get(),
                      static_cast<const SDL_Rect*>(source),
                      static_cast<const SDL_FRect*>(destination),
                      angle,
                      static_cast<const SDL_FPoint*>(center),
                      SDL_FLIP_NONE);
  } else {
    SDL_RenderCopyEx(ptr(),
                     texture.get(),
                     static_cast<const SDL_Rect*>(source),
                     static_cast<const SDL_Rect*>(destination),
                     angle,
                     static_cast<const SDL_Point*>(center),
                     SDL_FLIP_NONE);
  }
}

template <typename Derived>
template <typename R, typename P>
void basic_renderer<Derived>::render(const texture& texture,
                                     const irect& source,
                                     const basic_rect<R>& destination,
                                     double angle,
                                     const basic_point<P>& center,
                                     SDL_RendererFlip flip) noexcept
{
  static_assert(std::is_same_v<typename basic_rect<R>::value_type,
                               typename basic_point<P>::value_type>,
                "Destination rectangle and center point must have the same "
                "value types (int or float)!");

  if constexpr (basic_rect<R>::isFloating) {
    SDL_RenderCopyExF(ptr(),
                      texture.get(),
                      static_cast<const SDL_Rect*>(source),
                      static_cast<const SDL_FRect*>(destination),
                      angle,
                      static_cast<const SDL_FPoint*>(center),
                      flip);
  } else {
    SDL_RenderCopyEx(ptr(),
                     texture.get(),
                     static_cast<const SDL_Rect*>(source),
                     static_cast<const SDL_Rect*>(destination),
                     angle,
                     static_cast<const SDL_Point*>(center),
                     flip);
  }
}

template <typename Derived>
void basic_renderer<Derived>::set_color(const color& color) noexcept
{
  SDL_SetRenderDrawColor(
      ptr(), color.red(), color.green(), color.blue(), color.alpha());
}
template <typename Derived>
void basic_renderer<Derived>::set_clip(std::optional<irect> area) noexcept
{
  if (area) {
    SDL_RenderSetClipRect(ptr(), static_cast<const SDL_Rect*>(*area));
  } else {
    SDL_RenderSetClipRect(ptr(), nullptr);
  }
}

template <typename Derived>
void basic_renderer<Derived>::set_viewport(const irect& viewport) noexcept
{
  SDL_RenderSetViewport(ptr(), static_cast<const SDL_Rect*>(viewport));
}

template <typename Derived>
void basic_renderer<Derived>::set_blend_mode(blend_mode mode) noexcept
{
  SDL_SetRenderDrawBlendMode(ptr(), static_cast<SDL_BlendMode>(mode));
}

template <typename Derived>
void basic_renderer<Derived>::set_target(const texture* target) noexcept
{
  if (target && target->is_target()) {
    SDL_SetRenderTarget(ptr(), target->get());
  } else {
    SDL_SetRenderTarget(ptr(), nullptr);
  }
}

template <typename Derived>
void basic_renderer<Derived>::set_scale(float xScale, float yScale) noexcept
{
  if ((xScale > 0) && (yScale > 0)) {
    SDL_RenderSetScale(ptr(), xScale, yScale);
  }
}

template <typename Derived>
void basic_renderer<Derived>::set_logical_size(const iarea& size) noexcept
{
  if ((size.width > 0) && (size.height > 0)) {
    SDL_RenderSetLogicalSize(ptr(), size.width, size.height);
  }
}

template <typename Derived>
void basic_renderer<Derived>::set_logical_integer_scale(bool enabled) noexcept
{
  SDL_RenderSetIntegerScale(ptr(), detail::convert_bool(enabled));
}

template <typename Derived>
auto basic_renderer<Derived>::logical_width() const noexcept -> int
{
  int width{};
  SDL_RenderGetLogicalSize(ptr(), &width, nullptr);
  return width;
}

template <typename Derived>
auto basic_renderer<Derived>::logical_height() const noexcept -> int
{
  int height{};
  SDL_RenderGetLogicalSize(ptr(), nullptr, &height);
  return height;
}

template <typename Derived>
auto basic_renderer<Derived>::logical_size() const noexcept -> iarea
{
  int width{};
  int height{};
  SDL_RenderGetLogicalSize(ptr(), &width, &height);
  return {width, height};
}

template <typename Derived>
auto basic_renderer<Derived>::x_scale() const noexcept -> float
{
  float xScale{};
  SDL_RenderGetScale(ptr(), &xScale, nullptr);
  return xScale;
}

template <typename Derived>
auto basic_renderer<Derived>::y_scale() const noexcept -> float
{
  float yScale{};
  SDL_RenderGetScale(ptr(), nullptr, &yScale);
  return yScale;
}

template <typename Derived>
auto basic_renderer<Derived>::scale() const noexcept -> std::pair<float, float>
{
  float xScale{};
  float yScale{};
  SDL_RenderGetScale(ptr(), &xScale, &yScale);
  return {xScale, yScale};
}

template <typename Derived>
auto basic_renderer<Derived>::clip() const noexcept -> std::optional<irect>
{
  irect rect{};
  SDL_RenderGetClipRect(ptr(), static_cast<SDL_Rect*>(rect));
  if (!rect.has_area()) {
    return std::nullopt;
  } else {
    return rect;
  }
}

template <typename Derived>
auto basic_renderer<Derived>::info() const noexcept
    -> std::optional<SDL_RendererInfo>
{
  SDL_RendererInfo info{};
  const auto result = SDL_GetRendererInfo(ptr(), &info);
  if (result == 0) {
    return info;
  } else {
    return std::nullopt;
  }
}

template <typename Derived>
auto basic_renderer<Derived>::output_width() const noexcept -> int
{
  int width{};
  SDL_GetRendererOutputSize(ptr(), &width, nullptr);
  return width;
}

template <typename Derived>
auto basic_renderer<Derived>::output_height() const noexcept -> int
{
  int height{};
  SDL_GetRendererOutputSize(ptr(), nullptr, &height);
  return height;
}

template <typename Derived>
auto basic_renderer<Derived>::output_size() const noexcept -> iarea
{
  int width{};
  int height{};
  SDL_GetRendererOutputSize(ptr(), &width, &height);
  return {width, height};
}

template <typename Derived>
auto basic_renderer<Derived>::get_blend_mode() const noexcept -> blend_mode
{
  SDL_BlendMode mode{};
  SDL_GetRenderDrawBlendMode(ptr(), &mode);
  return static_cast<enum blend_mode>(mode);
}

template <typename Derived>
auto basic_renderer<Derived>::flags() const noexcept -> u32
{
  SDL_RendererInfo info{};
  SDL_GetRendererInfo(ptr(), &info);
  return info.flags;
}

template <typename Derived>
auto basic_renderer<Derived>::is_vsync_enabled() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_PRESENTVSYNC);
}

template <typename Derived>
auto basic_renderer<Derived>::is_accelerated() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_ACCELERATED);
}

template <typename Derived>
auto basic_renderer<Derived>::is_software_based() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_SOFTWARE);
}

template <typename Derived>
auto basic_renderer<Derived>::supports_target_textures() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_TARGETTEXTURE);
}

template <typename Derived>
auto basic_renderer<Derived>::is_using_integer_logical_scaling() const noexcept
    -> bool
{
  return SDL_RenderGetIntegerScale(ptr());
}

template <typename Derived>
auto basic_renderer<Derived>::is_clipping_enabled() const noexcept -> bool
{
  return SDL_RenderIsClipEnabled(ptr());
}

template <typename Derived>
auto basic_renderer<Derived>::get_color() const noexcept -> color
{
  u8 red{};
  u8 green{};
  u8 blue{};
  u8 alpha{};
  SDL_GetRenderDrawColor(ptr(), &red, &green, &blue, &alpha);
  return {red, green, blue, alpha};
}

template <typename Derived>
auto basic_renderer<Derived>::viewport() const noexcept -> irect
{
  irect viewport{};
  SDL_RenderGetViewport(ptr(), static_cast<SDL_Rect*>(viewport));
  return viewport;
}

template <typename Derived>
auto basic_renderer<Derived>::ptr() noexcept -> SDL_Renderer*
{
  return static_cast<Derived*>(this)->get();
}

template <typename Derived>
auto basic_renderer<Derived>::ptr() const noexcept -> SDL_Renderer*
{
  return static_cast<const Derived*>(this)->get();
}

}  // namespace centurion

#endif  // CENTURION_BASIC_RENDERER_IMPLEMENTATION
