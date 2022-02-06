#ifndef CENTURION_VIDEO_HPP_
#define CENTURION_VIDEO_HPP_

#include <SDL.h>

#include <optional>     // optional, nullopt
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "common.hpp"
#include "math.hpp"
#include "pixels.hpp"

namespace cen {

/// \addtogroup video
/// \{

#if SDL_VERSION_ATLEAST(2, 0, 16)

enum class flash_op
{
  cancel = SDL_FLASH_CANCEL,               ///< Cancel any current flashing.
  briefly = SDL_FLASH_BRIEFLY,             ///< Briefly flash the window.
  until_focused = SDL_FLASH_UNTIL_FOCUSED  ///< Flash the window until it's focused.
};

/// \name Flash operation functions
/// \{

[[nodiscard]] constexpr auto to_string(const flash_op op) -> std::string_view
{
  switch (op) {
    case flash_op::cancel:
      return "cancel";

    case flash_op::briefly:
      return "briefly";

    case flash_op::until_focused:
      return "until_focused";

    default:
      throw exception{"Did not recognize window flash operation!"};
  }
}

inline auto operator<<(std::ostream& stream, const flash_op op) -> std::ostream&
{
  return stream << to_string(op);
}

/// \} End of flash operation functions

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

enum class blend_mode
{
  none = SDL_BLENDMODE_NONE,    ///< No blending.
  blend = SDL_BLENDMODE_BLEND,  ///< Alpha blending.
  add = SDL_BLENDMODE_ADD,      ///< Additive blending.
  mod = SDL_BLENDMODE_MOD,      ///< Color modulation.

#if SDL_VERSION_ATLEAST(2, 0, 12)

