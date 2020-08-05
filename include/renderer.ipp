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

#ifndef CENTURION_RENDERER_IMPLEMENTATION
#define CENTURION_RENDERER_IMPLEMENTATION

#include "centurion_api.hpp"
#include "renderer.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

template <typename T>
auto renderer::translate(const basic_point<T>& point) const noexcept
    -> basic_point<T>
{
  const auto rect = viewport();

  using value_type = typename basic_point<T>::value_type;

  const auto x = point.x() - static_cast<value_type>(rect.x());
  const auto y = point.y() - static_cast<value_type>(rect.y());

  return basic_point<T>{x, y};
}

template <typename T>
auto renderer::translate(const basic_rect<T>& rect) const noexcept
    -> basic_rect<T>
{
  return basic_rect<T>{translate(rect.position()), rect.size()};
}

template <typename T>
void renderer::draw_rect_t(const basic_rect<T>& rect) noexcept
{
  draw_rect(translate(rect));
}

template <typename T>
void renderer::fill_rect_t(const basic_rect<T>& rect) noexcept
{
  fill_rect(translate(rect));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const basic_point<T>& position) noexcept
{
  render(texture, translate(position));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const basic_rect<T>& destination) noexcept
{
  render(texture, translate(destination));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<T>& destination) noexcept
{
  render(texture, source, translate(destination));
}

template <typename T>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<T>& destination,
                        double angle) noexcept
{
  render(texture, source, translate(destination), angle);
}

template <typename R, typename P>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<R>& destination,
                        double angle,
                        const basic_point<P>& center) noexcept
{
  render(texture, source, translate(destination), angle, center);
}

template <typename R, typename P>
void renderer::render_t(const texture& texture,
                        const irect& source,
                        const basic_rect<R>& destination,
                        double angle,
                        const basic_point<P>& center,
                        SDL_RendererFlip flip) noexcept
{
  render(texture, source, translate(destination), angle, center, flip);
}

template <typename... Args>
void renderer::emplace_font(entt::id_type id, Args&&... args)
{
  if (m_fonts.find(id) != m_fonts.end()) {
    remove_font(id);
  }
  m_fonts.emplace(id, font{std::forward<Args>(args)...});
}

}  // namespace centurion

#endif  // CENTURION_RENDERER_IMPLEMENTATION
