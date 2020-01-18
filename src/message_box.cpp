#include "message_box.h"
#include <cstdint>
#include <SDL.h>
#include "centurion_exception.h"

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

MessageBox::MessageBox(std::string title)
    : title{std::move(title)} {}

MessageBox::MessageBox(std::string title, std::string message)
    : title{std::move(title)},
      message{std::move(message)} {}

MessageBox::~MessageBox() noexcept = default;

std::vector<SDL_MessageBoxButtonData> MessageBox::create_sdl_button_data() const noexcept {
  std::vector<SDL_MessageBoxButtonData> result;
  result.reserve(buttons.size());

  for (const auto& b : buttons) {
    result.push_back(b);
  }

  return result;
}

int MessageBox::show(SDL_Window* window) {
  if (buttons.empty()) {
    buttons.emplace_back(ButtonData::ReturnKey, 0, "OK");
  }

  const auto sdl_buttonData = create_sdl_button_data();
  const SDL_MessageBoxColorScheme sdl_colorScheme = colorScheme;

  const SDL_MessageBoxData data{
      static_cast<SDL_MessageBoxFlags>(type),
      window,
      title.c_str(),
      message.c_str(),
      static_cast<int>(buttons.size()),
      &sdl_buttonData.front(),
      &sdl_colorScheme
  };

  int button = -1;
  if (SDL_ShowMessageBox(&data, &button) < 0) {
    throw CenturionException("Failed to show message box! Error: " + std::string{SDL_GetError()});
  }

  return button;
}

void MessageBox::show(const std::string& title,
                      const std::string& message,
                      MessageBoxID type,
                      SDL_Window* window) noexcept {
  SDL_ShowSimpleMessageBox(static_cast<uint32_t>(type), title.c_str(), message.c_str(), window);
}

void MessageBox::add_button(ButtonData data, int id, std::string text) noexcept {
  buttons.emplace_back(data, id, std::move(text));
}

void MessageBox::set_title(const std::string& title) noexcept {
  this->title = title;
}

void MessageBox::set_message(const std::string& message) noexcept {
  this->message = message;
}

void MessageBox::set_type(MessageBoxID type) noexcept {
  this->type = type;
}

MessageBoxID MessageBox::get_type() const noexcept {
  return type;
}

}
