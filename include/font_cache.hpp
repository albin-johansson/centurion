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
 * @file font_cache.hpp
 *
 * @brief Provides the `font_cache` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_FONT_CACHE_HEADER
#define CENTURION_FONT_CACHE_HEADER

#include <SDL_ttf.h>

#include <algorithm>
#include <hashed_string.hpp>
#include <memory>
#include <unordered_map>
#include <utility>

#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "centurion_types.hpp"
#include "font.hpp"
#include "texture.hpp"
#include "unicode_string.hpp"

namespace centurion::experimental {

/**
 * @class font_cache
 *
 * @ingroup graphics
 *
 * @brief Provides an API that enables efficient font rendering.
 *
 * @details This class provides two different optimizations.
 *
 * First of, this class will, if told, cache glyph textures that can be used
 * to render strings by simply looking up the individual glyphs and rendering
 * existing textures. It should be noted that the glyph-based rendering will
 * not feature accurate kerning. However, this might not be noticeable and/or
 * worth the performance boost. This type of rendering is *very* efficient for
 * rendering pieces of text that frequently changes, since other approaches
 * would require dynamic allocation and de-allocation for every new rendered
 * string.
 *
 * Secondly, it's also possible to tell instances of this class to cache full
 * strings and associate them with a user-provided identifier. Using this
 * approach, the strings will be rendered using accurate kerning. The problem
 * is, as you probably know, is that it's often hard to know what exact
 * strings you will render at compile-time. Use this option if you know that
 * you're going to render some specific string a lot.
 *
 * @todo Look into adding option for accurate kerning.
 *
 * @since 5.0.0
 *
 * @headerfile font_cache.hpp
 */
class font_cache final {
 public:
  /**
   * @struct glyph_data
   *
   * @brief Simple aggregate that contains a texture and metrics for a glyph.
   *
   * @since 5.0.0
   *
   * @headerfile font_cache.hpp
   */
  struct glyph_data {
    texture cached;         ///< The cached texture.
    glyph_metrics metrics;  ///< The metrics of the glyph.
  };

  /**
   * @brief Creates an empty font cache instance.
   *
   * @note You have to explicitly state what glyphs that you want to be cached.
   *
   * @param font the font that will be used.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit font_cache(font&& font) noexcept;

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

  /**
   * @copydoc font_cache(font&&)
   */
  CENTURION_QUERY
  static auto unique(font&& font) -> std::unique_ptr<font_cache>;

  /**
   * @brief Creates and returns a unique pointer to a font cache instance.
   *
   * @details Creates an empty font cache, and creates the associated font
   * in-place.
   *
   * @tparam Args the types of the arguments forwarded to the font constructor.
   *
   * @param args the arguments that will be forwarded to the font constructor.
   *
   * @return a unique pointer to a font cache.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  [[nodiscard]] static auto unique(Args&&... args)
      -> std::unique_ptr<font_cache>
  {
    return std::make_unique<font_cache>(std::forward<Args>(args)...);
  }

  /**
   * @copydoc font_cache(font&&)
   */
  CENTURION_QUERY
  static auto shared(font&& font) -> std::shared_ptr<font_cache>;

  /**
   * @brief Creates and returns a shared pointer to a font cache instance.
   *
   * @details Creates an empty font cache, and creates the associated font
   * in-place.
   *
   * @tparam Args the types of the arguments forwarded to the font constructor.
   *
   * @param args the arguments that will be forwarded to the font constructor.
   *
   * @return a shared pointer to a font cache.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  [[nodiscard]] static auto shared(Args&&... args)
      -> std::shared_ptr<font_cache>
  {
    return std::make_shared<font_cache>(std::forward<Args>(args)...);
  }

  /**
   * @name String caching
   * Methods related to caching strings as textures.
   */
  ///@{

