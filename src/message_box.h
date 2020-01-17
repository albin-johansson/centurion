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

  operator SDL_MessageBoxColorScheme() const noexcept;
};

class MessageBox {
 private:
  SDL_MessageBoxData data = {};
  ColorScheme colorScheme;
  std::vector<Button> buttonData;

 public:
  MessageBox();

  virtual ~MessageBox() noexcept;

  void show();

};

//typedef struct
//{
//  Uint32 flags;                       /**< ::SDL_MessageBoxFlags */
//  SDL_Window *window;                 /**< Parent window, can be NULL */
//  const char *title;                  /**< UTF-8 title */
//  const char *message;                /**< UTF-8 message text */
//
//  int numbuttons;
//  const SDL_MessageBoxButtonData *buttons;
//
//  const SDL_MessageBoxColorScheme *colorScheme;   /**< ::SDL_MessageBoxColorScheme, can be NULL to use system settings */
//} SDL_MessageBoxData;

}
