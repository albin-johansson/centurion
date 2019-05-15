#pragma once
#include <SDL_ttf.h>
#include <memory>
#include <string>

namespace centurion {
namespace visuals {

class Font;
using Font_sptr = std::shared_ptr<Font>;
using Font_uptr = std::unique_ptr<Font>;
using Font_wptr = std::weak_ptr<Font>;

/**
\brief The Font class serves as a representation of a True Type font.
\since 1.0.0
*/
class Font final {
 private:
  TTF_Font* font = nullptr;
  int styleMask;
  int size;

  bool IsValidStyle(int style) noexcept;

  void RemoveStyle(int mask) noexcept;

  void ApplyStyle(int mask) noexcept;

 public:
  /**
  \param path - the path of the True Type Font (.ttf) file.
  \param size - the point size of the font.
  \since 1.0.0
  */
  Font(const std::string& path, int size);

  ~Font();

  /**
  \brief Resets the style of this font, so that the style is equivalent to the
  style used when this font was first created.
  \since 1.1.0
  */
  void ResetStyle() noexcept;

  /**
  \brief Sets the styling of this font. The possible values are
  TTF_STYLE_NORMAL, TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and
  TTF_STYLE_STRIKETHROUGH. These values may be OR'd together.
  \param style - the mask specifying the desired styling of this font.
  \since 1.0.0
  */
  void SetStyle(int style) noexcept;

  /**
  \brief Assigns whether or not this font should be bold.
  \param isBold - true if this font should be bold, false otherwise.
  \since 1.1.0
  */
  void SetBold(bool isBold) noexcept;

  /**
  \brief Assigns whether or not this font should be italic.
  \param isItalic - true if this font should be italic, false otherwise.
  \since 1.1.0
  */
  void SetItalic(bool isItalic) noexcept;

  /**
  \brief Assigns whether or not this font should be underlined.
  \param isUnderlined - true if this font should be underlined, false otherwise.
  \since 1.1.0
  */
  void SetUnderlined(bool isUnderlined) noexcept;

  /**
  \brief Assigns whether or not this font should use a strikethrough.
  \param isStrikethrough - true if this font should be a strikethrough font,
  false otherwise.
  \since 1.1.0
  */
  void SetStrikethrough(bool isStrikethrough) noexcept;

  /**
  \brief Assigns whether or not this is an outlined font.
  \param isOutlined - should be true if the font should only be outlined.
  \since 1.0.0
  */
  void SetOutlined(bool isOutlined) noexcept;

  /**
  \brief Returns a raw pointer to the SDL_font which this Font object
  represents.
  DO NOT use the returned pointer to call TTF_CloseFont().
  \since 1.0.0
  */
  inline TTF_Font* GetSDLVersion() noexcept { return font; }

  /**
  \brief Returns the point size of the font that this Font instance represents.
  \since 1.0.0
  */
  inline int GetSize() const noexcept { return size; }

  /**
  \brief Returns the style mask for this font.
  \since 2.0.0
  */
  inline int GetStyleMask() const noexcept { return styleMask; }

  /**
  \brief Returns true if this font is bold, false otherwise.
  \since 1.1.0
  */
  inline bool IsBold() const noexcept { return styleMask & TTF_STYLE_BOLD; }

  /**
  \brief Returns true if this font is italic, false otherwise.
  \since 1.1.0
  */
  inline bool IsItalic() const noexcept { return styleMask & TTF_STYLE_ITALIC; }

  /**
  \brief Returns true if this font is underlined, false otherwise.
  \since 1.1.0
  */
  inline bool IsUnderlined() const noexcept {
    return styleMask & TTF_STYLE_UNDERLINE;
  }

  /**
  \brief Returns true if this font uses a strikethrough, false otherwise.
  \since 1.1.0
  */
  inline bool IsStrikethrough() const noexcept {
    return styleMask & TTF_STYLE_STRIKETHROUGH;
  }

  /**
  \brief Returns true if this font is an outlined font, returns false otherwise.
  \since 2.0.0
  */
  inline bool IsOutlined() const noexcept {
    return TTF_GetFontOutline(font) > 0;
  }

  /**
  \brief Returns true if this font is a fixed width font, returns false
  otherwise.
  \since 2.0.0
  */
  inline bool IsFixedWidth() const noexcept {
    return TTF_FontFaceIsFixedWidth(font);
  }

  /**
  \brief Calculates and returns the width of the supplied string, if it was
  rendered in this font.
  \param str - the string that will be measured.
  \since 1.0.0
  */
  int GetStringWidth(const std::string& str) const noexcept;

  /**
  \brief Calculates and returns the height of the supplied string, if it was
  rendered in this font.
  \param str - the string that will be measured.
  \since 1.0.0
  */
  int GetStringHeight(const std::string& str) const noexcept;

  /**
  \brief Creates and returns a shared pointer that points to a Font instance.
  \param path - the path of the True Type Font (.ttf) file.
  \param size - the point size of the font.
  \since 1.1.0
  */
  static Font_sptr CreateShared(const std::string& path, int size);

  /**
  \brief Creates and returns an unique pointer that points to a Font instance.
  \param path - the path of the True Type Font (.ttf) file.
  \param size - the point size of the font.
  \since 1.1.0
  */
  static Font_uptr CreateUnique(const std::string& path, int size);
};

}  // namespace visuals
}  // namespace centurion