  /**
   * @brief Caches the supplied Unicode string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_blended_unicode`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Unicode string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_unicode(renderer& renderer,
                             entt::id_type id,
                             const unicode_string& str);

  /**
   * @brief Caches the supplied Unicode string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_blended_wrapped_unicode`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Unicode string that will be cached.
   * @param wrap the width in pixels after which the text will be wrapped.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_wrapped_unicode(renderer& renderer,
                                     entt::id_type id,
                                     const unicode_string& str,
                                     u32 wrap);

  /**
   * @brief Caches the supplied Unicode string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_shaded_unicode`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Unicode string that will be cached.
   * @param background the background color used for the box.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_shaded_unicode(renderer& renderer,
                            entt::id_type id,
                            const unicode_string& str,
                            const color& background);

  /**
   * @brief Caches the supplied Unicode string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_solid_unicode`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Unicode string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_solid_unicode(renderer& renderer,
                           entt::id_type id,
                           const unicode_string& str);

  /**
   * @brief Caches the supplied Latin-1 string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_blended_latin1`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Latin-1 string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_latin1(renderer& renderer,
                            entt::id_type id,
                            nn_czstring str);

  /**
   * @brief Caches the supplied Latin-1 string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_blended_wrapped_latin1`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Latin-1 string that will be cached.
   * @param wrap the width in pixels after which the text will be wrapped.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_wrapped_latin1(renderer& renderer,
                                    entt::id_type id,
                                    nn_czstring str,
                                    u32 wrap);

  /**
   * @brief Caches the supplied Latin-1 string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_shaded_latin1`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Latin-1 string that will be cached.
   * @param background the background color used for the box.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_shaded_latin1(renderer& renderer,
                           entt::id_type id,
                           nn_czstring str,
                           const color& background);

  /**
   * @brief Caches the supplied Latin-1 string as a texture.
   *
   * @details The texture is created using `renderer_base::render_solid`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Latin-1 string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_solid_latin1(renderer& renderer,
                          entt::id_type id,
                          nn_czstring str);

  /**
   * @brief Caches the supplied UTF-8 string as a texture.
   *
   * @details The texture is created using `renderer_base::render_blended_utf8`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the UTF-8 string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_utf8(renderer& renderer,
                          entt::id_type id,
                          nn_czstring str);

  /**
   * @brief Caches the supplied UTF-8 string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_blended_wrapped_utf8`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the UTF-8 string that will be cached.
   * @param wrap the width in pixels after which the text will be wrapped.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_wrapped_utf8(renderer& renderer,
                                  entt::id_type id,
                                  nn_czstring str,
                                  u32 wrap);

  /**
   * @brief Caches the supplied UTF-8 string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_shaded_utf8`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the UTF-8 string that will be cached.
   * @param background the background color used for the box.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_shaded_utf8(renderer& renderer,
                         entt::id_type id,
                         nn_czstring str,
                         const color& background);

  /**
   * @brief Caches the supplied UTF-8 string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_solid_utf8`.
   *
   * @note This method respects the kerning of the font.
   * @note This method has no effect if the supplied key is already taken.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the UTF-8 string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_solid_utf8(renderer& renderer, entt::id_type id, nn_czstring str);

  /**
   * @brief Indicates whether or not there is a cached texture associated
   * with the specified key.
   *
   * @param id the key that will be checked.
   *
   * @return `true` if there is a cached texture associated with the key;
   * `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto has_cached(entt::id_type id) const noexcept -> bool
  {
    return m_strings.count(id);
  }

  /**
   * @brief Returns a pointer to the texture associated with the specified key.
   *
   * @note The returned pointer is not suitable for storing for longer than
   * absolutely necessary, as it might get invalidated by modifications of
   * the font cache.
   *
   * @param id the key of the desired texture.
   *
   * @return a pointer to the texture associated with the specified key;
   * `nullptr` if no texture is found.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto try_get_cached(entt::id_type id) const noexcept -> const texture*;

  /**
   * @brief Returns the cached texture associated with the specified ID.
   *
   * @pre `id` **must** be associated with a cached string texture.
   *
   * @param id the key of the cached texture to obtain.
   *
   * @return the cached texture associated with the key.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get_cached(entt::id_type id) const -> const texture&
  {
    return m_strings.at(id);
  }

  ///@}  // end of string caching

  /**
   * @name Glyph caching
   * Methods related to cached Unicode glyph textures.
   */
  ///@{

