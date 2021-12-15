#ifndef CENTURION_VIDEO_FONT_CACHE_HPP_
#define CENTURION_VIDEO_FONT_CACHE_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <cassert>        // assert
#include <string>         // string
#include <unordered_map>  // unordered_map
#include <utility>        // move, forward

#include "../core/common.hpp"
#include "../render.hpp"
#include "../texture.hpp"
#include "font.hpp"
#include "surface.hpp"
#include "unicode_string.hpp"

namespace cen {

/**
 * Provides an API that enables efficient font rendering.
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
 */
class FontCache final {
 public:
  struct GlyphData final {
    Texture texture;
    GlyphMetrics metrics;
  };

  FontCache(const char* file, const int size) : mFont{file, size} {}

  FontCache(const std::string& file, const int size) : mFont{file, size} {}

  explicit FontCache(Font&& font) noexcept : mFont{std::move(font)} {}

  /* Renders a glyph and returns the next x-coordinate */
  template <typename T>
  auto RenderGlyph(BasicRenderer<T>& renderer, const Unicode glyph, const Point& position)
      -> int
  {
    if (const auto* data = TryGetGlyph(glyph)) {
      const auto& [texture, metrics] = *data;
      const auto outline = mFont.GetOutline();

      /* SDL_ttf handles the y-axis alignment */
      const auto x = position.GetX() + metrics.min_x - outline;
      const auto y = position.GetY() - outline;

      renderer.Render(texture, Point{x, y});

      return x + metrics.advance;
    }
    else {
      return position.GetX();
    }
  }

  /* Renders a string as a series of glyphs */
  template <typename T, typename String>
  void RenderText(BasicRenderer<T>& renderer, const String& str, Point position)
  {
    const auto originalX = position.GetX();
    const auto lineSkip = mFont.GetLineSkip();

    for (const Unicode glyph : str) {
      if (glyph == '\n') {
        position.SetX(originalX);
        position.SetY(position.GetY() + lineSkip);
      }
      else {
        const auto x = RenderGlyph(renderer, glyph, position);
        position.SetX(x);
      }
    }
  }

  template <typename T>
  auto StoreSolidUTF8(BasicRenderer<T>& renderer, const char* str, const Color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderSolidUTF8(str, color));
  }

