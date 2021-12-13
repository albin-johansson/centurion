#ifndef CENTURION_VIDEO_FONT_HPP_
#define CENTURION_VIDEO_FONT_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "../core/common.hpp"
#include "../core/exception.hpp"
#include "../core/features.hpp"
#include "../core/memory.hpp"
#include "../detail/stdlib.hpp"
#include "../math/area.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup video
/// \{

struct GlyphMetrics final {
  int min_x{};   /* The minimum X-offset. */
  int min_y{};   /* The minimum Y-offset. */
  int max_x{};   /* The maximum X-offset. */
  int max_y{};   /* The maximum Y-offset. */
  int advance{}; /* The advance offset. */
};

enum class FontHint : int {
  Normal = TTF_HINTING_NORMAL,
  Light = TTF_HINTING_LIGHT,
  Mono = TTF_HINTING_MONO,
  None = TTF_HINTING_NONE
};

class Font final {
 public:
  Font(const char* file, const int size) : mSize{size}
  {
    assert(file);

    if (size <= 0) {
      throw Error{"Bad font size!"};
    }

    mFont.reset(TTF_OpenFont(file, size));
    if (!mFont) {
      throw TTFError{};
    }
  }

  Font(const std::string& file, const int size) : Font{file.c_str(), size} {}

  void ResetStyle() noexcept { TTF_SetFontStyle(mFont.get(), TTF_STYLE_NORMAL); }

  void SetBold(const bool bold) noexcept
  {
    if (bold) {
      AddStyle(TTF_STYLE_BOLD);
    }
    else {
      RemoveStyle(TTF_STYLE_BOLD);
    }
  }

  void SetItalic(const bool italic) noexcept
  {
    if (italic) {
      AddStyle(TTF_STYLE_ITALIC);
    }
    else {
      RemoveStyle(TTF_STYLE_ITALIC);
    }
  }

  void SetUnderlined(const bool underlined) noexcept
  {
    if (underlined) {
      AddStyle(TTF_STYLE_UNDERLINE);
    }
    else {
      RemoveStyle(TTF_STYLE_UNDERLINE);
    }
  }

  void SetStrikethrough(const bool strikethrough) noexcept
  {
    if (strikethrough) {
      AddStyle(TTF_STYLE_STRIKETHROUGH);
    }
    else {
      RemoveStyle(TTF_STYLE_STRIKETHROUGH);
    }
  }

  void SetKerning(const bool kerning) noexcept
  {
    TTF_SetFontKerning(mFont.get(), kerning ? 1 : 0);
  }

  void SetOutline(const int outline) noexcept { TTF_SetFontOutline(mFont.get(), outline); }

  void SetFontHinting(const FontHint hint) noexcept
  {
    TTF_SetFontHinting(mFont.get(), to_underlying(hint));
  }

