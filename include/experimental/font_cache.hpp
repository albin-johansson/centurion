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
#include "graphics.hpp"
#include "log.hpp"

namespace centurion::experimental {

using unicode = u16;

class font_cache final {
 public:
  template <typename T>
  font_cache(const basic_renderer<T>& renderer, font&& font);

  template <typename T>
  [[nodiscard]] static auto unique(const basic_renderer<T>& renderer,
                                   font&& font) -> std::unique_ptr<font_cache>;

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
  template <typename T>
  auto render(basic_renderer<T>& renderer,
              unicode glyph,
              const point_i& position) -> int;

  template <typename T>
  void render(basic_renderer<T>& renderer,
              std::string_view str,
              point_i position);

  template <typename T>
  void render_cached(basic_renderer<T>& renderer,
                     entt::id_type id,
                     const point_i& position);

  template <typename T>
  void cache_alphabetical(basic_renderer<T>& renderer);

  template <typename T>
  void cache_numerical(basic_renderer<T>& renderer);

  template <typename T>
  void cache_string(basic_renderer<T>& renderer,
                    entt::id_type id,
                    std::string_view str);

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

  template <typename T>
  [[nodiscard]] auto create_glyph_texture(const basic_renderer<T>& renderer,
                                          unicode glyph) -> texture
  {
    const surface surf{TTF_RenderGlyph_Blended(
        m_font.get(), glyph, static_cast<SDL_Color>(renderer.get_color()))};
    return texture{renderer, surf};
  }

  template <typename T>
  void add_glyph(const basic_renderer<T>& renderer, unicode glyph)
  {
    if (!has(glyph)) {
      if (m_font.is_glyph_provided(glyph)) {
        m_glyphs.emplace(glyph, create_glyph_texture(renderer, glyph));
        m_metrics.emplace(glyph, m_font.glyph_metrics(glyph).value());
      }
    }
  }
};

template <typename T>
font_cache::font_cache(const basic_renderer<T>& renderer, font&& font)
    : m_font{std::move(font)}
{
  // Caches all printable ASCII characters
  for (unicode ch = 20; ch < 128; ++ch) {
    add_glyph(renderer, ch);
  }
}

template <typename T>
auto font_cache::unique(const basic_renderer<T>& renderer, font&& font)
    -> std::unique_ptr<font_cache>
{
  return std::make_unique<font_cache>(renderer, std::move(font));
}

template <typename T>
auto font_cache::render(basic_renderer<T>& renderer,
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

template <typename T>
void font_cache::render(basic_renderer<T>& renderer,
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

template <typename T>
void font_cache::render_cached(basic_renderer<T>& renderer,
                               entt::id_type id,
                               const point_i& position)
{
  if (m_strings.count(id)) {
    renderer.render(m_strings.at(id), position);
  }
}

template <typename T>
void font_cache::cache_alphabetical(basic_renderer<T>& renderer)
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

template <typename T>
void font_cache::cache_numerical(basic_renderer<T>& renderer)
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

template <typename T>
void font_cache::cache_string(basic_renderer<T>& renderer,
                              entt::id_type id,
                              std::string_view str)
{
  if (!m_strings.count(id)) {
    auto unique = renderer.text_blended(str.data(), m_font);
    m_strings.emplace(id, std::move(*unique));  // TODO investigate if valid
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