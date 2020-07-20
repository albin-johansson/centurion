#ifndef CENTURION_FONT_CACHE_SOURCE
#define CENTURION_FONT_CACHE_SOURCE

#include "font_cache.hpp"

#include "renderer.hpp"

namespace centurion::experimental {

CENTURION_DEF
font_cache::font_cache(font&& font) noexcept : m_font{std::move(font)}
{}

CENTURION_DEF
auto font_cache::unique(font&& font) -> std::unique_ptr<font_cache>
{
  return std::make_unique<font_cache>(std::move(font));
}

CENTURION_DEF
auto font_cache::shared(font&& font) -> std::shared_ptr<font_cache>
{
  return std::make_shared<font_cache>(std::move(font));
}

CENTURION_DEF
auto font_cache::create_glyph_texture(renderer& renderer, unicode glyph)
    -> texture
{
  const surface surf{TTF_RenderGlyph_Blended(
      m_font.get(), glyph, static_cast<SDL_Color>(renderer.get_color()))};
  return texture{renderer, surf};
}

CENTURION_DEF
void font_cache::cache_string_texture(entt::id_type id, texture&& texture)
{
  const auto iterator = m_strings.find(id);
  if (iterator == m_strings.end()) {
    m_strings.emplace(id, std::move(texture));
  }
}

CENTURION_DEF
void font_cache::cache_blended_unicode(renderer& renderer,
                                       entt::id_type id,
                                       const unicode_string& str)
{
  cache_string_texture(id, renderer.render_blended_unicode(str, m_font));
}

CENTURION_DEF
void font_cache::cache_blended_wrapped_unicode(renderer& renderer,
                                               entt::id_type id,
                                               const unicode_string& str,
                                               u32 wrap)
{
  cache_string_texture(
      id, renderer.render_blended_wrapped_unicode(str, m_font, wrap));
}

CENTURION_DEF
void font_cache::cache_shaded_unicode(renderer& renderer,
                                      entt::id_type id,
                                      const unicode_string& str,
                                      const color& background)
{
  cache_string_texture(id,
                       renderer.render_shaded_unicode(str, m_font, background));
}

CENTURION_DEF
void font_cache::cache_solid_unicode(renderer& renderer,
                                     entt::id_type id,
                                     const unicode_string& str)
{
  cache_string_texture(id, renderer.render_solid_unicode(str, m_font));
}

CENTURION_DEF
void font_cache::cache_blended_latin1(renderer& renderer,
                                      entt::id_type id,
                                      nn_czstring str)
{
  cache_string_texture(id, renderer.render_blended_latin1(str, m_font));
}

CENTURION_DEF
void font_cache::cache_blended_wrapped_latin1(renderer& renderer,
                                              entt::id_type id,
                                              nn_czstring str,
                                              u32 wrap)
{
  cache_string_texture(
      id, renderer.render_blended_wrapped_latin1(str, m_font, wrap));
}

CENTURION_DEF
void font_cache::cache_shaded_latin1(renderer& renderer,
                                     entt::id_type id,
                                     nn_czstring str,
                                     const color& background)
{
  cache_string_texture(id,
                       renderer.render_shaded_latin1(str, m_font, background));
}

CENTURION_DEF
void font_cache::cache_solid_latin1(renderer& renderer,
                                    entt::id_type id,
                                    nn_czstring str)
{
  cache_string_texture(id, renderer.render_solid_latin1(str, m_font));
}

CENTURION_DEF
void font_cache::cache_blended_utf8(renderer& renderer,
                                    entt::id_type id,
                                    nn_czstring str)
{
  cache_string_texture(id, renderer.render_blended_utf8(str, m_font));
}

CENTURION_DEF
void font_cache::cache_blended_wrapped_utf8(renderer& renderer,
                                            entt::id_type id,
                                            nn_czstring str,
                                            u32 wrap)
{
  cache_string_texture(id,
                       renderer.render_blended_wrapped_utf8(str, m_font, wrap));
}

CENTURION_DEF
void font_cache::cache_shaded_utf8(renderer& renderer,
                                   entt::id_type id,
                                   nn_czstring str,
                                   const color& background)
{
  cache_string_texture(id,
                       renderer.render_shaded_utf8(str, m_font, background));
}

CENTURION_DEF
void font_cache::cache_solid_utf8(renderer& renderer,
                                  entt::id_type id,
                                  nn_czstring str)
{
  cache_string_texture(id, renderer.render_solid_utf8(str, m_font));
}

CENTURION_DEF
void font_cache::add_glyph(renderer& renderer, unicode glyph)
{
  if (!has(glyph)) {
    if (m_font.is_glyph_provided(glyph)) {
      m_glyphs.emplace(glyph,
                       glyph_data{create_glyph_texture(renderer, glyph),
                                  m_font.glyph_metrics(glyph).value()});
    }
  }
}

CENTURION_DEF
void font_cache::cache_range(renderer& renderer, unicode begin, unicode end)
{
  for (unicode ch = begin; ch < end; ++ch) {
    add_glyph(renderer, ch);
  }
}

CENTURION_DEF
void font_cache::cache_basic_latin(renderer& renderer)
{
  // https://unicode-table.com/en/blocks/basic-latin/
  cache_range(renderer, 0x20, 0x7F);
}

CENTURION_DEF
void font_cache::cache_latin1_supplement(renderer& renderer)
{
  // https://unicode-table.com/en/blocks/latin-1-supplement/
  cache_range(renderer, 0xA0, 0x100);
}

CENTURION_DEF
void font_cache::cache_latin1(renderer& renderer)
{
  cache_basic_latin(renderer);
  cache_latin1_supplement(renderer);
}

CENTURION_DEF
auto font_cache::try_get_cached(entt::id_type id) const noexcept
    -> const texture*
{
  const auto iterator = m_strings.find(id);
  if (iterator != m_strings.end()) {
    return &iterator->second;  // TODO test
  } else {
    return nullptr;
  }
}

}  // namespace centurion::experimental

#endif  // CENTURION_FONT_CACHE_SOURCE