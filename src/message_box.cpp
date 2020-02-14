#ifndef CENTURION_MESSAGE_BOX_SOURCE
#define CENTURION_MESSAGE_BOX_SOURCE

#include "message_box.h"

#include <cstdint>
#include <utility>

#include "centurion_exception.h"
#include "colors.h"
#include "error.h"

namespace centurion {
namespace messagebox {

CENTURION_DEF ButtonData::ButtonData(ButtonDataHint hint, int id,
                                     std::string text)
    : buttonDataHint{hint}, id{id}, text{std::move(text)} {}

CENTURION_DEF ButtonData::operator SDL_MessageBoxButtonData() const noexcept {
  return {static_cast<uint32_t>(buttonDataHint), id, text.c_str()};
}

CENTURION_DEF ColorScheme::ColorScheme() noexcept {
  set_color(ColorType::Background, Colors::black);
  set_color(ColorType::ButtonBorder, Colors::black);
  set_color(ColorType::ButtonBackground, Colors::black);
  set_color(ColorType::ButtonSelected, Colors::black);
}

CENTURION_DEF void ColorScheme::set_color(ColorType type,
                                          const Color& color) noexcept {
  scheme.colors[get_index(type)] = color;
}

CENTURION_DEF const SDL_MessageBoxColorScheme& ColorScheme::get() const
    noexcept {
  return scheme;
}

CENTURION_DEF ColorScheme::operator SDL_MessageBoxColorScheme() const noexcept {
  return scheme;
}

CENTURION_DEF MessageBox::MessageBox(std::string title)
    : title{std::move(title)} {}

CENTURION_DEF MessageBox::MessageBox(std::string title, std::string message)
    : title{std::move(title)}, message{std::move(message)} {}

CENTURION_DEF MessageBox::~MessageBox() noexcept = default;

CENTURION_DEF std::vector<SDL_MessageBoxButtonData>
MessageBox::create_sdl_button_data() const noexcept {
  std::vector<SDL_MessageBoxButtonData> result;
  result.reserve(buttons.size());

  for (const auto& b : buttons) {
    result.push_back(b);
  }

  return result;
}

CENTURION_DEF SDL_MessageBoxData MessageBox::create_sdl_message_box_data(
    SDL_Window* window, const SDL_MessageBoxButtonData* data,
    const SDL_MessageBoxColorScheme* scheme) const noexcept {
  return {static_cast<SDL_MessageBoxFlags>(type),
          window,
          title.c_str(),
          message.c_str(),
          static_cast<int>(buttons.size()),
          data,
          scheme};
}

CENTURION_DEF int MessageBox::show(SDL_Window* window) {
  if (buttons.empty()) {
    buttons.emplace_back(ButtonDataHint::ReturnKey, 0, "OK");
  }

  const auto sdl_buttonData = create_sdl_button_data();
  const SDL_MessageBoxButtonData* buttonDataFront = &sdl_buttonData.front();

  const SDL_MessageBoxColorScheme* sdl_colorScheme = nullptr;

#ifdef CENTURION_HAS_OPTIONAL
  if (colorScheme) {
    auto& scheme = colorScheme.value();
    sdl_colorScheme = &scheme.get();
  }
#endif

  const auto data =
      create_sdl_message_box_data(window, buttonDataFront, sdl_colorScheme);

  int button = -1;
  if (SDL_ShowMessageBox(&data, &button) < 0) {
    throw CenturionException{"Failed to show message box! " + Error::msg()};
  }

  return button;  // TODO consider returning std::optional<int> instead
}

CENTURION_DEF void MessageBox::show(const std::string& title,
                                    const std::string& message,
                                    MessageBoxID type,
                                    SDL_Window* window) noexcept {
  SDL_ShowSimpleMessageBox(static_cast<uint32_t>(type), title.c_str(),
                           message.c_str(), window);
}

CENTURION_DEF void MessageBox::add_button(ButtonDataHint hint, int id,
                                          std::string text) noexcept {
  buttons.emplace_back(hint, id, std::move(text));
}

CENTURION_DEF void MessageBox::set_title(const std::string& title) noexcept {
  this->title = title;
}

CENTURION_DEF void MessageBox::set_message(
    const std::string& message) noexcept {
  this->message = message;
}

CENTURION_DEF void MessageBox::set_type(MessageBoxID type) noexcept {
  this->type = type;
}

#ifdef CENTURION_HAS_OPTIONAL

CENTURION_DEF void MessageBox::set_color_scheme(
    std::optional<ColorScheme> scheme) noexcept {
  this->colorScheme = std::move(scheme);
}

#endif

CENTURION_DEF MessageBoxID MessageBox::get_type() const noexcept {
  return type;
}

CENTURION_DEF bool operator==(ButtonDataHint a,
                              SDL_MessageBoxButtonFlags b) noexcept {
  return static_cast<SDL_MessageBoxButtonFlags>(a) == b;
}

CENTURION_DEF bool operator==(SDL_MessageBoxButtonFlags a,
                              ButtonDataHint b) noexcept {
  return a == static_cast<SDL_MessageBoxButtonFlags>(b);
}

CENTURION_DEF bool operator!=(ButtonDataHint a,
                              SDL_MessageBoxButtonFlags b) noexcept {
  return static_cast<SDL_MessageBoxButtonFlags>(a) != b;
}

CENTURION_DEF bool operator!=(SDL_MessageBoxButtonFlags a,
                              ButtonDataHint b) noexcept {
  return a != static_cast<SDL_MessageBoxButtonFlags>(b);
}

CENTURION_DEF bool operator==(SDL_MessageBoxColorType a, ColorType b) noexcept {
  return a == static_cast<SDL_MessageBoxColorType>(b);
}

CENTURION_DEF bool operator==(ColorType a, SDL_MessageBoxColorType b) noexcept {
  return static_cast<SDL_MessageBoxColorType>(a) == b;
}

CENTURION_DEF bool operator!=(SDL_MessageBoxColorType a, ColorType b) noexcept {
  return a != static_cast<SDL_MessageBoxColorType>(b);
}

CENTURION_DEF bool operator!=(ColorType a, SDL_MessageBoxColorType b) noexcept {
  return static_cast<SDL_MessageBoxColorType>(a) != b;
}

CENTURION_DEF bool operator==(MessageBoxID a, SDL_MessageBoxFlags b) noexcept {
  return static_cast<SDL_MessageBoxFlags>(a) == b;
}

CENTURION_DEF bool operator==(SDL_MessageBoxFlags a, MessageBoxID b) noexcept {
  return a == static_cast<SDL_MessageBoxFlags>(b);
}

CENTURION_DEF bool operator!=(MessageBoxID a, SDL_MessageBoxFlags b) noexcept {
  return static_cast<SDL_MessageBoxFlags>(a) != b;
}

CENTURION_DEF bool operator!=(SDL_MessageBoxFlags a, MessageBoxID b) noexcept {
  return a != static_cast<SDL_MessageBoxFlags>(b);
}

}  // namespace messagebox
}  // namespace centurion

#endif  // CENTURION_MESSAGE_BOX_SOURCE