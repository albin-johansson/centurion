#ifndef CENTURION_SCREEN_HEADER
#define CENTURION_SCREEN_HEADER

#include <SDL.h>

#include <optional>     // optional
#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/str.hpp"
#include "../math/area.hpp"
#include "../math/rect.hpp"
#include "pixel_format.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \struct dpi_info
 *
 * \brief Provides diagonal, horizontal and vertical DPI values.
 *
 * \since 5.0.0
 */
struct dpi_info final
{
  float diagonal{};    ///< The diagonal DPI value.
  float horizontal{};  ///< The horizontal DPI value.
  float vertical{};    ///< The vertical DPI value.
};

/**
 * \enum screen_orientation
 *
 * \brief Represents different screen orientations.
 *
 * \since 5.0.0
 *
 * \see SDL_DisplayOrientation
 */
enum class screen_orientation : int
{
  unknown = SDL_ORIENTATION_UNKNOWN,
  landscape = SDL_ORIENTATION_LANDSCAPE,
  landscape_flipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
  portrait = SDL_ORIENTATION_PORTRAIT,
  portrait_flipped = SDL_ORIENTATION_PORTRAIT_FLIPPED
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied screen orientation.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(screen_orientation::landscape) == "landscape"`.
 *
 * \param orientation the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const screen_orientation orientation)
    -> std::string_view
{
  switch (orientation) {
    case screen_orientation::unknown:
      return "unknown";

    case screen_orientation::landscape:
      return "landscape";

    case screen_orientation::landscape_flipped:
      return "landscape_flipped";

    case screen_orientation::portrait:
      return "portrait";

    case screen_orientation::portrait_flipped:
      return "portrait_flipped";

    default:
      throw cen_error{"Did not recognize screen orientation!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a screen orientation enumerator.
 *
 * \param stream the output stream that will be used.
 * \param orientation the enumerator that will be printed.
 *
 * \see `to_string(screen_orientation)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const screen_orientation orientation)
    -> std::ostream&
{
  return stream << to_string(orientation);
}

/// \} End of streaming

/**
 * \brief Sets whether or not screen savers are enabled.
 *
 * \note By default, screen savers are disabled.
 *
 * \param enabled `true` if screen savers should be enabled; `false` otherwise.
 *
 * \since 4.0.0
 */
inline void set_screen_saver_enabled(const bool enabled) noexcept
{
  if (enabled) {
    SDL_EnableScreenSaver();
  }
  else {
    SDL_DisableScreenSaver();
  }
}

/**
 * \brief Indicates whether or not screen savers are enabled.
 *
 * \note By default, screen savers are disabled.
 *
 * \return `true` if screen savers are enabled; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto is_screen_saver_enabled() noexcept -> bool
{
  return SDL_IsScreenSaverEnabled();
}

/// \} End of group video

}  // namespace cen

/// \addtogroup video
/// \{

/**
 * \namespace cen::screen
 *
 * \brief Contains functions that provide information about screen(s).
 *
 * \since 5.0.0
 */
namespace cen::screen {

/**
 * \brief Returns the amount of available displays.
 *
 * \return the number of available displays.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto count() noexcept -> int
{
  return SDL_GetNumVideoDisplays();
}

/**
 * \brief Returns the name of a display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the name of the specified display, might be null.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto name(const int index = 0) noexcept -> str
{
  return SDL_GetDisplayName(index);
}

/**
 * \brief Returns the orientation of the specified display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the orientation of the specified display.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto get_orientation(const int index = 0) noexcept -> screen_orientation
{
  return static_cast<screen_orientation>(SDL_GetDisplayOrientation(index));
}

/// \name Display mode queries
/// \{

/**
 * \brief Returns the desktop display mode.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the desktop display mode; `std::nullopt` if something goes wrong.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto display_mode(const int index = 0) noexcept
    -> std::optional<SDL_DisplayMode>
{
  SDL_DisplayMode mode{};
  if (SDL_GetDesktopDisplayMode(index, &mode) == 0) {
    return mode;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the refresh rate of the screen.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the refresh rate of the screen; `std::nullopt` if something goes wrong.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto refresh_rate(const int index = 0) noexcept -> std::optional<int>
{
  if (const auto mode = display_mode(index)) {
    return mode->refresh_rate;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the pixel format of the desktop display mode.
 *
 * \note This function returns the pixel format used by the desktop display mode, i.e. the
 * fullscreen display mode, so it might not be accurate for non-fullscreen windows.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the pixel format of the desktop display mode; `std::nullopt` if something goes
 * wrong.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto get_pixel_format(const int index = 0) noexcept
    -> std::optional<pixel_format>
{
  if (const auto mode = display_mode(index)) {
    return static_cast<pixel_format>(mode->format);
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the width of the screen.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the width of the screen; `std::nullopt` if something goes wrong.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto width(const int index = 0) noexcept -> std::optional<int>
{
  if (const auto mode = display_mode(index)) {
    return display_mode(index)->w;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the height of the screen.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the height of the screen; `std::nullopt` if something goes wrong.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto height(const int index = 0) noexcept -> std::optional<int>
{
  if (const auto mode = display_mode(index)) {
    return display_mode(index)->h;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the size of the screen.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the size of the screen; `std::nullopt` if something goes wrong.
 *
 * \since 4.1.0
 */
[[nodiscard]] inline auto size(const int index = 0) noexcept -> std::optional<iarea>
{
  if (const auto mode = display_mode(index)) {
    return iarea{mode->w, mode->h};
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns DPI information about a display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return DPI information about the specified display; `std::nullopt` if something went
 * wrong.
 *
 * \see SDL_GetDisplayDPI
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto dpi(const int index = 0) noexcept -> std::optional<dpi_info>
{
  dpi_info info;
  if (SDL_GetDisplayDPI(index, &info.diagonal, &info.horizontal, &info.vertical) == 0) {
    return info;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns vertical DPI information about a display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the vertical DPI information about the specified display; `std::nullopt` if
 * something went wrong.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto vertical_dpi(const int index = 0) noexcept -> std::optional<float>
{
  if (const auto info = dpi(index)) {
    return info->vertical;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns diagonal DPI information about a display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the diagonal DPI information about the specified display; `std::nullopt` if
 * something went wrong.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto diagonal_dpi(const int index = 0) noexcept -> std::optional<float>
{
  if (const auto info = dpi(index)) {
    return info->diagonal;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns horizontal DPI information about a display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the horizontal DPI information about the specified display; `std::nullopt` if
 * something went wrong.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto horizontal_dpi(const int index = 0) noexcept -> std::optional<float>
{
  if (const auto info = dpi(index)) {
    return info->horizontal;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the bounds of a display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the bounds of the specified display; `std::nullopt` if something went wrong.
 *
 * \see SDL_GetDisplayBounds
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto bounds(const int index = 0) noexcept -> std::optional<irect>
{
  irect result;
  if (SDL_GetDisplayBounds(index, result.data()) == 0) {
    return result;
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the usable bounds of a display.
 *
 * \param index the index of the queried display, in the range [0,
 * `cen::screen::count()`].
 *
 * \return the usable bounds of the specified display; `std::nullopt` if something went
 * wrong.
 *
 * \see SDL_GetDisplayUsableBounds
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto usable_bounds(const int index = 0) noexcept -> std::optional<irect>
{
  irect result;
  if (SDL_GetDisplayUsableBounds(index, result.data()) == 0) {
    return result;
  }
  else {
    return std::nullopt;
  }
}

/// \} End of display mode queries

}  // namespace cen::screen

/// \} End of group video

#endif  // CENTURION_SCREEN_HEADER