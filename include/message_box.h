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

#ifndef CENTURION_MESSAGE_BOX_HEADER
#define CENTURION_MESSAGE_BOX_HEADER

#include <SDL.h>

#include <vector>

#include "centurion_api.h"
#include "centurion_utils.h"
#include "color.h"

namespace centurion {
namespace messagebox {

/**
 * The ButtonDataHint enum class mirrors the SDL_MessageBoxButtonFlags enum.
 *
 * @since 3.0.0
 */
enum class ButtonDataHint {
  None = 0,
  ReturnKey = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
  EscapeKey = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
};

/**
 * Indicates whether or not the flags represent the same value.
 *
 * @param lhs the lhs Centurion message box button data hint.
 * @param rhs the rhs SDL message box button data flags.
 * @return true if the values represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(ButtonDataHint lhs,
                              SDL_MessageBoxButtonFlags rhs) noexcept;

/**
 * Indicates whether or not the flags represent the same value.
 *
 * @param lhs the lhs SDL message box button data flags.
 * @param rhs the rhs Centurion message box button data hint.
 * @return true if the values represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_MessageBoxButtonFlags lhs,
                              ButtonDataHint rhs) noexcept;

/**
 * Indicates whether or not the flags don't represent the same value.
 *
 * @param lhs the lhs Centurion message box button data hint.
 * @param rhs the rhs SDL message box button data flags.
 * @return true if the values don't represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(ButtonDataHint lhs,
                              SDL_MessageBoxButtonFlags rhs) noexcept;

/**
 * Indicates whether or not the flags don't represent the same value.
 *
 * @param lhs the lhs SDL message box button data flags.
 * @param rhs the rhs Centurion message box button data hint.
 * @return true if the values don't represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_MessageBoxButtonFlags lhs,
                              ButtonDataHint rhs) noexcept;

/**
 * The ColorType enum class mirrors the SDL_MessageBoxColorType enum.
 *
 * @since 3.0.0
 */
enum class ColorType {
  Background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
  ButtonBorder = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
  ButtonBackground = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
  ButtonSelected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

/**
 * Indicates whether or not the message box color types represent the same
 * value.
 *
 * @param lhs the lhs SDL message box color type.
 * @param rhs the rhs Centurion message box color type.
 * @return true if the color types represent the same value; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator==(SDL_MessageBoxColorType lhs, ColorType rhs) noexcept;

/**
 * Indicates whether or not the message box color types represent the same
 * value.
 *
 * @param lhs the lhs Centurion message box color type.
 * @param rhs the rhs SDL message box color type.
 * @return true if the color types represent the same value; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator==(ColorType lhs, SDL_MessageBoxColorType rhs) noexcept;

/**
 * Indicates whether or not the message box color types don't represent the same
 * value.
 *
 * @param lhs the lhs SDL message box color type.
 * @param rhs the rhs Centurion message box color type.
 * @return true if the color types don't represent the same value; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator!=(SDL_MessageBoxColorType lhs, ColorType rhs) noexcept;

/**
 * Indicates whether or not the message box color types don't represent the same
 * value.
 *
 * @param lhs the lhs Centurion message box color type.
 * @param rhs the rhs SDL message box color type.
 * @return true if the color types don't represent the same value; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator!=(ColorType lhs, SDL_MessageBoxColorType rhs) noexcept;

/**
 * The ColorScheme class is a simple wrapper around an SDL_MessageBoxColorScheme
 * struct.
 *
 * @since 3.0.0
 */
class ColorScheme final {
 public:
  /**
   * @since 3.0.0
   */
  CENTURION_API
  ColorScheme() noexcept;

  /**
   * Sets the color of a color scheme component.
   *
   * @param type the color scheme component that will be set.
   * @param color the color that will be used.
   * @since 3.0.0
   */
  CENTURION_API
  void set_color(ColorType type, const Color& color) noexcept;

