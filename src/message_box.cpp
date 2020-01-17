#include "message_box.h"
#include <cstdint>
#include <SDL.h>

namespace centurion::messagebox {

/***************************************
 * MESSAGE BOX BUTTON ******************
 ***************************************/

Button::Button(ButtonData buttonData, int id, const std::string& text)
    : data{buttonData}, id{id}, text{text} {}

Button::Button(ButtonData buttonData, int id, std::string&& text)
    : data{buttonData}, id{id}, text{std::move(text)} {}

Button::~Button() = default;

Button::operator SDL_MessageBoxButtonData() const noexcept {
  return {static_cast<uint32_t>(data), id, text.c_str()};
}

/***************************************
 * COLOR SCHEME ************************
 ***************************************/

ColorScheme::ColorScheme() {
  set_color(ColorSchemeType::Background, {0, 0, 0});
  set_color(ColorSchemeType::ButtonBorder, {0, 0, 0});
  set_color(ColorSchemeType::ButtonBackground, {0, 0, 0});
  set_color(ColorSchemeType::ButtonSelected, {0, 0, 0});
}

ColorScheme::~ColorScheme() noexcept = default;

void ColorScheme::set_color(ColorSchemeType type, SDL_MessageBoxColor color) noexcept {
  scheme.colors[get_index(type)] = color;
}

ColorScheme::operator SDL_MessageBoxColorScheme() const noexcept {
  return scheme;
}

/***************************************
 * MESSAGE BOX *************************
 ***************************************/

MessageBox::MessageBox() {
  buttonData.reserve(3);
  buttonData.emplace_back(ButtonData::None, 0, "No");
  buttonData.emplace_back(ButtonData::ReturnKey, 1, "Yes");
  buttonData.emplace_back(ButtonData::EscapeKey, 2, "Cancel");
}

MessageBox::~MessageBox() noexcept = default;

void MessageBox::show() {
  const SDL_MessageBoxColorScheme s = colorScheme;

  auto* d = new SDL_MessageBoxButtonData[buttonData.size()];
  for (auto i = 0; i < buttonData.size(); i++) {
    d[i] = buttonData[i];
  }

  data = {
      SDL_MESSAGEBOX_INFORMATION,
      nullptr,
      "Centurion message box",
      "select a button",
      static_cast<int>(buttonData.size()),
      d,
      &s
  };

  int button;
  if (SDL_ShowMessageBox(&data, &button) < 0) {
    SDL_Log("error displaying message box");
  }
  if (button == -1) {
    SDL_Log("no selection");
  } else {
    SDL_Log("selection was %i", button);
  }

  delete[] d;
}

}