  mul = SDL_BLENDMODE_MUL,  ///< Color multiplication.

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  invalid = SDL_BLENDMODE_INVALID
};

/// \name Blend mode functions
/// \{

[[nodiscard]] constexpr auto to_string(const blend_mode mode) -> std::string_view
{
  switch (mode) {
    case blend_mode::none:
      return "none";

    case blend_mode::blend:
      return "blend";

    case blend_mode::add:
      return "add";

    case blend_mode::mod:
      return "mod";

    case blend_mode::invalid:
      return "invalid";

#if SDL_VERSION_ATLEAST(2, 0, 12)

    case blend_mode::mul:
      return "mul";

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    default:
      throw exception{"Did not recognize blend mode!"};
  }
}

inline auto operator<<(std::ostream& stream, const blend_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

/// \} End of blend mode functions

enum class blend_factor
{
  zero = SDL_BLENDFACTOR_ZERO,
  one = SDL_BLENDFACTOR_ONE,

  src_color = SDL_BLENDFACTOR_SRC_COLOR,
  one_minus_src_color = SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,

  src_alpha = SDL_BLENDFACTOR_SRC_ALPHA,
  one_minus_src_alpha = SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,

  dst_color = SDL_BLENDFACTOR_DST_COLOR,
  one_minus_dst_color = SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,

  dst_alpha = SDL_BLENDFACTOR_DST_ALPHA,
  one_minus_dst_alpha = SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA
};

/// \name Blend factor functions
/// \{

[[nodiscard]] constexpr auto to_string(const blend_factor factor) -> std::string_view
{
  switch (factor) {
    case blend_factor::zero:
      return "zero";

    case blend_factor::one:
      return "one";

    case blend_factor::src_color:
      return "src_color";

    case blend_factor::one_minus_src_color:
      return "one_minus_src_color";

    case blend_factor::src_alpha:
      return "src_alpha";

    case blend_factor::one_minus_src_alpha:
      return "one_minus_src_alpha";

    case blend_factor::dst_color:
      return "dst_color";

    case blend_factor::one_minus_dst_color:
      return "one_minus_dst_color";

    case blend_factor::dst_alpha:
      return "dst_alpha";

    case blend_factor::one_minus_dst_alpha:
      return "one_minus_dst_alpha";

    default:
      throw exception{"Did not recognize blend factor!"};
  }
}

inline auto operator<<(std::ostream& stream, const blend_factor factor) -> std::ostream&
{
  return stream << to_string(factor);
}

/// \} End of blend factor functions

enum class blend_op
{
  add = SDL_BLENDOPERATION_ADD,
  sub = SDL_BLENDOPERATION_SUBTRACT,
  reverse_sub = SDL_BLENDOPERATION_REV_SUBTRACT,
  min = SDL_BLENDOPERATION_MINIMUM,
  max = SDL_BLENDOPERATION_MAXIMUM
};

/// \name Blend operation functions
/// \{

[[nodiscard]] constexpr auto to_string(const blend_op op) -> std::string_view
{
  switch (op) {
    case blend_op::add:
      return "add";

    case blend_op::sub:
      return "sub";

    case blend_op::reverse_sub:
      return "reverse_sub";

    case blend_op::min:
      return "min";

    case blend_op::max:
      return "max";

    default:
      throw exception{"Did not recognize blend operation!"};
  }
}

inline auto operator<<(std::ostream& stream, const blend_op op) -> std::ostream&
{
  return stream << to_string(op);
}

/// \} End of blend operation functions

enum class orientation
{
  unknown = SDL_ORIENTATION_UNKNOWN,
  landscape = SDL_ORIENTATION_LANDSCAPE,
  landscape_flipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
  portrait = SDL_ORIENTATION_PORTRAIT,
  portrait_flipped = SDL_ORIENTATION_PORTRAIT_FLIPPED
};

/// \name Orientation functions
/// \{

[[nodiscard]] constexpr auto to_string(const orientation o) -> std::string_view
{
  switch (o) {
    case orientation::unknown:
      return "unknown";

    case orientation::landscape:
      return "landscape";

    case orientation::landscape_flipped:
      return "landscape_flipped";

    case orientation::portrait:
      return "portrait";

    case orientation::portrait_flipped:
      return "portrait_flipped";

    default:
      throw exception{"Did not recognize display orientation!"};
  }
}

inline auto operator<<(std::ostream& stream, const orientation o) -> std::ostream&
{
  return stream << to_string(o);
}

/// \} End of orientation functions

/**
 * \brief Represents the mode of a display.
 */
class display_mode final
{
 public:
  /// \name Factory functions
  /// \{

  /**
   * \brief Returns information about the current display mode for a display.
   *
   * \param index the index of the display to query, in the range [0, `display_count()`].
   *
   * \return the current display mode.
   *
   * \throws sdl_error if the display mode cannot be obtained.
   */
  [[nodiscard]] static auto current(const int index = 0) -> display_mode
  {
    SDL_DisplayMode mode{};
    if (SDL_GetCurrentDisplayMode(index, &mode) == 0) {
      return display_mode{mode};
    }
    else {
      throw sdl_error{};
    }
  }

  /**
   * \brief Returns information about the desktop display mode for a display.
   *
   * \param index the index of the display to query, in the range [0, `display_count()`].
   *
   * \return the desktop display mode.
   *
   * \throws sdl_error if the display mode cannot be obtained.
   */
  [[nodiscard]] static auto desktop(const int index = 0) -> display_mode
  {
    SDL_DisplayMode mode{};
    if (SDL_GetDesktopDisplayMode(index, &mode) == 0) {
      return display_mode{mode};
    }
    else {
      throw sdl_error{};
    }
  }

  /// \} End of factory functions

  /**
   * \brief Returns the pixel format of the display mode.
   *
   * \return the display mode pixel format.
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(mMode.format);
  }

  /**
   * \brief Returns the screen width of the display mode.
   *
   * \return the display mode screen width.
   */
  [[nodiscard]] auto width() const noexcept -> int { return mMode.w; }

  /**
   * \brief Returns the screen height of the display mode.
   *
   * \return the display mode screen height.
   */
  [[nodiscard]] auto height() const noexcept -> int { return mMode.h; }

  /**
   * \brief Returns the screen size of the display mode.
   *
   * \return the display mode screen size.
   */
  [[nodiscard]] auto size() const noexcept -> iarea { return {mMode.w, mMode.h}; }

  /**
   * \brief Returns the refresh rate of the display mode.
   *
   * \return the display mode refresh rate; an empty optional is returned if it's unavailable.
   */
  [[nodiscard]] auto refresh_rate() const noexcept -> std::optional<int>
  {
    if (mMode.refresh_rate != 0) {
      return mMode.refresh_rate;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the potential driver data associated with the display mode.
   *
   * \return the driver data.
   */
  [[nodiscard]] auto driver_data() noexcept -> void* { return mMode.driverdata; }

  /// \copydoc driver_data()
  [[nodiscard]] auto driver_data() const noexcept -> const void* { return mMode.driverdata; }

 private:
  SDL_DisplayMode mMode{};

  explicit display_mode(const SDL_DisplayMode mode) : mMode{mode} {}
};

/**
 * \brief Describes how a blend mode factors should be combined.
 */
struct blend_task final
{
  blend_factor src;  ///< The blend factor applied to the source pixels.
  blend_factor dst;  ///< The blend factor applied to the destination pixels.
  blend_op op;       ///< The operation used to combine the source and destination pixels.
};

/**
 * \brief Provides diagonal, horizontal and vertical DPI information.
 */
struct dpi_info final
{
  float diagonal{};
  float horizontal{};
  float vertical{};
};

/// \name Blend mode functions
/// \{

[[nodiscard]] inline auto compose_blend_mode(const blend_task& color,
                                             const blend_task& alpha) noexcept -> blend_mode
{
  const auto res = SDL_ComposeCustomBlendMode(static_cast<SDL_BlendFactor>(color.src),
                                              static_cast<SDL_BlendFactor>(color.dst),
                                              static_cast<SDL_BlendOperation>(color.op),
                                              static_cast<SDL_BlendFactor>(alpha.src),
                                              static_cast<SDL_BlendFactor>(alpha.dst),
                                              static_cast<SDL_BlendOperation>(alpha.op));
  return static_cast<blend_mode>(res);
}

/// \} End of blend mode functions

/// \name Screen saver functions
/// \{

/**
 * \brief Sets whether screen savers are enabled.
 *
 * \details By default, screen savers are disabled.
 *
 * \param enabled `true` if screen savers should be enabled; `false` otherwise.
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
 * \brief Indicates whether screen savers are enabled.
 *
 * \return `true` if screen savers are enabled; `false` otherwise.
 */
[[nodiscard]] inline auto is_screen_saver_enabled() noexcept -> bool
{
  return SDL_IsScreenSaverEnabled();
}

/// \} End of screen saver functions

/// \name Display functions
/// \{

/**
 * \brief Returns the amount of available displays.
 *
 * \return the number of available displays.
 */
[[nodiscard]] inline auto display_count() noexcept -> int
{
  return SDL_GetNumVideoDisplays();
}

/**
 * \brief Returns the name of a display.
 *
 * \param index the index of the queried display, in the range [0, `display_count()`].
 *
 * \return the display name; an empty optional is returned if the name couldn't be obtained.
 */
[[nodiscard]] inline auto display_name(const int index = 0) -> std::optional<std::string>
{
  if (const char* name = SDL_GetDisplayName(index)) {
    return std::string{name};
  }
  else {
    return std::nullopt;
  }
}

/**
 * \brief Returns the orientation of a display.
 *
 * \param index the index of the queried display, in the range [0, `display_count()`].
 *
 * \return the display orientation.
 */
[[nodiscard]] inline auto display_orientation(const int index = 0) noexcept -> orientation
{
  return static_cast<orientation>(SDL_GetDisplayOrientation(index));
}

/**
 * \brief Returns the DPI of a display.
 *
 * \param index the index of the queried display, in the range [0, `display_count()`].
 *
 * \return the DPI information; an empty optional is returned if an error occurs.
 */
[[nodiscard]] inline auto display_dpi(const int index = 0) noexcept -> std::optional<dpi_info>
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
 * \brief Returns the bounds of a display.
 *
 * \param index the index of the queried display, in the range [0, `display_count()`].
 *
 * \return the display bounds; an empty optional is returned if an error occurs.
 */
[[nodiscard]] inline auto display_bounds(const int index = 0) noexcept -> std::optional<irect>
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
 * \param index the index of the queried display, in the range [0, `display_count()`].
 *
 * \return the usable display bounds; an empty optional is returned if an error occurs.
 */
[[nodiscard]] inline auto display_usable_bounds(const int index = 0) noexcept
    -> std::optional<irect>
{
  irect result;
  if (SDL_GetDisplayUsableBounds(index, result.data()) == 0) {
    return result;
  }
  else {
    return std::nullopt;
  }
}

/// \} End of display functions

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_VIDEO_HPP_