  /**
   * Creates and returns the SDL_MessageBoxColorScheme equivalent of the color
   * scheme
   *
   * @return a SDL_MessageBoxColorScheme that is equivalent to the color
   * scheme.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API SDL_MessageBoxColorScheme convert() const noexcept;

 private:
  SDL_MessageBoxColorScheme m_scheme{};

  /**
   * Returns the array index associated with the supplied color scheme type.
   *
   * @param type color scheme type to obtain the index for.
   * @return the array index associated with the supplied color scheme type.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int index(ColorType type) const noexcept { return static_cast<int>(type); }
};

struct MessageBoxConfig;

/**
 * The MessageBox class represents a modal message box that can be used display
 * information, warnings and errors.
 *
 * @since 3.0.0
 */
class MessageBox final {
 public:
  /**
   * The ButtonOrder enum class provides hints for how the buttons in a message
   * box should be aligned, either left-to-right or right-to-left.
   *
   * @since 4.0.0
   */
  enum class ButtonOrder { LeftToRight, RightToLeft };

  /**
   * The MessageBoxType enum class serves as a hint of the purpose of a message
   * box. Message boxes can indicate errors, warnings and general information.
   *
   * @since 4.0.0
   */
  enum class Type {
    Error = SDL_MESSAGEBOX_ERROR,
    Warning = SDL_MESSAGEBOX_WARNING,
    Information = SDL_MESSAGEBOX_INFORMATION
  };

  /**
   * @since 3.0.0
   */
  CENTURION_API MessageBox();

  /**
   * @param title the title of the message box, can be null. "Centurion message
   * box" is used if the supplied string is null.
   * @param message the message of the message box, can be null. "N/A" is
   * used if the supplied string is null.
   * @since 3.0.0
   */
  CENTURION_API explicit MessageBox(CZString title, CZString message = nullptr);

  CENTURION_API ~MessageBox() noexcept;

  /**
   * Displays the message box. If no buttons have been added, the message box
   * will feature an "OK" button. This method will block the invoking thread
   * until the user closes the message box.
   *
   * @param window a pointer to the parent window, can safely be null to
   * indicate no parent.
   * @return the ID of the pressed button; -1 if no button was pressed.
   * @throws CenturionException if the message box cannot be displayed.
   * @since 3.0.0
   */
  CENTURION_API int show(SDL_Window* window = nullptr);

  /**
   * Creates and displays a message box. This method provides a simpler way to
   * create message boxes, compared to creating instances of the MessageBox
   * class. This method will block the invoking thread until the user closes
   * the message box.
   *
   * @param title the title of the message box window, can be null. "Centurion
   * message box" is used if the supplied string is null.
   * @param message the message of the message box window, can be null. "N/A"
   * is used if the supplied string is null.
   * @param config the configuration hints of the message box.
   * @param window a pointer to the parent window, can safely be null to
   * indicate no parent.
   * @since 3.0.0
   */
  CENTURION_API static void show(CZString title,
                                 CZString message,
                                 const MessageBoxConfig& config,
                                 SDL_Window* window = nullptr) noexcept;

  /**
   * Adds a button to the message box. If you don't explicitly add a
   * button, there will be an "OK" button added automatically.
   *
   * @param hint the data hint of the button.
   * @param id the ID of the button.
   * @param text the text of the button, if null then the empty string is used.
   * @since 3.0.0
   */
  CENTURION_API void add_button(ButtonDataHint hint,
                                int id,
                                CZString text) noexcept;

  /**
   * Sets the title of the message box. This method has no effect if the
   * supplied string is null.
   *
   * @param title the title of the message box, can be null.
   * @since 3.0.0
   */
  CENTURION_API void set_title(CZString title) noexcept;

  /**
   * Sets the message of the message box. This method has no effect if the
   * supplied string is null.
   *
   * @param message the message of the message box, can be null.
   * @since 3.0.0
   */
  CENTURION_API void set_message(CZString message) noexcept;

