#pragma once
#include <SDL_ttf.h>
#include <memory>
#include <string>

namespace centurion {
namespace visuals {

/**
\brief The Font class serves as a representation of a True Type font.
*/
class Font {
 private:
  TTF_Font* font;
  int styleMask;
  int size;

  bool IsValidStyle(int style);

  void RemoveStyle(int mask);

  void ApplyStyle(int mask);

 public:
  /**
  \param path - the path of the True Type Font (.ttf) file.
  \param size - the point size of the font.
  */
  Font(const std::string& path, int size);

  ~Font();

  /**
  \brief Creates and returns a heap allocated Font instance.
  \param path - the path of the True Type Font (.ttf) file.
  \param size - the point size of the font.
  */
  static std::shared_ptr<centurion::visuals::Font> Create(
      const std::string& path, int size);

  /**
  \brief Resets the style of this font, so that the style is equivalent to the
  style used when this font was first created.
  */
  void ResetStyle();

  /**
  \brief Sets the styling of this font. The possible values are
  TTF_STYLE_NORMAL, TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and
  TTF_STYLE_STRIKETHROUGH. These values may be OR'd together.
  \param style - the mask specifying the desired styling of this font.
  */
  void SetStyle(int style);

  /**
  \brief Assigns whether or not this font should be bold.
  \param isBold - true if this font should be bold, false otherwise.
  */
  void SetBold(bool isBold);

  /**
  \brief Assigns whether or not this font should be italic.
  \param isItalic - true if this font should be italic, false otherwise.
  */
  void SetItalic(bool isItalic);

  /**
  \brief Assigns whether or not this font should be underlined.
  \param isUnderlined - true if this font should be underlined, false otherwise.
  */
  void SetUnderlined(bool isUnderlined);

  /**
  \brief Assigns whether or not this font should use a strikethrough.
  \param isStrikethrough - true if this font should be a strikethrough font,
  false otherwise.
  */
  void SetStrikethrough(bool isStrikethrough);

  /**
  \brief Assigns whether or not this is an outlined font.
  \param isOutlined - should be true if the font should only be outlined.
  */
  void SetOutlined(bool isOutlined);

  /**
  \brief Returns a raw pointer to the SDL_font which this Font object
  represents.
  DO NOT use the returned pointer to call TTF_CloseFont().
  */
  inline TTF_Font* GetSDLVersion() { return font; }

  /**
  \brief Returns the point size of the font that this Font instacne represents.
  */
  inline int GetSize() const { return size; }

  /**
  \brief Returns true if this font is bold, false otherwise.
  */
  bool IsBold() const;

  /**
  \brief Returns true if this font is italic, false otherwise.
  */
  bool IsItalic() const;

  /**
  \brief Returns true if this font is underlined, false otherwise.
  */
  bool IsUnderlined() const;

  /**
  \brief Returns true if this font uses a strikethrough, false otherwise.
  */
  bool IsStrikethrough() const;

  /**
  \brief Calculates and returns the width of the supplied string, if it was
  rendered in this font.
  \param str - the string that will be measured.
  */
  int GetStringWidth(const std::string& str) const;

  /**
  \brief Calculates and returns the height of the supplied string, if it was
  rendered in this font.
  \param str - the string that will be measured.
  */
  int GetStringHeight(const std::string& str) const;
};

typedef std::shared_ptr<centurion::visuals::Font> Font_sptr;
typedef std::unique_ptr<centurion::visuals::Font> Font_uptr;
typedef std::weak_ptr<centurion::visuals::Font> Font_wptr;

}  // namespace visuals
}  // namespace centurion