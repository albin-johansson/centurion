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

#ifndef CENTURION_EXPERIMENTAL_FONT_HEADER
#define CENTURION_EXPERIMENTAL_FONT_HEADER

#include <SDL_ttf.h>

#include <algorithm>
#include <array>
#include <hashed_string.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "colors.hpp"
#include "font.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "surface.hpp"

namespace centurion::experimental {

using unicode = u16;

class font_cache final {
 public:
  font_cache(renderer& renderer, font&& font);

  [[nodiscard]] static auto unique(renderer& renderer, font&& font)
      -> std::unique_ptr<font_cache>;

  /**
   * @brief Renders a glyph at the specified position.
   *
   * @tparam T the font key type that the renderer uses.
   *
   * @param renderer the renderer that will be used.
   * @param glyph the glyph, in unicode, that will be rendered.
   * @param position the position of the rendered glyph.
   *
   * @return the x-coordinate of the next glyph to be rendered after the
   * current glyph.
   *
   * @since 5.0.0
   */
  auto render(renderer& renderer, unicode glyph, const point_i& position)
      -> int;

  void render(renderer& renderer, std::string_view str, point_i position);

  void render_cached(renderer& renderer,
                     entt::id_type id,
                     const point_i& position);

  void cache_alphabetical(renderer& renderer);

  void cache_numerical(renderer& renderer);

  void cache_string(renderer& renderer, entt::id_type id, std::string_view str);

  void add_glyph(renderer& renderer, unicode glyph);

  [[nodiscard]] auto has(unicode glyph) const noexcept -> bool;

  [[nodiscard]] auto at(unicode glyph) const -> const texture&;

  [[nodiscard]] auto metrics(unicode glyph) -> glyph_metrics&;

  [[nodiscard]] auto metrics(unicode glyph) const -> const glyph_metrics&;

  [[nodiscard]] auto get() noexcept -> font& { return m_font; }

  [[nodiscard]] auto get() const noexcept -> const font& { return m_font; }

 private:
  font m_font;

  std::unordered_map<unicode, texture> m_glyphs;
  std::unordered_map<unicode, glyph_metrics> m_metrics;
  std::unordered_map<entt::id_type, texture> m_strings;

