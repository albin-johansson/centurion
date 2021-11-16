#ifndef CENTURION_CLIPBOARD_HEADER
#define CENTURION_CLIPBOARD_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string

#include "../core/common.hpp"
#include "../core/result.hpp"
#include "../core/sdl_string.hpp"

namespace cen {

/// \addtogroup system
/// \{

/// \name Clipboard functions
/// \{

/**
 * \brief Indicates whether or not the clipboard exists and that it contains non-empty text.
 *
 * \return `true` if there is clipboard text; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto has_clipboard_text() noexcept -> bool
{
  return SDL_HasClipboardText();
}

/**
 * \brief Returns the current clipboard text.
 *
 * \details If the clipboard cannot be obtained, this function returns the empty string.
 *
 * \return the clipboard text.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto get_clipboard_text() -> std::string
{
  const sdl_string text{SDL_GetClipboardText()};
  return text.copy();
}

/**
 * \brief Sets the current clipboard text.
 *
 * \pre `text` cannot be null.
 *
 * \param text the text that will be stored in the clipboard.
 *
 * \return `success` if the clipboard text was successfully set; `failure` otherwise.
 *
 * \since 5.0.0
 */
inline auto set_clipboard_text(const not_null<str> text) noexcept -> result
{
  assert(text);
  return SDL_SetClipboardText(text) == 0;
}

/**
 * \brief Sets the current clipboard text.
 *
 * \param text the text that will be stored in the clipboard.
 *
 * \return `success` if the clipboard text was successfully set; `failure` otherwise.
 *
 * \since 5.3.0
 */
inline auto set_clipboard_text(const std::string& text) noexcept -> result
{
  return set_clipboard_text(text.c_str());
}

/// \} End of clipboard functions

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_CLIPBOARD_HEADER
