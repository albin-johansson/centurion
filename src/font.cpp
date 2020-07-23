#include "font.hpp"

#include "centurion_utils.hpp"
#include "error.hpp"

namespace centurion {

font::font(nn_czstring file, int size) : m_size{size}
{
  if (size <= 0) {
    throw centurion_exception{"Bad font size!"};
  }

  m_font.reset(TTF_OpenFont(file, size));
  if (!m_font) {
    throw detail::ttf_error("Failed to open font!");
  }

  m_style = TTF_GetFontStyle(m_font.get());
}

auto font::unique(nn_czstring file, int size) -> std::unique_ptr<font>
{
  return std::make_unique<font>(file, size);
}

auto font::shared(nn_czstring file, int size) -> std::shared_ptr<font>
{
  return std::make_shared<font>(file, size);
}

void font::reset() noexcept
{
  m_style = TTF_STYLE_NORMAL;
  TTF_SetFontStyle(m_font.get(), m_style);
}

void font::add_style(int mask) noexcept
{
  m_style |= mask;
  TTF_SetFontStyle(m_font.get(), m_style);
}

void font::remove_style(int mask) noexcept
{
  m_style &= ~mask;
  TTF_SetFontStyle(m_font.get(), m_style);
}

void font::set_bold(bool bold) noexcept
{
  if (bold) {
    add_style(TTF_STYLE_BOLD);
  } else {
    remove_style(TTF_STYLE_BOLD);
  }
}

void font::set_italic(bool italic) noexcept
{
  if (italic) {
    add_style(TTF_STYLE_ITALIC);
  } else {
    remove_style(TTF_STYLE_ITALIC);
  }
}

void font::set_underlined(bool underlined) noexcept
{
  if (underlined) {
    add_style(TTF_STYLE_UNDERLINE);
  } else {
    remove_style(TTF_STYLE_UNDERLINE);
  }
}

void font::set_strikethrough(bool strikethrough) noexcept
{
  if (strikethrough) {
    add_style(TTF_STYLE_STRIKETHROUGH);
  } else {
    remove_style(TTF_STYLE_STRIKETHROUGH);
  }
}

void font::set_outline(int outline) noexcept
{
  TTF_SetFontOutline(m_font.get(), outline);
}

void font::set_font_hinting(font::hint hint) noexcept
{
  TTF_SetFontHinting(m_font.get(), static_cast<int>(hint));
}

void font::set_kerning(bool kerning) noexcept
{
  TTF_SetFontKerning(m_font.get(), kerning ? 1 : 0);
}

auto font::bold() const noexcept -> bool
{
  return m_style & TTF_STYLE_BOLD;
}

auto font::italic() const noexcept -> bool
{
  return m_style & TTF_STYLE_ITALIC;
}

auto font::underlined() const noexcept -> bool
{
  return m_style & TTF_STYLE_UNDERLINE;
}

auto font::strikethrough() const noexcept -> bool
{
  return m_style & TTF_STYLE_STRIKETHROUGH;
}

auto font::outlined() const noexcept -> bool
{
  return TTF_GetFontOutline(m_font.get());
}

auto font::is_fixed_width() const noexcept -> bool
{
  return TTF_FontFaceIsFixedWidth(m_font.get());
}

auto font::outline() const noexcept -> int
{
  return TTF_GetFontOutline(m_font.get());
}

auto font::kerning_amount(unicode firstGlyph,
                          unicode secondGlyph) const noexcept -> int
{
  const auto amount =
      TTF_GetFontKerningSizeGlyphs(m_font.get(), firstGlyph, secondGlyph);
  return amount;
}

auto font::is_glyph_provided(unicode glyph) const noexcept -> bool
{
  return TTF_GlyphIsProvided(m_font.get(), glyph);
}

auto font::get_metrics(unicode glyph) const noexcept
    -> std::optional<glyph_metrics>
{
  glyph_metrics metrics{};
  const auto result = TTF_GlyphMetrics(m_font.get(),
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

auto font::string_width(czstring s) const noexcept -> int
{
  int width{};
  TTF_SizeText(m_font.get(), s, &width, nullptr);
  return width;
}

auto font::string_height(czstring s) const noexcept -> int
{
  int height{};
  TTF_SizeText(m_font.get(), s, nullptr, &height);
  return height;
}

auto font::string_size(czstring s) const noexcept -> area_i
{
  int width{};
  int height{};
  TTF_SizeText(m_font.get(), s, &width, &height);
  return {width, height};
}

auto font::height() const noexcept -> int
{
  return TTF_FontHeight(m_font.get());
}

auto font::descent() const noexcept -> int
{
  return TTF_FontDescent(m_font.get());
}

auto font::ascent() const noexcept -> int
{
  return TTF_FontAscent(m_font.get());
}

auto font::line_skip() const noexcept -> int
{
  return TTF_FontLineSkip(m_font.get());
}

auto font::font_faces() const noexcept -> int
{
  return static_cast<int>(TTF_FontFaces(m_font.get()));
}

auto font::font_hinting() const noexcept -> font::hint
{
  return static_cast<font::hint>(TTF_GetFontHinting(m_font.get()));
}

auto font::kerning() const noexcept -> bool
{
  return TTF_GetFontKerning(m_font.get());
}

auto font::family_name() const noexcept -> czstring
{
  return TTF_FontFaceFamilyName(m_font.get());
}

auto font::style_name() const noexcept -> czstring
{
  return TTF_FontFaceStyleName(m_font.get());
}

auto font::ttf_version() noexcept -> SDL_version
{
  SDL_version version;
  SDL_TTF_VERSION(&version)
  return version;
}

auto font::to_string() const -> std::string
{
  const auto idStr = "font@" + detail::address_of(this);
  const auto nameStr = " | Name: " + std::string{family_name()};
  const auto sizeStr = ", Size: " + std::to_string(size());
  return "[" + idStr + nameStr + sizeStr + "]";
}

}  // namespace centurion