  [[nodiscard]] auto IsBold() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_BOLD;
  }

  [[nodiscard]] auto IsItalic() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_ITALIC;
  }

  [[nodiscard]] auto IsUnderlined() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_UNDERLINE;
  }

  [[nodiscard]] auto IsStrikethrough() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_STRIKETHROUGH;
  }

  [[nodiscard]] auto HasKerning() const noexcept -> bool
  {
    return TTF_GetFontKerning(mFont.get());
  }

  [[nodiscard]] auto IsFixedWidth() const noexcept -> bool
  {
    return TTF_FontFaceIsFixedWidth(mFont.get());
  }

  [[nodiscard]] auto IsOutlined() const noexcept -> bool { return GetOutline() != 0; }

  [[nodiscard]] auto GetOutline() const noexcept -> int
  {
    return TTF_GetFontOutline(mFont.get());
  }

  [[nodiscard]] auto GetFontHinting() const noexcept -> FontHint
  {
    return static_cast<FontHint>(TTF_GetFontHinting(mFont.get()));
  }

  /* Returns the maximum height of a character in this font. */
  [[nodiscard]] auto GetHeight() const noexcept -> int { return TTF_FontHeight(mFont.get()); }

  /* Returns the offset from the baseline to the bottom of the font characters. */
  [[nodiscard]] auto GetDescent() const noexcept -> int
  {
    return TTF_FontDescent(mFont.get());
  }

  /* Returns the offset from the baseline to the top of the font characters. */
  [[nodiscard]] auto GetAscent() const noexcept -> int { return TTF_FontAscent(mFont.get()); }

  /* Returns the recommended vertical spacing between lines of rendered text. */
  [[nodiscard]] auto GetLineSkip() const noexcept -> int
  {
    return TTF_FontLineSkip(mFont.get());
  }

  /* Returns the number of available font faces. */
  [[nodiscard]] auto GetFontFaces() const noexcept -> int
  {
    return static_cast<int>(TTF_FontFaces(mFont.get()));
  }

  [[nodiscard]] auto GetFamilyName() const noexcept -> const char*
  {
    return TTF_FontFaceFamilyName(mFont.get());
  }

  [[nodiscard]] auto GetStyleName() const noexcept -> const char*
  {
    return TTF_FontFaceStyleName(mFont.get());
  }

  [[nodiscard]] auto GetSize() const noexcept -> int { return mSize; }

  /* Returns the kerning amount between two glyphs. */
  [[nodiscard]] auto GetKerning(const Unicode previous, const Unicode current) const noexcept
      -> int
  {
    return TTF_GetFontKerningSizeGlyphs(mFont.get(), previous, current);
  }

  [[nodiscard]] auto IsGlyphProvided(const Unicode glyph) const noexcept -> bool
  {
    return TTF_GlyphIsProvided(mFont.get(), glyph);
  }

  [[nodiscard]] auto GetMetrics(const Unicode glyph) const noexcept
      -> std::optional<GlyphMetrics>
  {
    GlyphMetrics metrics;
    if (TTF_GlyphMetrics(mFont.get(),
                         glyph,
                         &metrics.min_x,
                         &metrics.max_x,
                         &metrics.min_y,
                         &metrics.max_y,
                         &metrics.advance) != -1) {
      return metrics;
    }
    else {
      return std::nullopt;
    }
  }

  /* Returns the size of a rendered string. */
  [[nodiscard]] auto CalcSize(const char* str) const noexcept -> std::optional<iarea>
  {
    assert(str);

    iarea size{};
    if (TTF_SizeText(mFont.get(), str, &size.width, &size.height) != -1) {
      return size;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto CalcSize(const std::string& str) const noexcept -> std::optional<iarea>
  {
    return CalcSize(str.c_str());
  }

  [[nodiscard]] auto get() const noexcept -> TTF_Font* { return mFont.get(); }

 private:
  Managed<TTF_Font> mFont;
  int mSize{};

  void AddStyle(const int mask) noexcept
  {
    const auto style = TTF_GetFontStyle(mFont.get());
    TTF_SetFontStyle(mFont.get(), style | mask);
  }

  void RemoveStyle(const int mask) noexcept
  {
    const auto style = TTF_GetFontStyle(mFont.get());
    TTF_SetFontStyle(mFont.get(), style & ~mask);
  }
};

[[nodiscard]] constexpr auto to_string(const FontHint hint) -> std::string_view
{
  switch (hint) {
    case FontHint::Normal:
      return "Normal";

    case FontHint::Light:
      return "Light";

    case FontHint::Mono:
      return "Mono";

    case FontHint::None:
      return "None";

    default:
      throw Error{"Did not recognize font hint!"};
  }
}

[[nodiscard]] inline auto to_string(const Font& font) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Font(data: {}, name: {}, size: {})",
                     detail::address_of(font.get()),
                     font.GetFamilyName(),
                     font.GetSize());
#else
  return "Font(data: " + detail::address_of(font.get()) +
         ", name: " + std::string{font.GetFamilyName()} +
         ", size: " + std::to_string(font.GetSize()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const FontHint hint) -> std::ostream&
{
  return stream << to_string(hint);
}

inline auto operator<<(std::ostream& stream, const Font& font) -> std::ostream&
{
  return stream << to_string(font);
}

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_VIDEO_FONT_HPP_