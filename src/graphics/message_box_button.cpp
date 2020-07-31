#include <utility>  // move

#include "message_box.hpp"

namespace centurion {

message_box::button::button(button_id id,
                            std::string text,
                            default_button defaultButton)
    : m_id{id}, m_defaultButton{defaultButton}, m_text{std::move(text)}
{}

auto message_box::button::id() const noexcept -> button_id
{
  return m_id;
}

auto message_box::button::convert() const noexcept -> SDL_MessageBoxButtonData
{
  SDL_MessageBoxButtonData result{};

  result.flags = static_cast<u32>(m_defaultButton);
  result.buttonid = m_id;
  result.text = m_text.c_str();

  return result;
}

}  // namespace centurion
