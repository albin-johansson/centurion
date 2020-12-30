#include "message_box.hpp"

#include <algorithm>  // max, any_of
#include <utility>    // move

#include "detail/stack_resource.hpp"
#include "exception.hpp"

namespace cen {

message_box::message_box(std::string title, std::string message)
    : m_title{std::move(title)}
    , m_message{std::move(message)}
{}

void message_box::show(SDL_Window* parent,
                       const std::string& title,
                       const std::string& message,
                       type type,
                       button_order buttonOrder)
{
  if (const auto result = SDL_ShowSimpleMessageBox(to_flags(type, buttonOrder),
                                                   title.c_str(),
                                                   message.c_str(),
                                                   parent);
      result == -1) {
    throw sdl_error{"Failed to show message box"};
  }
}

auto message_box::show(SDL_Window* parent) -> std::optional<button_id>
{
  SDL_MessageBoxData data{};

  data.window = parent;
  data.title = m_title.c_str();
  data.message = m_message.c_str();
  data.flags = to_flags(m_type, m_buttonOrder);
  data.colorScheme = m_colorScheme ? m_colorScheme->get() : nullptr;

  // Realistically 1-3 buttons, stack buffer for 8 buttons, just in case.
  detail::stack_resource<8 * sizeof(SDL_MessageBoxButtonData)> resource;
  std::pmr::vector<SDL_MessageBoxButtonData> buttonData{resource.get()};

  if (m_buttons.empty()) {
    add_button(0, "OK", default_button::return_key);
  }

  for (const auto& button : m_buttons) {
    buttonData.emplace_back(button.convert());
  }

  data.buttons = buttonData.data();
  data.numbuttons = static_cast<int>(buttonData.size());

  button_id button{-1};
  if (SDL_ShowMessageBox(&data, &button) == -1) {
    throw sdl_error{"Failed to show message box"};
  }

  if (button != -1) {
    return button;
  } else {
    return std::nullopt;
  }
}

void message_box::show(const std::string& title,
                       const std::string& message,
                       type type,
                       button_order buttonOrder)
{
  show(nullptr, title, message, type, buttonOrder);
}

auto message_box::show() -> std::optional<button_id>
{
  return show(nullptr);
}

void message_box::add_button(button_id id,
                             std::string text,
                             default_button defaultButton)
{
  m_buttons.emplace_back(id, std::move(text), defaultButton);
}

void message_box::set_color_scheme(const color_scheme& colorScheme) noexcept
{
  m_colorScheme = colorScheme;
}

void message_box::set_title(std::string title)
{
  m_title = std::move(title);
}

void message_box::set_message(std::string message)
{
  m_message = std::move(message);
}

void message_box::set_type(type type) noexcept
{
  m_type = type;
}

void message_box::set_button_order(button_order order) noexcept
{
  m_buttonOrder = order;
}

auto message_box::has_button(button_id id) const noexcept -> bool
{
  return std::any_of(m_buttons.begin(),
                     m_buttons.end(),
                     [id](const button& button) noexcept {
                       return button.id() == id;
                     });
}

auto message_box::get_title() const -> std::string_view
{
  return m_title;
}

auto message_box::get_message() const -> std::string_view
{
  return m_message;
}

auto message_box::get_type() const noexcept -> type
{
  return m_type;
}

auto message_box::get_button_order() const noexcept -> button_order
{
  return m_buttonOrder;
}

}  // namespace cen
