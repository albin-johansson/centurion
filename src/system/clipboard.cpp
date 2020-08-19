#include "clipboard.hpp"

#include <memory>

namespace centurion::clipboard {
namespace {

// TODO recurring deleter, add sdl_string class == zstring?
class deleter final
{
 public:
  void operator()(zstring text) noexcept { SDL_free(text); }
};

}  // namespace

auto has_text() noexcept -> bool
{
  return SDL_HasClipboardText();
}

auto get_text() -> std::string
{
  const std::unique_ptr<char, deleter> text{SDL_GetClipboardText()};
  if (text) {
    return std::string{text.get()};
  } else {
    return "";
  }
}

auto set_text(nn_czstring text) noexcept -> bool
{
  return SDL_SetClipboardText(text) == 0;
}

}  // namespace centurion::clipboard
