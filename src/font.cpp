#ifndef CENTURION_FONT_SOURCE
#define CENTURION_FONT_SOURCE

#include "font.hpp"

#include "centurion_utils.hpp"
#include "error.hpp"

namespace centurion {

CENTURION_DEF
font::font(czstring file, int size) : m_size{size}
{
  if (!file) {
    throw centurion_exception{"Cannot create Font from null path!"};
  }

  if (size <= 0) {
    throw centurion_exception{"Bad font size!"};
  }

  m_font = TTF_OpenFont(file, size);
  if (!m_font) {
    throw detail::Error::from_ttf("Failed to open font!");
  }

  m_style = TTF_GetFontStyle(m_font);
}

CENTURION_DEF
font::font(font&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
font::~font() noexcept
{
  destroy();
}

CENTURION_DEF
auto font::operator=(font&& other) noexcept -> font&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void font::destroy() noexcept
{
  if (m_font) {
    TTF_CloseFont(m_font);
  }
}

CENTURION_DEF
void font::move(font&& other) noexcept
{
  destroy();

  m_font = other.m_font;
  m_style = other.m_style;
  m_size = other.m_size;

  other.m_font = nullptr;
}

CENTURION_DEF
auto font::unique(czstring file, int size) -> std::unique_ptr<font>
{
  return std::make_unique<font>(file, size);
}

CENTURION_DEF
auto font::shared(czstring file, int size) -> std::shared_ptr<font>
{
  return std::make_shared<font>(file, size);
}

CENTURION_DEF
void font::reset() noexcept
{
  m_style = TTF_STYLE_NORMAL;
  TTF_SetFontStyle(m_font, m_style);
}

CENTURION_DEF
void font::add_style(int mask) noexcept
{
  m_style |= mask;
  TTF_SetFontStyle(m_font, m_style);
}

CENTURION_DEF
void font::remove_style(int mask) noexcept
{
  m_style &= ~mask;
  TTF_SetFontStyle(m_font, m_style);
}

CENTURION_DEF
void font::set_bold(bool bold) noexcept
{
  if (bold) {
    add_style(TTF_STYLE_BOLD);
  } else {
    remove_style(TTF_STYLE_BOLD);
  }
}

CENTURION_DEF
void font::set_italic(bool italic) noexcept
{
  if (italic) {
    add_style(TTF_STYLE_ITALIC);
  } else {
    remove_style(TTF_STYLE_ITALIC);
  }
}

CENTURION_DEF
void font::set_underlined(bool underlined) noexcept
{
  if (underlined) {
    add_style(TTF_STYLE_UNDERLINE);
  } else {
    remove_style(TTF_STYLE_UNDERLINE);
  }
}

CENTURION_DEF
void font::set_strikethrough(bool strikethrough) noexcept
{
  if (strikethrough) {
    add_style(TTF_STYLE_STRIKETHROUGH);
  } else {
    remove_style(TTF_STYLE_STRIKETHROUGH);
  }
}

CENTURION_DEF
void font::set_outlined(bool outlined) noexcept
{
  TTF_SetFontOutline(m_font, outlined ? 1 : 0);
}

CENTURION_DEF
void font::set_font_hinting(font::Hint hint) noexcept
{
  TTF_SetFontHinting(m_font, static_cast<int>(hint));
}

CENTURION_DEF
void font::set_kerning(bool kerning) noexcept
{
  TTF_SetFontKerning(m_font, kerning ? 1 : 0);
}

CENTURION_DEF
auto font::bold() const noexcept -> bool
{
  return m_style & TTF_STYLE_BOLD;
}

CENTURION_DEF
auto font::italic() const noexcept -> bool
{
  return m_style & TTF_STYLE_ITALIC;
}

CENTURION_DEF
auto font::underlined() const noexcept -> bool
{
  return m_style & TTF_STYLE_UNDERLINE;
}

CENTURION_DEF
auto font::strikethrough() const noexcept -> bool
{
  return m_style & TTF_STYLE_STRIKETHROUGH;
}

CENTURION_DEF
auto font::outlined() const noexcept -> bool
{
  return TTF_GetFontOutline(m_font);
}

CENTURION_DEF
auto font::is_fixed_width() const noexcept -> bool
{
  return TTF_FontFaceIsFixedWidth(m_font);
}

CENTURION_DEF
auto font::kerning_amount(u16 firstGlyph, u16 secondGlyph) const noexcept -> int
{
  const auto amount =
      TTF_GetFontKerningSizeGlyphs(m_font, firstGlyph, secondGlyph);
  return amount;
}

CENTURION_DEF
auto font::is_glyph_provided(u16 glyph) const noexcept -> bool
{
  return TTF_GlyphIsProvided(m_font, glyph);
}

CENTURION_DEF
auto font::glyph_metrics(u16 glyph) const noexcept
    -> std::optional<struct glyph_metrics>
{
  centurion::glyph_metrics metrics{};
  const auto result = TTF_GlyphMetrics(m_font,
                                       glyph,
                                       &metrics.minX,
                                       &metrics.maxX,
                                       &metrics.minY,
                                       &metrics.maxY,
                                       &metrics.advance);
  if (result != -1) {
    return metrics;
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto font::string_width(czstring s) const noexcept -> int
{
  int width = 0;
  TTF_SizeText(m_font, s, &width, nullptr);
  return width;
}

CENTURION_DEF
auto font::string_height(czstring s) const noexcept -> int
{
  int height = 0;
  TTF_SizeText(m_font, s, nullptr, &height);
  return height;
}

CENTURION_DEF
auto font::string_size(czstring s) const noexcept -> area_i
{
  int width = 0;
  int height = 0;
  TTF_SizeText(m_font, s, &width, &height);
  return {width, height};
}

CENTURION_DEF
auto font::height() const noexcept -> int
{
  return TTF_FontHeight(m_font);
}

CENTURION_DEF
auto font::descent() const noexcept -> int
{
  return TTF_FontDescent(m_font);
}

CENTURION_DEF
auto font::ascent() const noexcept -> int
{
  return TTF_FontAscent(m_font);
}

CENTURION_DEF
auto font::line_skip() const noexcept -> int
{
  return TTF_FontLineSkip(m_font);
}

CENTURION_DEF
auto font::font_faces() const noexcept -> int
{
  return static_cast<int>(TTF_FontFaces(m_font));
}

CENTURION_DEF
auto font::font_hinting() const noexcept -> font::Hint
{
  return static_cast<font::Hint>(TTF_GetFontHinting(m_font));
}

CENTURION_DEF
auto font::kerning() const noexcept -> bool
{
  return TTF_GetFontKerning(m_font);
}

CENTURION_DEF
auto font::family_name() const noexcept -> czstring
{
  return TTF_FontFaceFamilyName(m_font);
}

CENTURION_DEF
auto font::style_name() const noexcept -> czstring
{
  return TTF_FontFaceStyleName(m_font);
}

CENTURION_DEF
auto font::ttf_version() noexcept -> SDL_version
{
  SDL_version version;
  SDL_TTF_VERSION(&version);
  return version;
}

CENTURION_DEF
auto font::to_string() const -> std::string
{
  const auto idStr = "Font@" + detail::address_of(this);
  const auto nameStr = " | Name: " + std::string{family_name()};
  const auto sizeStr = ", Size: " + std::to_string(size());
  return "[" + idStr + nameStr + sizeStr + "]";
}

}  // namespace centurion

#endif  // CENTURION_FONT_SOURCE