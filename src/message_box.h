/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <string>
#include <vector>
#include <SDL_messagebox.h>

namespace centurion::messagebox {

enum class ButtonData {
  None = 0,
  ReturnKey = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
  EscapeKey = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
};

[[nodiscard]]
inline bool operator==(ButtonData a, SDL_MessageBoxButtonFlags b) noexcept {
  return static_cast<SDL_MessageBoxButtonFlags>(a) == b;
}

[[nodiscard]]
inline bool operator==(SDL_MessageBoxButtonFlags a, ButtonData b) noexcept {
  return a == static_cast<SDL_MessageBoxButtonFlags>(b);
}

[[nodiscard]]
inline bool operator!=(ButtonData a, SDL_MessageBoxButtonFlags b) noexcept {
  return static_cast<SDL_MessageBoxButtonFlags>(a) != b;
}

[[nodiscard]]
inline bool operator!=(SDL_MessageBoxButtonFlags a, ButtonData b) noexcept {
  return a != static_cast<SDL_MessageBoxButtonFlags>(b);
}

class Button {
 private:
  ButtonData data;
  int id;
  std::string text;

 public:
  Button(ButtonData buttonData, int id, const std::string& text);

  Button(ButtonData buttonData, int id, std::string&& text);

  ~Button();

  /*implicit*/ operator SDL_MessageBoxButtonData() const noexcept;
};

enum class ColorSchemeType {
  Background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
  ButtonBorder = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
  ButtonBackground = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
  ButtonSelected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

[[nodiscard]]
inline bool operator==(SDL_MessageBoxColorType a, ColorSchemeType b) noexcept {
  return a == static_cast<SDL_MessageBoxColorType>(b);
}

[[nodiscard]]
inline bool operator==(ColorSchemeType a, SDL_MessageBoxColorType b) noexcept {
  return static_cast<SDL_MessageBoxColorType>(a) == b;
}

[[nodiscard]]
inline bool operator!=(SDL_MessageBoxColorType a, ColorSchemeType b) noexcept {
  return a != static_cast<SDL_MessageBoxColorType>(b);
}

[[nodiscard]]
inline bool operator!=(ColorSchemeType a, SDL_MessageBoxColorType b) noexcept {
  return static_cast<SDL_MessageBoxColorType>(a) != b;
}

class ColorScheme {
 private:
  SDL_MessageBoxColorScheme scheme;

  [[nodiscard]]
  int get_index(ColorSchemeType type) const noexcept {
    return static_cast<int>(type);
  }

 public:
  ColorScheme();

  ~ColorScheme() noexcept;

  void set_color(ColorSchemeType type, SDL_MessageBoxColor color) noexcept;

  /*implicit*/ operator SDL_MessageBoxColorScheme() const noexcept;
};

/**
 * The MessageBoxID enum class mirrors the values of the SDL_MessageBoxFlags enum. It's safe to
 * statically cast values of the SDL_MessageBoxFlags to MessageBoxID values. It's also possible
 * to compare MessageBoxID and SDL_MessageBoxFlags values with the == and != operators.
 *
 * @since 3.0.0
 */
enum class MessageBoxID {
  Info = SDL_MESSAGEBOX_INFORMATION,
  Warning = SDL_MESSAGEBOX_WARNING,
  Error = SDL_MESSAGEBOX_ERROR
};

[[nodiscard]]
inline bool operator==(MessageBoxID a, SDL_MessageBoxFlags b) noexcept {
  return static_cast<SDL_MessageBoxFlags>(a) == b;
}

[[nodiscard]]
inline bool operator==(SDL_MessageBoxFlags a, MessageBoxID b) noexcept {
  return a == static_cast<SDL_MessageBoxFlags>(b);
}

[[nodiscard]]
inline bool operator!=(MessageBoxID a, SDL_MessageBoxFlags b) noexcept {
  return static_cast<SDL_MessageBoxFlags>(a) != b;
}

[[nodiscard]]
inline bool operator!=(SDL_MessageBoxFlags a, MessageBoxID b) noexcept {
  return a != static_cast<SDL_MessageBoxFlags>(b);
}

/**
 * The MessageBox class represents a modal message box that can be used display information,
 * warnings and errors.
 *
 * @since 3.0.0
 */
class MessageBox {
 private:
  ColorScheme colorScheme;
  std::vector<Button> buttons;
  std::string title = "Centurion message box";
  std::string message = "N/A";
  MessageBoxID type = MessageBoxID::Info;

  [[nodiscard]]
  std::vector<SDL_MessageBoxButtonData> create_sdl_button_data() const noexcept;

 public:
  /**
   * @since 3.0.0
   */
  MessageBox() = default;

  /**
   * @param title the title of the message box.
   * @since 3.0.0
   */
  explicit MessageBox(std::string title);

  /**
   * @param title the title of the message box.
   * @param message the message of the message box.
   * @since 3.0.0
   */
  MessageBox(std::string title, std::string message);

  virtual ~MessageBox() noexcept;

  /**
   * Displays the message box. If no buttons have been added, the message box will feature an
   * "OK" button.
   *
   * @param window a pointer to the parent window, can safely be null to indicate no parent.
   * @return the ID of the pressed button; -1 if no button was pressed.
   * @throws CenturionException if the message box cannot be displayed.
   * @since 3.0.0
   */
  int show(SDL_Window* window = nullptr);

  /**
   * Creates and displays a message box. This method provides a simpler way to create
   * message boxes, compared to creating instances of the MessageBox class.
   *
   * @param title the title of the message box window.
   * @param message the message of the message box window.
   * @param type the type of the message.
   * @param window a pointer to the parent window, can safely be null to indicate no parent.
   * @since 3.0.0
   */
  static void show(const std::string& title,
                   const std::string& message,
                   MessageBoxID type,
                   SDL_Window* window = nullptr) noexcept;

  /**
   * Adds a button to the message box.
   *
   * @param data the data of the button.
   * @param id the ID of the button.
   * @param text the text of the button.
   * @since 3.0.0
   */
  void add_button(ButtonData data, int id, std::string text) noexcept;

  /**
   * Sets the title of the message box.
   *
   * @param title the title of the message box.
   * @since 3.0.0
   */
  void set_title(const std::string& title) noexcept;

  /**
   * Sets the message of the message box.
   *
   * @param message the message of the message box.
   * @since 3.0.0
   */
  void set_message(const std::string& message) noexcept;

  /**
   * Sets what kind of message box the message box is. By default, this property is set to
   * MessageBoxID::Info.
   *
   * @param type the type of the message box.
   * @since 3.0.0
   */
  void set_type(MessageBoxID type) noexcept;

  /**
   * Returns the type of the message box.
   *
   * @return the type of the message box.
   * @since 3.0.0
   */
  [[nodiscard]]
  MessageBoxID get_type() const noexcept;

};

}
