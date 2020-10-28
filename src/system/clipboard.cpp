#include "clipboard.hpp"

#include "sdl_string.hpp"

namespace cen::clipboard {

auto has_text() noexcept -> bool
{
  return SDL_HasClipboardText();
}

auto get_text() -> std::string
{
  const sdl_string text{SDL_GetClipboardText()};
  return text.copy();
}

auto set_text(nn_czstring text) noexcept -> bool
{
  return SDL_SetClipboardText(text) == 0;
}

}  // namespace cen::clipboard
