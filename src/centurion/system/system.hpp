#ifndef CENTURION_SYSTEM_SYSTEM_HPP_
#define CENTURION_SYSTEM_SYSTEM_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <string>    // string

#include "../core/common.hpp"
#include "../core/time.hpp"

namespace cen {

/// \addtogroup system
/// \{

/// \name Counter functions
/// \{

/**
 * \brief Returns the frequency of the system high-performance counter.
 *
 * \return the frequency of the system high-performance counter.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto frequency() noexcept -> u64
{
  return SDL_GetPerformanceFrequency();
}

/**
 * \brief Returns the current raw value of the system high-performance counter.
 *
 * \note The unit of the returned value is platform dependent.
 *
 * \return the current value of the system high-performance counter.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto now() noexcept -> u64
{
  return SDL_GetPerformanceCounter();
}

/**
 * \brief Returns the value of the system high-performance counter in seconds.
 *
 * \tparam T the representation type.
 *
 * \return the value of the system high-performance counter, in seconds.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto now_in_seconds() noexcept(noexcept(seconds<T>{})) -> seconds<T>
{
  return seconds<T>{static_cast<T>(SDL_GetPerformanceCounter()) / static_cast<T>(frequency())};
}

/**
 * \brief Returns the amount of milliseconds since the library was initialized.
 *
 * \return the amount of milliseconds since the library was initialized.
 *
 * \deprecated Since 6.4.0, use `ticks64()` instead.
 *
 * \since 3.0.0
 */
[[nodiscard, deprecated]] inline auto ticks() noexcept(noexcept(u32_ms{u32{}})) -> u32_ms
{
  return u32_ms{SDL_GetTicks()};
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

/**
 * \brief Returns the amount of milliseconds since the library was initialized.
 *
 * \return the amount of milliseconds since the library was initialized.
 *
 * \since 6.4.0
 */
[[nodiscard]] inline auto ticks64() noexcept(noexcept(u64_ms{u64{}})) -> u64_ms
{
  return u64_ms{SDL_GetTicks64()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

/// \} End of counter functions

/// \name RAM functions
/// \{

/**
 * \brief Returns the total amount of system RAM, in megabytes.
 *
 * \return the amount of RAM.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto memory_mb() noexcept -> int
{
  return SDL_GetSystemRAM();
}

/**
 * \brief Returns the total amount of system RAM, in gigabytes.
 *
 * \return the amount of RAM.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto memory_gb() noexcept -> int
{
  return memory_mb() / 1'000;
}

/// \} End of RAM functions

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

#endif  // CENTURION_SYSTEM_SYSTEM_HPP_