  template <typename T>
  auto StoreShadedUTF8(BasicRenderer<T>& renderer,
                       const char* str,
                       const Color& fg,
                       const Color& bg) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderShadedUTF8(str, fg, bg));
  }

  template <typename T>
  auto StoreBlendedUTF8(BasicRenderer<T>& renderer, const char* str, const Color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedUTF8(str, color));
  }

  template <typename T>
  auto StoreWrappedUTF8(BasicRenderer<T>& renderer,
                        const char* str,
                        const Color& color,
                        const Uint32 wrap) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedWrappedUTF8(str, color, wrap));
  }

  template <typename T>
  auto StoreSolidLatin1(BasicRenderer<T>& renderer, const char* str, const Color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderSolidLatin1(str, color));
  }

  template <typename T>
  auto StoreShadedLatin1(BasicRenderer<T>& renderer,
                         const char* str,
                         const Color& fg,
                         const Color& bg) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderShadedLatin1(str, fg, bg));
  }

  template <typename T>
  auto StoreBlendedLatin1(BasicRenderer<T>& renderer, const char* str, const Color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedLatin1(str, color));
  }

  template <typename T>
  auto StoreWrappedLatin1(BasicRenderer<T>& renderer,
                          const char* str,
                          const Color& color,
                          const Uint32 wrap) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedWrappedLatin1(str, color, wrap));
  }

  template <typename T>
  auto StoreSolidUnicode(BasicRenderer<T>& renderer,
                         const UnicodeString& str,
                         const Color& color) -> std::size_t
  {
    return Store(renderer, mFont.RenderSolidUnicode(str, color));
  }

  template <typename T>
  auto StoreShadedUnicode(BasicRenderer<T>& renderer,
                          const UnicodeString& str,
                          const Color& fg,
                          const Color& bg) -> std::size_t
  {
    return Store(renderer, mFont.RenderShadedUnicode(str, fg, bg));
  }

  template <typename T>
  auto StoreBlendedUnicode(BasicRenderer<T>& renderer,
                           const UnicodeString& str,
                           const Color& color) -> std::size_t
  {
    return Store(renderer, mFont.RenderBlendedUnicode(str, color));
  }

  template <typename T>
  auto StoreWrappedUnicode(BasicRenderer<T>& renderer,
                           const UnicodeString& str,
                           const Color& color,
                           const Uint32 wrap) -> std::size_t
  {
    return Store(renderer, mFont.RenderBlendedWrappedUnicode(str, color, wrap));
  }

  [[nodiscard]] auto HasString(const std::size_t id) const noexcept -> bool
  {
    return mStrings.find(id) != mStrings.end();
  }

  [[nodiscard]] auto GetString(const std::size_t id) const -> const Texture&
  {
    return mStrings.at(id);
  }

  [[nodiscard]] auto TryGetString(const std::size_t id) const noexcept -> const Texture*
  {
    const auto it = mStrings.find(id);
    if (it != mStrings.end()) {
      return &it->second;
    }
    else {
      return nullptr;
    }
  }

  template <typename T>
  void StoreGlyph(BasicRenderer<T>& renderer, const Unicode glyph)
  {
    if (HasGlyph(glyph) || !mFont.IsGlyphProvided(glyph)) {
      return;
    }

    GlyphData data{CreateGlyphTexture(renderer, glyph), mFont.GetMetrics(glyph).value()};
    mGlyphs.try_emplace(glyph, std::move(data));
  }

  template <typename T>
  void StoreGlyphRange(BasicRenderer<T>& renderer, const Unicode begin, const Unicode end)
  {
    for (auto ch = begin; ch < end; ++ch) {
      StoreGlyph(renderer, ch);
    }
  }

  template <typename T>
  void StoreBasicLatinGlyphs(BasicRenderer<T>& renderer)
  {
    /* https://unicode-table.com/en/blocks/basic-latin/ */
    StoreGlyphRange(renderer, 0x20, 0x7F);
  }

  template <typename T>
  void StoreLatin1SupplementGlyphs(BasicRenderer<T>& renderer)
  {
    /* https://unicode-table.com/en/blocks/latin-1-supplement/ */
    StoreGlyphRange(renderer, 0xA0, 0x100);
  }

  template <typename T>
  void StoreLatin1Glyphs(BasicRenderer<T>& renderer)
  {
    StoreBasicLatinGlyphs(renderer);
    StoreLatin1SupplementGlyphs(renderer);
  }

  [[nodiscard]] auto HasGlyph(const Unicode glyph) const noexcept -> bool
  {
    return mGlyphs.find(glyph) != mGlyphs.end();
  }

  [[nodiscard]] auto GetGlyph(const Unicode glyph) const -> const GlyphData&
  {
    return mGlyphs.at(glyph);
  }

  [[nodiscard]] auto TryGetGlyph(const Unicode glyph) const -> const GlyphData*
  {
    if (const auto it = mGlyphs.find(glyph); it != mGlyphs.end()) {
      return &it->second;
    }
    else {
      return nullptr;
    }
  }

  [[nodiscard]] auto GetFont() noexcept -> Font& { return mFont; }
  [[nodiscard]] auto GetFont() const noexcept -> const Font& { return mFont; }

 private:
  Font mFont;
  std::unordered_map<Unicode, GlyphData> mGlyphs;
  std::unordered_map<std::size_t, Texture> mStrings;
  std::size_t mNextStringId{1};

  template <typename T>
  [[nodiscard]] auto CreateGlyphTexture(BasicRenderer<T>& renderer, const Unicode glyph)
      -> Texture
  {
    return Texture{renderer, mFont.RenderBlendedGlyph(glyph, renderer.GetColor())};
  }

  template <typename T>
  auto Store(BasicRenderer<T>& renderer, Surface&& surface) -> std::size_t
  {
    const auto id = mNextStringId;
    assert(mStrings.find(id) == mStrings.end());

    mStrings.try_emplace(id, Texture{renderer, surface});
    ++mNextStringId;

    return id;
  }
};

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_VIDEO_FONT_CACHE_HPP_