#ifndef CENTURION_FONT_CACHE_HEADER
#define CENTURION_FONT_CACHE_HEADER

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <cassert>        // assert
#include <string>         // string
#include <unordered_map>  // unordered_map
#include <utility>        // move, forward

#include "../core/not_null.hpp"
#include "../core/str.hpp"
#include "font.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode_string.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \class font_cache
 *
 * \brief Provides an API that enables efficient font rendering.
 *
 * \details This class provides two different optimizations.
 *
 * Firstly, this class can be used to cache glyph textures that can then be used to render
 * strings, by simply looking up the individual glyphs and rendering the existing
 * textures. Note, this will not result in accurate kerning. However, this might not be
 * noticeable and/or worth the performance boost. This approach is *very* efficient for
 * rendering pieces of text that frequently changes, since other approaches would require
 * dynamic allocation and de-allocation for every new rendered string.
 *
 * Secondly, it's possible to cache complete strings and associate them with a
 * user-provided identifier. In contrast with the first approach, this will result in
 * accurate kerning. The only problem is that it's hard to know the exact strings you will
 * render at compile-time. Use this option if you know that you're going to render some
 * specific string a lot.
 *
 * \since 5.0.0
 */
class font_cache final
{
 public:
  using id_type = std::size_t;

  /**
   * \struct glyph_data
   *
   * \brief Simple aggregate that contains a texture and metrics for a glyph.
   *
   * \since 5.0.0
   */
  struct glyph_data final
  {
    texture cached;         ///< The cached texture.
    glyph_metrics metrics;  ///< The metrics of the glyph.
  };

  /// \name Construction
  /// \{

  /**
   * \brief Creates an empty font cache instance.
   *
   * \note You have to explicitly state what glyphs that you want to be cached.
   *
   * \param font the font that will be used.
   *
   * \since 5.0.0
   */
  explicit font_cache(font&& font) noexcept : m_font{std::move(font)}
  {}

  /**
   * \brief Creates an empty font cache, and creates the associated font in-place.
   *
   * \note This constructor throws whatever exceptions that the `font` constructor might
   * throw.
   *
   * \tparam Args the types of the arguments forwarded to the font constructor.
   *
   * \param args the arguments that will be forwarded to the font constructor.
   *
   * \since 5.0.0
   */
  template <typename... Args>
  explicit font_cache(Args&&... args) : m_font{std::forward<Args>(args)...}
  {}

  /// \} End of construction

  /// \name String texture caching
  /// \{

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   *
   * \see `basic_renderer::render_blended_utf8()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_blended_utf8(const id_type id, const not_null<str> string, Renderer& renderer)
  {
    assert(string);
    store(id, renderer.render_blended_utf8(string, get_font()));
  }

  /**
   * \see store_blended_utf8()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_blended_utf8(const id_type id, const std::string& string, Renderer& renderer)
  {
    store_blended_utf8(id, string.c_str(), renderer);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \see `basic_renderer::render_blended_wrapped_utf8()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_blended_wrapped_utf8(const id_type id,
                                  const not_null<str> string,
                                  Renderer& renderer,
                                  const u32 wrap)
  {
    assert(string);
    store(id, renderer.render_blended_wrapped_utf8(string, get_font(), wrap));
  }

