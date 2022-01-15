#ifndef CENTURION_FONT_HPP_
#define CENTURION_FONT_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL.h>
#include <SDL_ttf.h>

#include <cassert>        // assert
#include <cstddef>        // size_t
#include <cstring>        // strcmp
#include <filesystem>     // path
#include <memory>         // unique_ptr
#include <optional>       // optional
#include <ostream>        // ostream
#include <string>         // string, to_string
#include <string_view>    // string_view
#include <unordered_map>  // unordered_map
#include <utility>        // move, forward

#include "color.hpp"
#include "common.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "memory.hpp"
#include "render.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode.hpp"

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
    TTF_SetFontHinting(mFont.get(), ToUnderlying(hint));
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
  [[nodiscard]] auto CalcSize(const char* str) const noexcept -> std::optional<Area>
  {
    assert(str);

    Area size{};
    if (TTF_SizeText(mFont.get(), str, &size.width, &size.height) != -1) {
      return size;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto CalcSize(const std::string& str) const noexcept -> std::optional<Area>
  {
    return CalcSize(str.c_str());
  }

  [[nodiscard]] auto RenderBlendedGlyph(const Unicode glyph, const color& color) const
      -> Surface
  {
    return Surface{TTF_RenderGlyph_Blended(get(), glyph, color.get())};
  }

  [[nodiscard]] auto RenderSolidGlyph(const Unicode glyph, const color& color) const -> Surface
  {
    return Surface{TTF_RenderGlyph_Solid(get(), glyph, color.get())};
  }

  [[nodiscard]] auto RenderShadedGlyph(const Unicode glyph,
                                       const color& fg,
                                       const color& bg) const -> Surface
  {
    return Surface{TTF_RenderGlyph_Shaded(get(), glyph, fg.get(), bg.get())};
  }

  [[nodiscard]] auto RenderBlendedUTF8(const char* str, const color& color) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Blended(get(), str, color.get())};
  }

  [[nodiscard]] auto RenderBlendedUTF8(const std::string& str, const color& color) const
      -> Surface
  {
    return RenderBlendedUTF8(str.c_str(), color);
  }

  [[nodiscard]] auto RenderBlendedWrappedUTF8(const char* str,
                                              const color& color,
                                              const Uint32 wrap) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Blended_Wrapped(get(), str, color.get(), wrap)};
  }

  [[nodiscard]] auto RenderBlendedWrappedUTF8(const std::string& str,
                                              const color& color,
                                              const Uint32 wrap) const -> Surface
  {
    return RenderBlendedWrappedUTF8(str.c_str(), color, wrap);
  }

  [[nodiscard]] auto RenderShadedUTF8(const char* str, const color& fg, const color& bg) const
      -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Shaded(get(), str, fg.get(), bg.get())};
  }

  [[nodiscard]] auto RenderShadedUTF8(const std::string& str,
                                      const color& fg,
                                      const color& bg) const -> Surface
  {
    return RenderShadedUTF8(str.c_str(), fg, bg);
  }

  [[nodiscard]] auto RenderSolidUTF8(const char* str, const color& color) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Solid(get(), str, color.get())};
  }

  [[nodiscard]] auto RenderSolidUTF8(const std::string& str, const color& color) const
      -> Surface
  {
    return RenderSolidUTF8(str.c_str(), color);
  }

  [[nodiscard]] auto RenderBlendedLatin1(const char* str, const color& color) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Blended(get(), str, color.get())};
  }

  [[nodiscard]] auto RenderBlendedLatin1(const std::string& str, const color& color) const
      -> Surface
  {
    return RenderBlendedLatin1(str.c_str(), color);
  }

  [[nodiscard]] auto RenderBlendedWrappedLatin1(const char* str,
                                                const color& color,
                                                const Uint32 wrap) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Blended_Wrapped(get(), str, color.get(), wrap)};
  }

  [[nodiscard]] auto RenderBlendedWrappedLatin1(const std::string& str,
                                                const color& color,
                                                const Uint32 wrap) const -> Surface
  {
    return RenderBlendedWrappedLatin1(str.c_str(), color, wrap);
  }

  [[nodiscard]] auto RenderShadedLatin1(const char* str,
                                        const color& fg,
                                        const color& bg) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Shaded(get(), str, fg.get(), bg.get())};
  }

  [[nodiscard]] auto RenderShadedLatin1(const std::string& str,
                                        const color& fg,
                                        const color& bg) const -> Surface
  {
    return RenderShadedLatin1(str.c_str(), fg, bg);
  }

  [[nodiscard]] auto RenderSolidLatin1(const char* str, const color& color) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Solid(get(), str, color.get())};
  }

  [[nodiscard]] auto RenderSolidLatin1(const std::string& str, const color& color) const
      -> Surface
  {
    return RenderSolidLatin1(str.c_str(), color);
  }

  [[nodiscard]] auto RenderBlendedUnicode(const UnicodeString& str, const color& color) const
      -> Surface
  {
    return Surface{TTF_RenderUNICODE_Blended(get(), str.data(), color.get())};
  }

  [[nodiscard]] auto RenderBlendedWrappedUnicode(const UnicodeString& str,
                                                 const color& color,
                                                 const Uint32 wrap) const -> Surface
  {
    return Surface{TTF_RenderUNICODE_Blended_Wrapped(get(), str.data(), color.get(), wrap)};
  }

  [[nodiscard]] auto RenderShadedUnicode(const UnicodeString& str,
                                         const color& fg,
                                         const color& bg) const -> Surface
  {
    return Surface{TTF_RenderUNICODE_Shaded(get(), str.data(), fg.get(), bg.get())};
  }

  [[nodiscard]] auto RenderSolidUnicode(const UnicodeString& str, const color& color) const
      -> Surface
  {
    return Surface{TTF_RenderUNICODE_Solid(get(), str.data(), color.get())};
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

/**
 * Provides efficient font rendering.
 *
 * Firstly, this class can be used to cache individual glyphs as textures that can subsequently
 * be rendered one-by-one to form strings. Note, this approach will not result in accurate
 * kerning. However, this might not be noticeable, and simply worth the performance boost. This
 * approach is very efficient for rendering pieces of text that frequently changes, since
 * other approaches would require dynamic allocation and de-allocation for every new rendered
 * string.
 *
 * Secondly, it's possible to cache rendered strings and associate them with integer
 * identifiers. In contrast with the first approach, this will result in accurate kerning. The
 * only problem is that it's hard to know the exact strings you will render at compile-time.
 * Use this option if you know that you're going to render some specific string a lot.
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
  auto StoreSolidUTF8(BasicRenderer<T>& renderer, const char* str, const color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderSolidUTF8(str, color));
  }

  template <typename T>
  auto StoreShadedUTF8(BasicRenderer<T>& renderer,
                       const char* str,
                       const color& fg,
                       const color& bg) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderShadedUTF8(str, fg, bg));
  }

  template <typename T>
  auto StoreBlendedUTF8(BasicRenderer<T>& renderer, const char* str, const color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedUTF8(str, color));
  }

  template <typename T>
  auto StoreWrappedUTF8(BasicRenderer<T>& renderer,
                        const char* str,
                        const color& color,
                        const Uint32 wrap) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedWrappedUTF8(str, color, wrap));
  }

  template <typename T>
  auto StoreSolidLatin1(BasicRenderer<T>& renderer, const char* str, const color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderSolidLatin1(str, color));
  }

  template <typename T>
  auto StoreShadedLatin1(BasicRenderer<T>& renderer,
                         const char* str,
                         const color& fg,
                         const color& bg) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderShadedLatin1(str, fg, bg));
  }

  template <typename T>
  auto StoreBlendedLatin1(BasicRenderer<T>& renderer, const char* str, const color& color)
      -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedLatin1(str, color));
  }

  template <typename T>
  auto StoreWrappedLatin1(BasicRenderer<T>& renderer,
                          const char* str,
                          const color& color,
                          const Uint32 wrap) -> std::size_t
  {
    assert(str);
    return Store(renderer, mFont.RenderBlendedWrappedLatin1(str, color, wrap));
  }

  template <typename T>
  auto StoreSolidUnicode(BasicRenderer<T>& renderer,
                         const UnicodeString& str,
                         const color& color) -> std::size_t
  {
    return Store(renderer, mFont.RenderSolidUnicode(str, color));
  }

  template <typename T>
  auto StoreShadedUnicode(BasicRenderer<T>& renderer,
                          const UnicodeString& str,
                          const color& fg,
                          const color& bg) -> std::size_t
  {
    return Store(renderer, mFont.RenderShadedUnicode(str, fg, bg));
  }

  template <typename T>
  auto StoreBlendedUnicode(BasicRenderer<T>& renderer,
                           const UnicodeString& str,
                           const color& color) -> std::size_t
  {
    return Store(renderer, mFont.RenderBlendedUnicode(str, color));
  }

  template <typename T>
  auto StoreWrappedUnicode(BasicRenderer<T>& renderer,
                           const UnicodeString& str,
                           const color& color,
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
    return renderer.ToTexture(mFont.RenderBlendedGlyph(glyph, renderer.GetColor()));
  }

  template <typename T>
  auto Store(BasicRenderer<T>& renderer, Surface&& surface) -> std::size_t
  {
    const auto id = mNextStringId;
    assert(mStrings.find(id) == mStrings.end());

    mStrings.try_emplace(id, renderer.ToTexture(surface));
    ++mNextStringId;

    return id;
  }
};

/**
 * \brief Utility for handling fonts of various sizes.
 *
 * \details The main motivation behind this utility is the fact that it is common to load the
 * same font family in several different sizes. This class provides a simple API for
 * efficiently managing such pools of fonts.
 *
 * \details This class works by organizing different pools of fonts based on their file paths.
 * Which means that the same font, loaded from different file paths, will be put into different
 * pools.
 *
 * \note Despite the name, this class actually stores `font_cache` instances. However, you can
 * still simply extract the underlying `font` instances if you do not need the extra features
 * provided by the `font_cache` class.
 *
 * \see `font`
 * \see `font_cache`
 */
class font_bundle final {
 public:
  using id_type = std::size_t;
  using size_type = std::size_t;

  /**
   * \brief Loads a font in a specific size.
   *
   * \details It is safe to load a font that has already been previously loaded. Furthermore,
   * this function has no effect if there is already a font of the specified size stored in the
   * pool for the font family.
   *
   * \param path the file path of the font.
   * \param size the size of the font.
   *
   * \return the identifier associated with the font.
   */
  auto load_font(const char* path, const int size) -> id_type
  {
    assert(path);
    if (const auto id = get_id(path)) {
      mPools[*id].caches.try_emplace(size, Font{path, size});
      return *id;
    }
    else {
      const auto newId = mNextFontId;

      auto& pack = mPools[newId];
      pack.path = path;
      pack.caches.try_emplace(size, Font{path, size});

      ++mNextFontId;

      return newId;
    }
  }

  /**
   * \brief Indicates whether or not there is a font pool associated with an ID.
   *
   * \param id the pool ID that will be checked.
   *
   * \return `true` if there is a font pool associated with the ID; `false` otherwise.
   */
  [[nodiscard]] auto contains(const id_type id) const -> bool
  {
    return mPools.find(id) != mPools.end();
  }

  /**
   * \brief Indicates whether there is a pool for the specified file path.
   *
   * \param path the file path that will be checked.
   *
   * \return `true` if a pool is found; `false` otherwise.
   */
  [[nodiscard]] auto contains(const std::string_view path) const -> bool
  {
    return get_id(path).has_value();
  }

  /**
   * \brief Indicates whether there is a font of a specific size in a pool.
   *
   * \details This function returns `false` if an invalid pool identifier is used.
   *
   * \param id the identifier associated with the pool that will be checked.
   * \param size the font size to look for.
   *
   * \return `true` if there is a font of the specific size in the pool; `false` otherwise.
   */
  [[nodiscard]] auto contains(const id_type id, const int size) const -> bool
  {
    if (const auto pack = mPools.find(id); pack != mPools.end()) {
      return pack->second.caches.find(size) != pack->second.caches.end();
    }
    else {
      return false;
    }
  }

  /**
   * \brief Returns a previously loaded font of a particular size from a pool.
   *
   * \param id the identifier of the pool to query.
   * \param size the size of the desired font.
   *
   * \return the found font cache.
   *
   * \throws Error if the identifier is invalid or if there is no font of the specified size.
   */
  [[nodiscard]] auto at(const id_type id, const int size) -> FontCache&
  {
    if (const auto pool = mPools.find(id); pool != mPools.end()) {
      auto& caches = pool->second.caches;
      if (const auto cache = caches.find(size); cache != caches.end()) {
        return cache->second;
      }
      else {
        throw Error{"No loaded font of the requested size!"};
      }
    }
    else {
      throw Error{"Invalid font pool identifier!"};
    }
  }

  /// \copydoc at()
  [[nodiscard]] auto at(const id_type id, const int size) const -> const FontCache&
  {
    return mPools.at(id).caches.at(size);
  }

  /**
   * \brief Returns a previously loaded font of a particular size from a pool.
   *
   * \note This function is provided as a shorthand, and simply calls `at()` and extracts the
   * font from the found font cache.
   *
   * \param id the identifier of the pool to query.
   * \param size the size of the desired font.
   *
   * \return the found font.
   *
   * \throws Error if the identifier is invalid or if there is no font of the specified size.
   *
   * \see `at()`
   */
  [[nodiscard]] auto get_font(const id_type id, const int size) -> Font&
  {
    return at(id, size).GetFont();
  }

  /// \copydoc get_font()
  [[nodiscard]] auto get_font(const id_type id, const int size) const -> const Font&
  {
    return at(id, size).GetFont();
  }

  /**
   * \brief Returns the amount of fonts that have been loaded (including different sizes).
   *
   * \return the total amount of loaded individual fonts.
   *
   * \see `pool_count()`
   */
  [[nodiscard]] auto font_count() const noexcept -> size_type
  {
    size_type count = 0;

    for (const auto& [id, pack] : mPools) {
      count += pack.caches.size();
    }

    return count;
  }

  /**
   * \brief Returns the amount of loaded font pools, i.e. font faces irrespective of sizes.
   *
   * \return the number of font pools.
   *
   * \see `font_count()`
   */
  [[nodiscard]] auto pool_count() const -> size_type { return mPools.size(); }

 private:
  struct font_pool final {
    std::string path;
    std::unordered_map<int, FontCache> caches;  ///< Size -> Cache
  };

  std::unordered_map<id_type, font_pool> mPools;
  id_type mNextFontId{1};

  [[nodiscard]] auto get_id(const std::string_view path) const -> std::optional<id_type>
  {
    for (const auto& [id, pack] : mPools) {
      if (!pack.caches.empty()) {
        if (pack.path == path) {
          return id;
        }
      }
    }

    return std::nullopt;
  }
};

/// \name Font bundle functions
/// \{

[[nodiscard]] inline auto to_string(const font_bundle& bundle) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("font_bundle(#pools: {}, #fonts: {})",
                     bundle.pool_count(),
                     bundle.font_count());
#else
  return "font_bundle(#pools: " + std::to_string(bundle.pool_count()) +
         ", #fonts: " + std::to_string(bundle.font_count()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const font_bundle& bundle) -> std::ostream&
{
  return stream << to_string(bundle);
}

/// \} End of font bundle functions

[[nodiscard]] constexpr auto ToString(const FontHint hint) -> std::string_view
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

[[nodiscard]] inline auto ToString(const Font& font) -> std::string
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
  return stream << ToString(hint);
}

inline auto operator<<(std::ostream& stream, const Font& font) -> std::ostream&
{
  return stream << ToString(font);
}

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONT_HPP_