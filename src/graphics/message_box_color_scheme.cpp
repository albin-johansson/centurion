#include "colors.hpp"
#include "message_box.hpp"

namespace centurion {

message_box::color_scheme::color_scheme() noexcept
{
  set_color(color_id::background, colors::white);
  set_color(color_id::text, colors::white);
  set_color(color_id::button_background, colors::white);
  set_color(color_id::button_border, colors::white);
  set_color(color_id::button_selected, colors::white);
}

void message_box::color_scheme::set_color(color_id id,
                                          const color& color) noexcept
{
  m_scheme.colors[static_cast<int>(id)] =
      static_cast<SDL_MessageBoxColor>(color);
}

auto message_box::color_scheme::get() noexcept -> SDL_MessageBoxColorScheme*
{
  return &m_scheme;
}

}  // namespace centurion
