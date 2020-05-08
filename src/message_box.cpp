#ifndef CENTURION_MESSAGE_BOX_SOURCE
#define CENTURION_MESSAGE_BOX_SOURCE

#include "message_box.h"

#include <utility>

#include "centurion_exception.h"
#include "colors.h"
#include "error.h"

namespace centurion {
namespace messagebox {

CENTURION_DEF
ButtonData::ButtonData(ButtonDataHint hint, int id, std::string text)
    : m_buttonDataHint{hint}, m_id{id}, m_text{std::move(text)}
{}

CENTURION_DEF
ButtonData::operator SDL_MessageBoxButtonData() const noexcept
{
  return {static_cast<Uint32>(m_buttonDataHint), m_id, m_text.c_str()};
}

CENTURION_DEF
ColorScheme::ColorScheme() noexcept
{
  set_color(ColorType::Background, black);
  set_color(ColorType::ButtonBorder, black);
  set_color(ColorType::ButtonBackground, black);
  set_color(ColorType::ButtonSelected, black);
}

CENTURION_DEF
void ColorScheme::set_color(ColorType type, const Color& color) noexcept
{
  m_scheme.colors[index(type)] = color;
}

CENTURION_DEF
const SDL_MessageBoxColorScheme& ColorScheme::get() const noexcept
{
  return m_scheme;
}

CENTURION_DEF
ColorScheme::operator SDL_MessageBoxColorScheme() const noexcept
{
  return m_scheme;
}

CENTURION_DEF
MessageBox::MessageBox(const char* title)
{
  if (title) {
    this->m_title = title;
  }
}

CENTURION_DEF
MessageBox::MessageBox(const char* title, const char* message)
    : m_title{title}, m_message{message}
{
  if (title) {
    this->m_title = title;
  }

  if (message) {
    this->m_message = message;
  }
}

CENTURION_DEF
MessageBox::~MessageBox() noexcept = default;

CENTURION_DEF
std::vector<SDL_MessageBoxButtonData> MessageBox::create_sdl_button_data()
    const noexcept
{
  std::vector<SDL_MessageBoxButtonData> result;
  result.reserve(m_buttons.size());

  for (const auto& b : m_buttons) {
    result.push_back(b);
  }

  return result;
}

CENTURION_DEF
SDL_MessageBoxData MessageBox::create_sdl_message_box_data(
    SDL_Window* window,
    const SDL_MessageBoxButtonData* data,
    const SDL_MessageBoxColorScheme* scheme) const noexcept
{
  return {static_cast<SDL_MessageBoxFlags>(m_type),
          window,
          m_title,
          m_message,
          static_cast<int>(m_buttons.size()),
          data,
          scheme};
}

CENTURION_DEF
int MessageBox::show(SDL_Window* window)
{
  if (m_buttons.empty()) {
    m_buttons.emplace_back(ButtonDataHint::ReturnKey, 0, "OK");
  }

  const auto sdl_buttonData = create_sdl_button_data();
  const SDL_MessageBoxButtonData* buttonDataFront = &sdl_buttonData.front();

  const auto data = create_sdl_message_box_data(
      window, buttonDataFront, m_colorScheme ? &m_colorScheme->get() : nullptr);

  int button = -1;
  if (SDL_ShowMessageBox(&data, &button) < 0) {
    throw CenturionException{"Failed to show message box! " + Error::msg()};
  }

  return button;
}

CENTURION_DEF
void MessageBox::show(const char* title,
                      const char* message,
                      MessageBoxID type,
                      SDL_Window* window) noexcept
{
  SDL_ShowSimpleMessageBox(static_cast<Uint32>(type),
                           title ? title : "Centurion message box",
                           message ? message : "N/A",
                           window);
}

CENTURION_DEF
void MessageBox::add_button(ButtonDataHint hint,
                            int id,
                            std::string text) noexcept
{
  m_buttons.emplace_back(hint, id, std::move(text));
}

CENTURION_DEF
void MessageBox::set_title(const char* title) noexcept
{
  if (title) {
    this->m_title = title;
  }
}

CENTURION_DEF
void MessageBox::set_message(const char* message) noexcept
{
  if (message) {
    this->m_message = message;
  }
}

CENTURION_DEF
void MessageBox::set_type(MessageBoxID type) noexcept
{
  this->m_type = type;
}

CENTURION_DEF
void MessageBox::set_color_scheme(Optional<ColorScheme> scheme) noexcept
{
  this->m_colorScheme = scheme;
}

CENTURION_DEF
MessageBoxID MessageBox::type() const noexcept
{
  return m_type;
}

CENTURION_DEF
bool operator==(ButtonDataHint a, SDL_MessageBoxButtonFlags b) noexcept
{
  return static_cast<SDL_MessageBoxButtonFlags>(a) == b;
}

CENTURION_DEF
bool operator==(SDL_MessageBoxButtonFlags a, ButtonDataHint b) noexcept
{
  return a == static_cast<SDL_MessageBoxButtonFlags>(b);
}

CENTURION_DEF
bool operator!=(ButtonDataHint a, SDL_MessageBoxButtonFlags b) noexcept
{
  return static_cast<SDL_MessageBoxButtonFlags>(a) != b;
}

CENTURION_DEF
bool operator!=(SDL_MessageBoxButtonFlags a, ButtonDataHint b) noexcept
{
  return a != static_cast<SDL_MessageBoxButtonFlags>(b);
}

CENTURION_DEF
bool operator==(SDL_MessageBoxColorType a, ColorType b) noexcept
{
  return a == static_cast<SDL_MessageBoxColorType>(b);
}

CENTURION_DEF
bool operator==(ColorType a, SDL_MessageBoxColorType b) noexcept
{
  return static_cast<SDL_MessageBoxColorType>(a) == b;
}

CENTURION_DEF
bool operator!=(SDL_MessageBoxColorType a, ColorType b) noexcept
{
  return a != static_cast<SDL_MessageBoxColorType>(b);
}

CENTURION_DEF
bool operator!=(ColorType a, SDL_MessageBoxColorType b) noexcept
{
  return static_cast<SDL_MessageBoxColorType>(a) != b;
}

CENTURION_DEF
bool operator==(MessageBoxID a, SDL_MessageBoxFlags b) noexcept
{
  return static_cast<SDL_MessageBoxFlags>(a) == b;
}

CENTURION_DEF
bool operator==(SDL_MessageBoxFlags a, MessageBoxID b) noexcept
{
  return a == static_cast<SDL_MessageBoxFlags>(b);
}

CENTURION_DEF
bool operator!=(MessageBoxID a, SDL_MessageBoxFlags b) noexcept
{
  return static_cast<SDL_MessageBoxFlags>(a) != b;
}

CENTURION_DEF
bool operator!=(SDL_MessageBoxFlags a, MessageBoxID b) noexcept
{
  return a != static_cast<SDL_MessageBoxFlags>(b);
}

}  // namespace messagebox
}  // namespace centurion

#endif  // CENTURION_MESSAGE_BOX_SOURCE