  /**
   * \see store_blended_wrapped_utf8()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_blended_wrapped_utf8(const id_type id,
                                  const std::string& string,
                                  Renderer& renderer,
                                  const u32 wrap)
  {
    store_blended_wrapped_utf8(id, string.c_str(), renderer, wrap);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   * \param background the color used for the background box.
   *
   * \see `basic_renderer::render_shaded_utf8()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_shaded_utf8(const id_type id,
                         const not_null<str> string,
                         Renderer& renderer,
                         const color& background)
  {
    assert(string);
    store(id, renderer.render_shaded_utf8(string, get_font(), background));
  }

  /**
   * \see store_shaded_utf8()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_shaded_utf8(const id_type id,
                         const std::string& string,
                         Renderer& renderer,
                         const color& background)
  {
    store_shaded_utf8(id, string.c_str(), renderer, background);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   *
   * \see `basic_renderer::render_solid_utf8()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_solid_utf8(const id_type id, const not_null<str> string, Renderer& renderer)
  {
    assert(string);
    store(id, renderer.render_solid_utf8(string, get_font()));
  }

  /**
   * \see store_solid_utf8()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_solid_utf8(const id_type id, const std::string& string, Renderer& renderer)
  {
    store_solid_utf8(id, string.c_str(), renderer);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   *
   * \see `basic_renderer::render_blended_latin1()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_blended_latin1(const id_type id, const not_null<str> string, Renderer& renderer)
  {
    assert(string);
    store(id, renderer.render_blended_latin1(string, get_font()));
  }

  /**
   * \see store_blended_latin1()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_blended_latin1(const id_type id, const std::string& string, Renderer& renderer)
  {
    store_blended_latin1(id, string.c_str(), renderer);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \see `basic_renderer::render_blended_wrapped_latin1()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_blended_wrapped_latin1(const id_type id,
                                    const not_null<str> string,
                                    Renderer& renderer,
                                    const u32 wrap)
  {
    assert(string);
    store(id, renderer.render_blended_wrapped_latin1(string, get_font(), wrap));
  }

  /**
   * \see store_blended_wrapped_latin1()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_blended_wrapped_latin1(const id_type id,
                                    const std::string& string,
                                    Renderer& renderer,
                                    const u32 wrap)
  {
    store_blended_wrapped_latin1(id, string.c_str(), renderer, wrap);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   * \param background the color used for the background box.
   *
   * \see `basic_renderer::render_shaded_latin1()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_shaded_latin1(const id_type id,
                           const not_null<str> string,
                           Renderer& renderer,
                           const color& background)
  {
    assert(string);
    store(id, renderer.render_shaded_latin1(string, get_font(), background));
  }

  /**
   * \see store_shaded_latin1()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_shaded_latin1(const id_type id,
                           const std::string& string,
                           Renderer& renderer,
                           const color& background)
  {
    store_shaded_latin1(id, string.c_str(), renderer, background);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   *
   * \see `basic_renderer::render_solid_latin1()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_solid_latin1(const id_type id, const not_null<str> string, Renderer& renderer)
  {
    assert(string);
    store(id, renderer.render_solid_latin1(string, get_font()));
  }

  /**
   * \see store_solid_latin1()
   * \since 5.3.0
   */
  template <typename Renderer>
  void store_solid_latin1(const id_type id, const std::string& string, Renderer& renderer)
  {
    store_solid_latin1(id, string.c_str(), renderer);
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   *
   * \see `basic_renderer::render_blended_unicode()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_blended_unicode(const id_type id,
                             const unicode_string& string,
                             Renderer& renderer)
  {
    store(id, renderer.render_blended_unicode(string, get_font()));
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \see `basic_renderer::render_blended_wrapped_unicode()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_blended_wrapped_unicode(const id_type id,
                                     const unicode_string& string,
                                     Renderer& renderer,
                                     const u32 wrap)
  {
    store(id, renderer.render_blended_wrapped_unicode(string, get_font(), wrap));
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   * \param background the color used for the background box.
   *
   * \see `basic_renderer::render_shaded_unicode()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_shaded_unicode(const id_type id,
                            const unicode_string& string,
                            Renderer& renderer,
                            const color& background)
  {
    store(id, renderer.render_shaded_unicode(string, get_font(), background));
  }

  /**
   * \brief Caches the supplied string by rendering it to a texture.
   *
   * \details This function respects the kerning of the font. Any previous cached string
   * associated with the supplied ID will be overwritten.
   *
   * \tparam Renderer the type of the renderer that will be used.
   *
   * \param id the identifier that will be associated with the texture.
   * \param string the string that will be cached.
   * \param renderer the renderer that will be used to create the string texture.
   *
   * \see `basic_renderer::render_solid_unicode()`
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void store_solid_unicode(const id_type id, const unicode_string& string, Renderer& renderer)
  {
    store(id, renderer.render_solid_unicode(string, get_font()));
  }

  /**
   * \brief Indicates whether or not there is a cached string texture associated with the
   * specified key.
   *
   * \param id the key that will be checked.
   *
   * \return `true` if there is a cached texture associated with the key; `false`
   * otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto has_stored(const id_type id) const noexcept -> bool
  {
    return m_strings.find(id) != m_strings.end();
  }

  /**
   * \brief Returns the cached texture associated with the specified ID.
   *
   * \pre `id` **must** be associated with a cached string texture.
   *
   * \param id the key of the cached texture to obtain.
   *
   * \return the cached texture associated with the key.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_stored(const id_type id) const -> const texture&
  {
    return m_strings.at(id);
  }

  /**
   * \brief Returns a pointer to the texture associated with the specified key.
   *
   * \note The returned pointer is not suitable for storing for longer than absolutely
   * necessary, as it might get invalidated by modifications of the font cache.
   *
   * \param id the key of the desired texture.
   *
   * \return a pointer to the texture associated with the specified key; `nullptr` if no
   * texture is found.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto try_get_stored(const id_type id) const noexcept -> const texture*
  {
    const auto iterator = m_strings.find(id);
    if (iterator != m_strings.end()) {
      return &iterator->second;
    }
    else {
      return nullptr;
    }
  }

  /// \} End of string texture caching

  /// \name Glyph texture caching
  /// \{

  /**
   * \brief Adds a glyph to the font cache.
   *
   * \details This function has no effect if the supplied glyph isn't provided by the
   * associated font, or if the supplied glyph has already been cached.
   *
   * \tparam Renderer the type of the renderer.
   *
   * \param renderer the renderer that will be used to create the glyph texture.
   * \param glyph the glyph that will be cached.
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void add_glyph(Renderer& renderer, const unicode glyph)
  {
    if (has(glyph) || !m_font.is_glyph_provided(glyph)) {
      return;
    }

    glyph_data data{create_glyph_texture(renderer, glyph), m_font.get_metrics(glyph).value()};
    m_glyphs.try_emplace(glyph, std::move(data));
  }

  /**
   * \brief Caches the glyphs in the specified range.
   *
   * \details The range is interpreted as [min, max), i.e. the the `min` value is
   * included, and `max` is excluded.
   *
   * \remark For an overview of the various Unicode blocks, see <a
   * href="https://unicode-table.com/en/blocks/">this</a>.
   *
   * \tparam Renderer the type of the renderer.
   *
   * \param renderer the renderer that will be used to create the glyph textures.
   * \param begin the first glyph that will be included.
   * \param end the "end" glyph in the range, will not be included.
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void add_range(Renderer& renderer, const unicode begin, const unicode end)
  {
    for (auto ch = begin; ch < end; ++ch) {
      add_glyph(renderer, ch);
    }
  }

  /**
   * \brief Attempts to cache all printable basic latin characters.
   *
   * \details The basic latin set provides the most common characters, such as upper- and
   * lower-case latin letters, numbers and symbols. This function might throw if something
   * goes wrong when creating the textures.
   *
   * \tparam Renderer the type of the renderer.
   *
   * \param renderer the renderer that will be used to create the glyph textures.
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void add_basic_latin(Renderer& renderer)
  {
    // https://unicode-table.com/en/blocks/basic-latin/
    add_range(renderer, 0x20, 0x7F);
  }

  /**
   * \brief Attempts to cache all printable Latin-1 supplement characters.
   *
   * \tparam Renderer the type of the renderer.
   *
   * \param renderer the renderer that will be used to create the glyph textures.
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void add_latin1_supplement(Renderer& renderer)
  {
    // https://unicode-table.com/en/blocks/latin-1-supplement/
    add_range(renderer, 0xA0, 0x100);
  }

  /**
   * \brief Attempts to cache all printable Latin-1 characters.
   *
   * \note This function is effectively equivalent to calling both `add_basic_latin` and
   * `add_latin1_supplement`.
   *
   * \tparam Renderer the type of the renderer.
   *
   * \param renderer the renderer that will be used to create the glyph textures.
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  void add_latin1(Renderer& renderer)
  {
    add_basic_latin(renderer);
    add_latin1_supplement(renderer);
  }

  /**
   * \brief Indicates whether or not the specified glyph has been cached.
   *
   * \param glyph the glyph to check.
   *
   * \return `true` if the specified glyph has been cached; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto has(const unicode glyph) const noexcept -> bool
  {
    return m_glyphs.count(glyph);
  }

  /**
   * \brief Returns the data associated with the specified glyph.
   *
   * \pre `glyph` **must** have been previously cached.
   *
   * \param glyph the desired glyph to lookup the data for.
   *
   * \return the cached texture and metrics associated with the glyph.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto at(const unicode glyph) const -> const glyph_data&
  {
    return m_glyphs.at(glyph);
  }

  /**
   * \brief Returns the data associated with the specified glyph.
   *
   * \note This function is equivalent to calling `at`.
   *
   * \pre `glyph` **must** have been previously cached.
   *
   * \param glyph the desired glyph to lookup the data for.
   *
   * \return the cached texture and metrics associated with the glyph.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto operator[](unicode glyph) const -> const glyph_data&
  {
    return at(glyph);
  }

  /**
   * \brief Returns the data associated with the specified glyph, if it exists.
   *
   * \details This function is a non-throwing alternative to the `at()` and `operator[]`
   * functions.
   *
   * \note Do not store the returned pointer for longer than absolutely necessary, it may
   * get invalidated upon modification of the font cache.
   *
   * \param glyph the desired glyph to lookup the data for.
   *
   * \return a pointer to the associated glyph data; a null pointer if no matching data
   * was found.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto try_at(const unicode glyph) const -> const glyph_data*
  {
    if (const auto it = m_glyphs.find(glyph); it != m_glyphs.end()) {
      return &it->second;
    }
    else {
      return nullptr;
    }
  }

  /// \} End of glyph texture caching

  /**
   * \brief Returns the font used by the cache.
   *
   * \return a reference to the internal font.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_font() noexcept -> font&
  {
    return m_font;
  }

  /**
   * \copydoc get_font
   */
  [[nodiscard]] auto get_font() const noexcept -> const font&
  {
    return m_font;
  }

 private:
  font m_font;
  std::unordered_map<unicode, glyph_data> m_glyphs;
  std::unordered_map<id_type, texture> m_strings;

  /**
   * \brief Creates and returns a texture for the specified glyph.
   *
   * \details The glyph is rendered with `TTF_RenderGlyph_Blended`.
   *
   * \param renderer the renderer that will be used.
   * \param glyph the Unicode glyph that will be rendered.
   *
   * \return a texture that represents the specified glyph.
   *
   * \since 5.0.0
   */
  template <typename Renderer>
  [[nodiscard]] auto create_glyph_texture(Renderer& renderer, const unicode glyph) -> texture
  {
    const auto color = renderer.get_color().get();
    const surface src{TTF_RenderGlyph_Blended(m_font.get(), glyph, color)};
    return texture{renderer, src};
  }

  void store(const id_type id, texture&& texture)
  {
    if (const auto it = m_strings.find(id); it != m_strings.end()) {
      m_strings.erase(it);
    }
    m_strings.try_emplace(id, std::move(texture));
  }
};

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONT_CACHE_HEADER