  CENTURION_API
  void add_glyph(renderer& renderer, unicode glyph);

  /**
   * @brief Caches the glyphs in the specified range.
   *
   * @details The range is interpreted as [min, max), i.e. the the `min`
   * value is included, and `max` is excluded.
   *
   * @remark For an overview of the various Unicode blocks, see <a
   * href="https://unicode-table.com/en/blocks/">this</a>.
   *
   * @param renderer the renderer that will be used to create the glyph
   * textures.
   * @param begin the first glyph that will be included.
   * @param end the "end" glyph in the range, will not be included.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_range(renderer& renderer, unicode begin, unicode end);

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
  CENTURION_API
  void cache_basic_latin(renderer& renderer);

  /**
   * @brief Attempts to cache all printable Latin-1 supplement characters.
   *
   * @param renderer the renderer that will be used to create the glyph
   * textures.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_latin1_supplement(renderer& renderer);

  /**
   * @brief Attempts to cache all printable Latin-1 characters.
   *
   * @note This method is effectively equivalent to calling both
   * `cache_basic_latin` and `cache_latin1_supplement`.
   *
   * @param renderer the renderer that will be used to create the glyph
   * textures.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_latin1(renderer& renderer);

  /**
   * @brief Indicates whether or not the specified glyph has been cached.
   *
   * @param glyph the glyph to check.
   *
   * @return `true` if the specified glyph has been cached; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto has(unicode glyph) const noexcept -> bool
  {
    return m_glyphs.count(glyph);
  }

  /**
   * @brief Returns the data associated with the specified glyph.
   *
   * @pre `glyph` **must** have been previously cached.
   *
   * @details The recommended way to use this method is with structured
   * bindings, as in the following example.
   * @code{.cpp}
   *   ctn::font_cache cache = ...;
   *   const auto& [cachedTexture, glyphMetrics] = cache.at('A'_uni);
   * @endcode
   *
   * @param glyph the desired glyph to lookup the data for.
   *
   * @return the cached texture and metrics associated with the glyph.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto at(unicode glyph) const -> const glyph_data&
  {
    return m_glyphs.at(glyph);
  }

  /**
   * @brief Returns the data associated with the specified glyph.
   *
   * @note This function is equivalent to calling `at`.
   *
   * @pre `glyph` **must** have been previously cached.
   *
   * @details The recommended way to use this method is with structured
   * bindings, as in the following example.
   * @code{.cpp}
   *   ctn::font_cache cache = ...;
   *   const auto& [cachedTexture, glyphMetrics] = cache['A'];
   * @endcode
   *
   * @param glyph the desired glyph to lookup the data for.
   *
   * @return the cached texture and metrics associated with the glyph.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto operator[](unicode glyph) const -> const glyph_data&
  {
    return at(glyph);
  }

  ///@}  // end of glyph caching

  /**
   * @brief Returns the font used by the cache.
   *
   * @return a reference to the internal font.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto get() noexcept -> font& { return m_font; }

  /**
   * @copydoc get
   */
  [[nodiscard]] auto get() const noexcept -> const font& { return m_font; }

 private:
  font m_font;
  std::unordered_map<unicode, glyph_data> m_glyphs;
  std::unordered_map<entt::id_type, texture> m_strings;

  /**
   * @brief Adds a string texture to the string cache.
   *
   * @details This method has no effect if the supplied key is already taken.
   *
   * @param id the key that will be used for the texture.
   * @param texture the texture that will be cached.
   *
   * @since 5.0.0
   */
  void cache_string_texture(entt::id_type id, texture&& texture);

  /**
   * @brief Creates and returns a texture for the specified glyph.
   *
   * @details The glyph is rendered with `TTF_RenderGlyph_Blended`.
   *
   * @param renderer the renderer that will be used.
   * @param glyph the Unicode glyph that will be rendered.
   *
   * @return a texture that represents the specified glyph.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto create_glyph_texture(renderer& renderer, unicode glyph)
      -> texture;
};

}  // namespace centurion::experimental

#ifdef CENTURION_HEADER_ONLY
#include "font_cache.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_FONT_CACHE_HEADER