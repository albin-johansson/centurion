#ifndef CENTURION_MESSAGE_BOX_SOURCE
#define CENTURION_MESSAGE_BOX_SOURCE

#include "message_box.hpp"

#include "centurion_utils.hpp"
#include "colors.hpp"
#include "error.hpp"

namespace centurion {
namespace messagebox {
namespace {

/**
 * Creates and returns an <code>SDL_MessageBoxButtonData</code> object based
 * on the specified attributes.
 *
 * @param hint the button data hint that will be used.
 * @param id the ID of the button.
 * @param text the text that will be displayed on the button, the empty
 * string is used if null.
 * @since 4.0.0
 */
inline SDL_MessageBoxButtonData create_button_data(ButtonDataHint hint,
                                                   int id,
                                                   czstring text) noexcept
{
  return {static_cast<Uint32>(hint), id, text};
}

}  // namespace

CENTURION_DEF
ColorScheme::ColorScheme() noexcept
{
  set_color(ColorType::Background, color::black);
  set_color(ColorType::ButtonBorder, color::black);
  set_color(ColorType::ButtonBackground, color::black);
  set_color(ColorType::ButtonSelected, color::black);
}

CENTURION_DEF
void ColorScheme::set_color(ColorType type, const Color& color) noexcept
{
  m_scheme.colors[index(type)] = static_cast<SDL_MessageBoxColor>(color);
}

CENTURION_DEF
SDL_MessageBoxColorScheme ColorScheme::convert() const noexcept
{
  return m_scheme;
}

CENTURION_DEF
MessageBox::MessageBox() : m_config{std::make_unique<MessageBoxConfig>()}
{}

CENTURION_DEF
MessageBox::MessageBox(czstring title, czstring message) : MessageBox{}

{
  set_title(title);
  set_message(message);
}

CENTURION_DEF
MessageBox::~MessageBox() noexcept = default;

CENTURION_DEF
std::vector<SDL_MessageBoxButtonData> MessageBox::create_buttons()
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
SDL_MessageBoxData MessageBox::create_data(
    SDL_Window* window,
    const SDL_MessageBoxButtonData* data,
    const SDL_MessageBoxColorScheme* scheme) const noexcept
{
  const auto flags = static_cast<Uint32>(m_config->type) |
                     static_cast<Uint32>(m_config->buttonOrder);
  return {flags,
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
    m_buttons.emplace_back(
        create_button_data(ButtonDataHint::ReturnKey, 0, "OK"));
  }

  const auto buttons = create_buttons();

  std::optional<SDL_MessageBoxColorScheme> optScheme;
  if (m_colorScheme) {
    optScheme.emplace(m_colorScheme->convert());
  }

  const auto scheme = optScheme ? &*optScheme : nullptr;
  const auto data = create_data(window, &buttons.front(), scheme);

  int button = -1;
  if (SDL_ShowMessageBox(&data, &button) == -1) {
    throw detail::Error::from_core("Failed to show message box!");
  }

  return button;
}

CENTURION_DEF
void MessageBox::show(czstring title,
                      czstring message,
                      const MessageBoxConfig& config,
                      SDL_Window* window) noexcept
{
  const auto flags = static_cast<Uint32>(config.type) |
                     static_cast<Uint32>(config.buttonOrder);
  SDL_ShowSimpleMessageBox(flags,
                           title ? title : "Centurion message box",
                           message ? message : "N/A",
                           window);
}

CENTURION_DEF
void MessageBox::add_button(ButtonDataHint hint, int id, czstring text) noexcept
{
  m_buttons.emplace_back(create_button_data(hint, id, text));
}

CENTURION_DEF
void MessageBox::set_title(czstring title) noexcept
{
  m_title = title ? title : m_title;
}

CENTURION_DEF
void MessageBox::set_message(czstring message) noexcept
{
  m_message = message ? message : m_message;
}

CENTURION_DEF
void MessageBox::set_type(Type type) noexcept
{
  m_config->type = type;
}

CENTURION_DEF
void MessageBox::set_button_order(ButtonOrder order) noexcept
{
  m_config->buttonOrder = order;
}

CENTURION_DEF
void MessageBox::set_color_scheme(std::optional<ColorScheme> scheme) noexcept
{
  this->m_colorScheme = scheme;
}

CENTURION_DEF
MessageBox::Type MessageBox::type() const noexcept
{
  return m_config->type;
}

CENTURION_DEF
MessageBox::ButtonOrder MessageBox::button_order() const noexcept
{
  return m_config->buttonOrder;
}

CENTURION_DEF
bool operator==(ButtonDataHint lhs, SDL_MessageBoxButtonFlags rhs) noexcept
{
  return static_cast<SDL_MessageBoxButtonFlags>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_MessageBoxButtonFlags lhs, ButtonDataHint rhs) noexcept
{
  return lhs == static_cast<SDL_MessageBoxButtonFlags>(rhs);
}

CENTURION_DEF
bool operator!=(ButtonDataHint lhs, SDL_MessageBoxButtonFlags rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_MessageBoxButtonFlags lhs, ButtonDataHint rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator==(SDL_MessageBoxColorType lhs, ColorType rhs) noexcept
{
  return lhs == static_cast<SDL_MessageBoxColorType>(rhs);
}

CENTURION_DEF
bool operator==(ColorType lhs, SDL_MessageBoxColorType rhs) noexcept
{
  return static_cast<SDL_MessageBoxColorType>(lhs) == rhs;
}

CENTURION_DEF
bool operator!=(SDL_MessageBoxColorType lhs, ColorType rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(ColorType lhs, SDL_MessageBoxColorType rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace messagebox
}  // namespace centurion

#endif  // CENTURION_MESSAGE_BOX_SOURCE