  /**
   * Sets the type of message that the message box represents. By default,
   * this property is set to <code>Information</code>.
   *
   * @param type the type of the message box.
   * @since 3.0.0
   */
  CENTURION_API void set_type(Type type) noexcept;

  /**
   * Sets the button order of the buttons in the message box. By default,
   * this property is set to <code>LeftToRight</code>.
   *
   * @param order the button order that will be used.
   * @since 4.0.0
   */
  CENTURION_API void set_button_order(ButtonOrder order) noexcept;

  /**
   * Sets the color scheme that will be used by the message box. Color schemes
   * aren't supported on all platforms, so the default value is nothing for
   * the color scheme.
   *
   * @param scheme the color scheme that will be used; nothing indicates
   * that the system defaults should be used.
   * @since 3.0.0
   */
  CENTURION_API void set_color_scheme(Optional<ColorScheme> scheme) noexcept;

  /**
   * Returns the title of the message box. The default title is "Centurion
   * message box".
   *
   * @return the title of the message box.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CZString title() const noexcept { return m_title; }

  /**
   * Returns the message of the message box. The default message is "N/A".
   *
   * @return the message of the message box.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CZString message() const noexcept { return m_message; }

  /**
   * Returns the color scheme that is used by the message box. Color schemes
   * aren't supported on all platforms, so the default value is nothing for
   * the color scheme.
   *
   * @return the color scheme that is used by the message box; nothing if
   * there is none.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  Optional<ColorScheme> color_scheme() const noexcept { return m_colorScheme; }

  /**
   * Returns the type of the message box. By default, this property is set to
   * <code>Information</code>.
   *
   * @return the type of the message box.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Type type() const noexcept;

  /**
   * Returns the button order that is used by the buttons in the message box. By
   * default, this property is set to <code>LeftToRight</code>.
   *
   * @return the button order that is used by the buttons in the message box.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API ButtonOrder button_order() const noexcept;

 private:
  Optional<ColorScheme> m_colorScheme = nothing;
  std::vector<SDL_MessageBoxButtonData> m_buttons;
  CZString m_title = "Centurion message box";
  CZString m_message = "N/A";
  UniquePtr<MessageBoxConfig> m_config;

  /**
   * Creates and returns a vector of SDL_MessageBoxButtonData instances.
   *
   * @return a vector of SDL_MessageBoxButtonData instances.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::vector<SDL_MessageBoxButtonData> create_buttons() const noexcept;

  /**
   * Creates and returns an SDL_MessageBoxData based on the MessageBox.
   *
   * @param window the parent window, can safely be null.
   * @param data a pointer to the first element in the array of buttons.
   * @param scheme a pointer to the color scheme that will be used, set to null
   * by default.
   * @return an SDL_MessageBoxData based on the MessageBox.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  SDL_MessageBoxData create_data(
      SDL_Window* window,
      const SDL_MessageBoxButtonData* data,
      const SDL_MessageBoxColorScheme* scheme = nullptr) const noexcept;
};

/**
 * The MessageBoxConfig enum class represents as a configuration hint for
 * message boxes and specifies the desired type and button order of a
 * message box.
 *
 * @since 4.0.0
 */
struct MessageBoxConfig {
  MessageBox::Type type = MessageBox::Type::Information;
  MessageBox::ButtonOrder buttonOrder = MessageBox::ButtonOrder::LeftToRight;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<ColorScheme>::value, "ColorScheme isn't final!");
#endif

static_assert(std::is_nothrow_default_constructible<ColorScheme>::value,
              "ColorScheme isn't nothrow default constructible!");

static_assert(std::is_nothrow_destructible<ColorScheme>::value,
              "ColorScheme isn't nothrow destructible!");

}  // namespace messagebox
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "message_box.cpp"
#endif

#endif  // CENTURION_MESSAGE_BOX_HEADER