  [[nodiscard]] auto create_glyph_texture(renderer& renderer, unicode glyph)
      -> texture
  {
    const surface surf{TTF_RenderGlyph_Blended(
        m_font.get(), glyph, static_cast<SDL_Color>(renderer.get_color()))};
    return texture{renderer, surf};
  }
};

inline font_cache::font_cache(renderer& renderer, font&& font)
    : m_font{std::move(font)}
{
  // Caches all printable ASCII characters
  for (unicode ch = 20; ch < 128; ++ch) {
    add_glyph(renderer, ch);
  }
}

inline auto font_cache::unique(renderer& renderer, font&& font)
    -> std::unique_ptr<font_cache>
{
  return std::make_unique<font_cache>(renderer, std::move(font));
}

inline auto font_cache::render(renderer& renderer,
                               unicode glyph,
                               const point_i& position) -> int
{
  const auto& glyphMetrics = metrics(glyph);

  const auto x = position.x() + glyphMetrics.minX;
  const auto y = position.y();

  //  const auto y = (position.y() + glyphMetrics.maxY) -
  //      ((m_font.ascent() + glyphMetrics.maxY));

  renderer.render(at(glyph), point_i{x, y});

  return position.x() + glyphMetrics.advance;
}

inline void font_cache::render(renderer& renderer,
                               std::string_view str,
                               point_i position)
{
  const auto originalX = position.x();

  for (const auto glyph : str) {
    if (glyph == '\n') {
      position.set_x(originalX);
      position.set_y(position.y() + m_font.line_skip());
    } else {
      const auto x = render(renderer, glyph, position);
      position.set_x(x);
    }
  }
}

inline void font_cache::render_cached(renderer& renderer,
                                      entt::id_type id,
                                      const point_i& position)
{
  if (m_strings.count(id)) {
    renderer.render(m_strings.at(id), position);
  }
}

inline void font_cache::cache_alphabetical(renderer& renderer)
{
  add_glyph(renderer, 'A');
  add_glyph(renderer, 'B');
  add_glyph(renderer, 'C');
  add_glyph(renderer, 'D');
  add_glyph(renderer, 'E');
  add_glyph(renderer, 'F');
  add_glyph(renderer, 'G');
  add_glyph(renderer, 'H');
  add_glyph(renderer, 'I');
  add_glyph(renderer, 'J');
  add_glyph(renderer, 'K');
  add_glyph(renderer, 'L');
  add_glyph(renderer, 'M');
  add_glyph(renderer, 'N');
  add_glyph(renderer, 'O');
  add_glyph(renderer, 'P');
  add_glyph(renderer, 'Q');
  add_glyph(renderer, 'R');
  add_glyph(renderer, 'S');
  add_glyph(renderer, 'T');
  add_glyph(renderer, 'U');
  add_glyph(renderer, 'V');
  add_glyph(renderer, 'W');
  add_glyph(renderer, 'X');
  add_glyph(renderer, 'Y');
  add_glyph(renderer, 'Z');

  add_glyph(renderer, 'a');
  add_glyph(renderer, 'b');
  add_glyph(renderer, 'c');
  add_glyph(renderer, 'd');
  add_glyph(renderer, 'e');
  add_glyph(renderer, 'f');
  add_glyph(renderer, 'g');
  add_glyph(renderer, 'h');
  add_glyph(renderer, 'i');
  add_glyph(renderer, 'j');
  add_glyph(renderer, 'k');
  add_glyph(renderer, 'l');
  add_glyph(renderer, 'm');
  add_glyph(renderer, 'n');
  add_glyph(renderer, 'o');
  add_glyph(renderer, 'p');
  add_glyph(renderer, 'q');
  add_glyph(renderer, 'r');
  add_glyph(renderer, 's');
  add_glyph(renderer, 't');
  add_glyph(renderer, 'u');
  add_glyph(renderer, 'v');
  add_glyph(renderer, 'w');
  add_glyph(renderer, 'x');
  add_glyph(renderer, 'y');
  add_glyph(renderer, 'z');
}

inline void font_cache::cache_numerical(renderer& renderer)
{
  add_glyph(renderer, '0');
  add_glyph(renderer, '1');
  add_glyph(renderer, '2');
  add_glyph(renderer, '3');
  add_glyph(renderer, '4');
  add_glyph(renderer, '5');
  add_glyph(renderer, '6');
  add_glyph(renderer, '7');
  add_glyph(renderer, '8');
  add_glyph(renderer, '9');
}

inline void font_cache::cache_string(renderer& renderer,
                                     entt::id_type id,
                                     std::string_view str)
{
  if (!m_strings.count(id)) {
    auto unique = renderer.text_blended(str.data(), m_font);
    m_strings.emplace(id, std::move(*unique));  // TODO investigate if valid
  }
}

inline void font_cache::add_glyph(renderer& renderer, unicode glyph)
{
  if (!has(glyph) && m_font.is_glyph_provided(glyph)) {
    m_glyphs.emplace(glyph, create_glyph_texture(renderer, glyph));
    m_metrics.emplace(glyph, m_font.glyph_metrics(glyph).value());
  }
}

inline auto font_cache::has(unicode glyph) const noexcept -> bool
{
  constexpr entt::hashed_string id{"asdasd"};
  u32 u = id;

  return m_glyphs.count(glyph);
}

inline auto font_cache::at(unicode glyph) const -> const texture&
{
  return m_glyphs.at(glyph);
}

inline auto font_cache::metrics(unicode glyph) -> glyph_metrics&
{
  return m_metrics.at(glyph);
}

inline auto font_cache::metrics(unicode glyph) const -> const glyph_metrics&
{
  return m_metrics.at(glyph);
}

}  // namespace centurion::experimental

#ifdef CENTURION_HEADER_ONLY
// TODO include source file
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_EXPERIMENTAL_FONT_HEADER