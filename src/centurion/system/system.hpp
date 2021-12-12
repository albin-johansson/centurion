#ifndef CENTURION_SYSTEM_SYSTEM_HPP_
#define CENTURION_SYSTEM_SYSTEM_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <chrono>       // duration_cast
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "../core/common.hpp"
#include "../core/exception.hpp"
#include "../core/sdl_string.hpp"
#include "../core/time.hpp"

namespace cen {

/// \addtogroup system
/// \{

/// \brief Represents different battery power states.
/// \since 3.0.0
enum class power_state {
  unknown = SDL_POWERSTATE_UNKNOWN,        ///< The status is unknown.
  on_battery = SDL_POWERSTATE_ON_BATTERY,  ///< Not plugged in and running on battery.
  no_battery = SDL_POWERSTATE_NO_BATTERY,  ///< No battery available.
  charging = SDL_POWERSTATE_CHARGING,      ///< Currently charging the battery.
  charged = SDL_POWERSTATE_CHARGED         ///< Currently plugged in and charged.
};

/// \name Counter functions
/// \{

/**
 * \brief Returns the frequency of the system high-performance counter.
 *
 * \return the frequency of the system high-performance counter.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto frequency() noexcept -> Uint64
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
[[nodiscard]] inline auto now() noexcept -> Uint64
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
[[nodiscard, deprecated]] inline auto ticks() noexcept(noexcept(u32_ms{Uint32{}})) -> u32_ms
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
[[nodiscard]] inline auto ticks64() noexcept(noexcept(u64_ms{Uint64{}})) -> u64_ms
{
  return u64_ms{SDL_GetTicks64()};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

/// \} End of counter functions

/// \name Battery functions
/// \{

/**
 * \brief Returns the seconds of battery life that is remaining.
 *
 * \return seconds of remaining battery life; `std::nullopt` if the value cannot be
 * computed.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto battery_seconds() -> std::optional<seconds<int>>
{
  int secondsLeft = -1;
  SDL_GetPowerInfo(&secondsLeft, nullptr);
  if (secondsLeft != -1) {
    return seconds<int>{secondsLeft};
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the amount of minutes of battery life that is remaining.
 *
 * \return minutes of remaining battery life; `std::nullopt` if the value cannot be
 * computed.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto battery_minutes() -> std::optional<minutes<int>>
{
  if (const auto secondsLeft = battery_seconds()) {
    return std::chrono::duration_cast<minutes<int>>(*secondsLeft);
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the percentage of battery life that is currently left.
 *
 * \return percentage of remaining battery life, in the range [0, 100]; `std::nullopt` if
 * the battery percentage isn't available.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto battery_percentage() noexcept -> std::optional<int>
{
  int percentageLeft = -1;
  SDL_GetPowerInfo(nullptr, &percentageLeft);
  if (percentageLeft != -1) {
    return percentageLeft;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the current power state.
 *
 * \return the current power state.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto query_battery() noexcept -> power_state
{
  return static_cast<power_state>(SDL_GetPowerInfo(nullptr, nullptr));
}

/**
 * \brief Indicates whether or not the system is running on a battery.
 *
 * \details This function is simply a convenience function that is based on the
 * `battery::state()` function.
 *
 * \return `true` if the system is running on a battery; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto battery_exists() noexcept -> bool
{
  const auto state = query_battery();
  return state == power_state::on_battery || state == power_state::charged ||
         state == power_state::charging;
}

/**
 * \brief Indicate whether or not the battery is being charged.
 *
 * \details This convenience function is equivalent to checking if `battery::state()` is
 * equal to `power_state::charging`.
 *
 * \return `true` if the battery is charging; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto battery_charging() noexcept -> bool
{
  return query_battery() == power_state::charging;
}

/**
 * \brief Indicate whether or not the battery is charged.
 *
 * \details This convenience function is equivalent to checking if `battery::state()` is
 * equal to `power_state::charged`.
 *
 * \return `true` if the battery is charged; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto battery_charged() noexcept -> bool
{
  return query_battery() == power_state::charged;
}

/**
 * \brief Indicate whether or not a battery is available.
 *
 * \details This convenience function considers a battery available if the state returned
 * from `battery::state()` is neither `no_battery` nor `unknown`.
 *
 * \return `true` if a battery is available; `false` otherwise.
 *
 * \since 5.1.0
 */
[[nodiscard]] inline auto battery_available() noexcept -> bool
{
  const auto state = query_battery();
  return state != power_state::no_battery && state != power_state::unknown;
}

/// \} End of battery functions

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
inline auto set_clipboard_text(const char* text) noexcept -> result
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

#if SDL_VERSION_ATLEAST(2, 0, 14)

/**
 * \brief Attempts to open a URL using a web browser or even a file manager for local
 * files.
 *
 * \note This function will return `success` if there was at least an "attempt" to open
 * the specified URL, but it doesn't mean that the URL was successfully loaded.
 *
 * \remarks This function will differ greatly in its effects depending on the current
 * platform.
 *
 * \param url the URL that should be opened, cannot be null.
 *
 * \return `success` if there was an attempt to open the URL; `failure` otherwise.
 *
 * \since 5.2.0
 */
inline auto open_url(const char* url) noexcept -> result
{
  assert(url);
  return SDL_OpenURL(url) == 0;
}

/**
 * \see open_url()
 * \since 5.3.0
 */
inline auto open_url(const std::string& url) noexcept -> result
{
  return open_url(url.c_str());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied power state.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(power_state::on_battery) == "on_battery"`.
 *
 * \param state the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const power_state state) -> std::string_view
{
  switch (state) {
    case power_state::unknown:
      return "unknown";

    case power_state::on_battery:
      return "on_battery";

    case power_state::no_battery:
      return "no_battery";

    case power_state::charging:
      return "charging";

    case power_state::charged:
      return "charged";

    default:
      throw Error{"Did not recognize power state!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a power state enumerator.
 *
 * \param stream the output stream that will be used.
 * \param state the enumerator that will be printed.
 *
 * \see `to_string(power_state)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const power_state state) -> std::ostream&
{
  return stream << to_string(state);
}

/// \} End of streaming

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_SYSTEM_SYSTEM_HPP_
