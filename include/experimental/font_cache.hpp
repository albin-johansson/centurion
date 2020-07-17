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

class unicode_string final {
 public:
  using value_type = std::vector<unicode>::value_type;

  using pointer = std::vector<unicode>::pointer;
  using const_pointer = std::vector<unicode>::const_pointer;

  using reference = std::vector<unicode>::reference;
  using const_reference = std::vector<unicode>::const_reference;

  using iterator = std::vector<unicode>::iterator;
  using const_iterator = std::vector<unicode>::const_iterator;

  using reverse_iterator = std::vector<unicode>::reverse_iterator;
  using const_reverse_iterator = std::vector<unicode>::const_reverse_iterator;

  using size_type = std::vector<unicode>::size_type;
  using difference_type = std::vector<unicode>::difference_type;

  unicode_string() = default;

  void reserve(size_type n) { m_data.reserve(n); }

  void append(unicode ch) { m_data.emplace_back(ch); }

  template <typename First, typename... Args>
  void append(First first, Args... codes)
  {
    static_assert(std::is_same_v<unicode, First>);
    append(first);
    append(codes...);
  }

  void operator+=(unicode ch) { append(ch); }

  [[nodiscard]] auto size() const noexcept -> size_type
  {
    return m_data.size();
  }
  [[nodiscard]] auto capacity() const noexcept -> size_type
  {
    return m_data.capacity();
  }

  auto begin() noexcept -> iterator { return m_data.begin(); }
  auto begin() const noexcept -> const_iterator { return m_data.begin(); }

  auto cbegin() noexcept -> const_iterator { return m_data.cbegin(); }
  auto cbegin() const noexcept -> const_iterator { return m_data.cbegin(); }

  auto rbegin() noexcept -> reverse_iterator { return m_data.rbegin(); }
  auto rbegin() const noexcept -> const_reverse_iterator
  {
    return m_data.rbegin();
  }

  auto end() noexcept -> iterator { return m_data.end(); }
  auto end() const noexcept -> const_iterator { return m_data.end(); }

  auto rend() noexcept -> reverse_iterator { return m_data.rend(); }
  auto rend() const noexcept -> const_reverse_iterator { return m_data.rend(); }

  auto crbegin() noexcept -> const_reverse_iterator { return m_data.crbegin(); }
  auto crbegin() const noexcept -> const_reverse_iterator
  {
    return m_data.crbegin();
  }

  auto crend() noexcept -> const_reverse_iterator { return m_data.crend(); }
  auto crend() const noexcept -> const_reverse_iterator
  {
    return m_data.crend();
  }

  [[nodiscard]] auto at(size_type index) -> reference
  {
    return m_data.at(index);
  }
  [[nodiscard]] auto at(size_type index) const -> const_reference
  {
    return m_data.at(index);
  }

  [[nodiscard]] auto operator[](size_type index) -> reference
  {
    return m_data[index];
  }
  [[nodiscard]] auto operator[](size_type index) const -> const_reference
  {
    return m_data[index];
  }

 private:
  std::vector<unicode> m_data;
};

[[nodiscard]] inline auto operator==(const unicode_string& lhs,
                                     const unicode_string& rhs)
{
  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (unicode_string::size_type index = 0; index < lhs.size(); ++index) {
    const auto a = lhs.at(index);
    const auto b = rhs.at(index);
    if (a != b) {
      return false;
    }
  }

  return true;
}

[[nodiscard]] inline auto operator!=(const unicode_string& lhs,
                                     const unicode_string& rhs)
{
  return !(lhs == rhs);
}

class font_cache final {
 public:
  /**
   * @brief Creates an empty font cache instance.
   *
   * @note You have to explicitly state what glyphs that you want to be cached.
   *
   * @param font the font that will be used.
   *
   * @since 5.0.0
   */
  explicit font_cache(font&& font) noexcept : m_font{std::move(font)} {}

