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
 * @file font_cache.ipp
 *
 * @brief Provides the implementation of the templates in the `font_cache`
 * class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_FONT_CACHE_IMPLEMENTATION
#define CENTURION_FONT_CACHE_IMPLEMENTATION

#include "centurion_api.hpp"
#include "font_cache.hpp"
#include "surface.hpp"
#include "texture.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

template <typename... Args>
font_cache::font_cache(Args&&... args) : m_font{std::forward<Args>(args)...}
{}

template <typename... Args>
auto font_cache::unique(Args&&... args) -> uptr
{
  return std::make_unique<font_cache>(std::forward<Args>(args)...);
}

template <typename... Args>
auto font_cache::shared(Args&&... args) -> sptr
{
  return std::make_shared<font_cache>(std::forward<Args>(args)...);
}

template <typename Renderer>
void font_cache::store_blended_utf8(entt::id_type id,
                                    nn_czstring string,
                                    Renderer& renderer)
{
  store(id, renderer.render_blended_utf8(string, get_font()));
}

template <typename Renderer>
void font_cache::store_blended_wrapped_utf8(entt::id_type id,
                                            nn_czstring string,
                                            Renderer& renderer,
                                            u32 wrap)
{
  store(id, renderer.render_blended_wrapped_utf8(string, get_font(), wrap));
}

template <typename Renderer>
void font_cache::store_shaded_utf8(entt::id_type id,
                                   nn_czstring string,
                                   Renderer& renderer,
                                   const color& background)
{
  store(id, renderer.render_shaded_utf8(string, get_font(), background));
}

template <typename Renderer>
void font_cache::store_solid_utf8(entt::id_type id,
                                  nn_czstring string,
                                  Renderer& renderer)
{
  store(id, renderer.render_solid_utf8(string, get_font()));
}

template <typename Renderer>
void font_cache::store_blended_latin1(entt::id_type id,
                                      nn_czstring string,
                                      Renderer& renderer)
{
  store(id, renderer.render_blended_latin1(string, get_font()));
}

template <typename Renderer>
void font_cache::store_blended_wrapped_latin1(entt::id_type id,
                                              nn_czstring string,
                                              Renderer& renderer,
                                              u32 wrap)
{
  store(id, renderer.render_blended_wrapped_latin1(string, get_font(), wrap));
}

template <typename Renderer>
void font_cache::store_shaded_latin1(entt::id_type id,
                                     nn_czstring string,
                                     Renderer& renderer,
                                     const color& background)
{
  store(id, renderer.render_shaded_latin1(string, get_font(), background));
}

template <typename Renderer>
void font_cache::store_solid_latin1(entt::id_type id,
                                    nn_czstring string,
                                    Renderer& renderer)
{
  store(id, renderer.render_solid_latin1(string, get_font()));
}

template <typename Renderer>
void font_cache::store_blended_unicode(entt::id_type id,
                                       const unicode_string& string,
                                       Renderer& renderer)
{
  store(id, renderer.render_blended_unicode(string, get_font()));
}

template <typename Renderer>
void font_cache::store_blended_wrapped_unicode(entt::id_type id,
                                               const unicode_string& string,
                                               Renderer& renderer,
                                               u32 wrap)
{
  store(id, renderer.render_blended_wrapped_unicode(string, get_font(), wrap));
}

template <typename Renderer>
void font_cache::store_shaded_unicode(entt::id_type id,
                                      const unicode_string& string,
                                      Renderer& renderer,
                                      const color& background)
{
  store(id, renderer.render_shaded_unicode(string, get_font(), background));
}

template <typename Renderer>
void font_cache::store_solid_unicode(entt::id_type id,
                                     const unicode_string& string,
                                     Renderer& renderer)
{
  store(id, renderer.render_solid_unicode(string, get_font()));
}

template <typename Renderer>
void font_cache::add_glyph(Renderer& renderer, unicode glyph)
{
  if (has(glyph) || !m_font.is_glyph_provided(glyph)) {
    return;
  }

  m_glyphs.emplace(glyph,
                   glyph_data{create_glyph_texture(renderer, glyph),
                              m_font.get_metrics(glyph).value()});
}

template <typename Renderer>
auto font_cache::create_glyph_texture(Renderer& renderer, unicode glyph)
    -> texture
{
  const surface surf{TTF_RenderGlyph_Blended(
      m_font.get(), glyph, static_cast<SDL_Color>(renderer.get_color()))};
  return texture{renderer, surf};
}

template <typename Renderer>
void font_cache::add_range(Renderer& renderer, unicode begin, unicode end)
{
  for (unicode ch = begin; ch < end; ++ch) {
    add_glyph(renderer, ch);
  }
}

template <typename Renderer>
void font_cache::add_basic_latin(Renderer& renderer)
{
  // https://unicode-table.com/en/blocks/basic-latin/
  add_range(renderer, 0x20, 0x7F);
}

template <typename Renderer>
void font_cache::add_latin1_supplement(Renderer& renderer)
{
  // https://unicode-table.com/en/blocks/latin-1-supplement/
  add_range(renderer, 0xA0, 0x100);
}

template <typename Renderer>
void font_cache::add_latin1(Renderer& renderer)
{
  add_basic_latin(renderer);
  add_latin1_supplement(renderer);
}

}  // namespace centurion

#endif  // CENTURION_FONT_CACHE_IMPLEMENTATION