  /**
   * @brief Creates an empty font cache, and creates the associated font
   * in-place.
   *
   * @tparam Args the types of the arguments forwarded to the font constructor.
   *
   * @param args the arguments that will be forwarded to the font constructor.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  explicit font_cache(Args&&... args) : m_font{std::forward<Args>(args)...}
  {}

  [[nodiscard]] static auto unique(font&& font) -> std::unique_ptr<font_cache>
  {
    return std::make_unique<font_cache>(std::move(font));
  }

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
  auto render(renderer& renderer, unicode glyph, const point_i& position) -> int
  {
    const auto& glyphMetrics = metrics(glyph);

    const auto x = position.x() + glyphMetrics.minX;
    const auto y = position.y();

    //  const auto y = (position.y() + glyphMetrics.maxY) -
    //      ((m_font.ascent() + glyphMetrics.maxY));

    renderer.render(at(glyph), point_i{x, y});

    return position.x() + glyphMetrics.advance;
  }

  void render(renderer& renderer, std::string_view str, point_i position)
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

  void render(renderer& renderer, unicode_string str, point_i position)
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

  void render_cached(renderer& renderer,
                     entt::id_type id,
                     const point_i& position)
  {
    if (const auto iterator = m_strings.find(id); iterator != m_strings.end()) {
      renderer.render(m_strings.at(id), position);
    }
  }

  void cache_string(renderer& renderer, entt::id_type id, std::string_view str)
  {
    if (!m_strings.count(id)) {
      auto unique = renderer.text_blended(str.data(), m_font);
      m_strings.emplace(id, std::move(*unique));  // TODO investigate if valid
    }
  }

  void cache_utf8(renderer& renderer, entt::id_type id, std::string_view str)
  {
    auto* r = renderer.get();

    auto* surface = TTF_RenderUTF8_Blended(
        m_font.get(), str.data(), static_cast<SDL_Color>(renderer.get_color()));


  }

  void add_glyph(renderer& renderer, unicode glyph)
  {
    if (!has(glyph)) {
      if (m_font.is_glyph_provided(glyph)) {
        m_glyphs.emplace(glyph, create_glyph_texture(renderer, glyph));
        m_metrics.emplace(glyph, m_font.glyph_metrics(glyph).value());
      } else {
        log::warn(
            "%s doesn't feature the glyph: %X", m_font.family_name(), glyph);
      }
    }
  }

  /**
   * @brief Caches the glyphs in the specified range.
   *
   * @details The range is interpreted as [min, max), meaning the the `min`
   * value is included, and `max` is excluded.
   *
   * @param renderer the renderer that will be used to create the glyph
   * textures.
   * @param begin the first glyph that will be included.
   * @param end the "end" glyph in the range, will not be included.
   *
   * @since 5.0.0
   */
  void cache_range(renderer& renderer, unicode begin, unicode end)
  {
    for (unicode ch = begin; ch < end; ++ch) {
      add_glyph(renderer, ch);
    }
  }

  /**
   * @brief Attempts to cache all printable basic latin characters.
   *
   * @details The basic latin set provides the most common characters, such as
   * upper- and lower-case latin letters, numbers and symbols. This method
   * might throw if something goes wrong when creating the textures.
   *
   * @param renderer the renderer that will be used to create the glyph
   * textures.
   *
   * @since 5.0.0
   */
  void cache_basic_latin(renderer& renderer)
  {
    // https://unicode-table.com/en/blocks/basic-latin/

    //    Range: 0000-007F
    // Controls: 0000-0020 and 007F
    cache_range(renderer, 0x20, 0x7F);
  }

  void cache_latin1_supplement(renderer& renderer)
  {
    // https://unicode-table.com/en/blocks/latin-1-supplement/

    //    Range: 0080-00FF
    // Controls: 0080-009F

    cache_range(renderer, 0xA0, 0x100);
  }

  void cache_latin1(renderer& renderer)
  {
    cache_basic_latin(renderer);
    cache_latin1_supplement(renderer);
  }

  [[nodiscard]] auto has(unicode glyph) const noexcept -> bool
  {
    return m_glyphs.count(glyph);
  }

  [[nodiscard]] auto at(unicode glyph) const -> const texture&
  {
    return m_glyphs.at(glyph);
  }

  [[nodiscard]] auto metrics(unicode glyph) -> glyph_metrics&
  {
    return m_metrics.at(glyph);
  }

  [[nodiscard]] auto metrics(unicode glyph) const -> const glyph_metrics&
  {
    return m_metrics.at(glyph);
  }

  [[nodiscard]] auto get() noexcept -> font& { return m_font; }

  [[nodiscard]] auto get() const noexcept -> const font& { return m_font; }

 private:
  font m_font;

  struct glyph_info {
    texture image;
    glyph_metrics metrics;
  };

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

}  // namespace centurion::experimental

#ifdef CENTURION_HEADER_ONLY
// TODO include source file
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_EXPERIMENTAL_FONT_HEADER