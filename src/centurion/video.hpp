/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

#if SDL_VERSION_ATLEAST(2, 0, 16)

enum class flash_op
{
  cancel = SDL_FLASH_CANCEL,               ///< Cancel any current flashing.
  briefly = SDL_FLASH_BRIEFLY,             ///< Briefly flash the window.
  until_focused = SDL_FLASH_UNTIL_FOCUSED  ///< Flash the window until it's focused.
};

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

enum class blend_op
{
  add = SDL_BLENDOPERATION_ADD,
  sub = SDL_BLENDOPERATION_SUBTRACT,
  reverse_sub = SDL_BLENDOPERATION_REV_SUBTRACT,
  min = SDL_BLENDOPERATION_MINIMUM,
  max = SDL_BLENDOPERATION_MAXIMUM
};

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

enum class orientation
{
  unknown = SDL_ORIENTATION_UNKNOWN,
  landscape = SDL_ORIENTATION_LANDSCAPE,
  landscape_flipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
  portrait = SDL_ORIENTATION_PORTRAIT,
  portrait_flipped = SDL_ORIENTATION_PORTRAIT_FLIPPED
};

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

class display_mode final
{
 public:
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

  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(mMode.format);
  }

  [[nodiscard]] auto width() const noexcept -> int { return mMode.w; }
  [[nodiscard]] auto height() const noexcept -> int { return mMode.h; }
  [[nodiscard]] auto size() const noexcept -> iarea { return {mMode.w, mMode.h}; }

  [[nodiscard]] auto refresh_rate() const noexcept -> maybe<int>
  {
    if (mMode.refresh_rate != 0) {
      return mMode.refresh_rate;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto driver_data() noexcept -> void* { return mMode.driverdata; }
  [[nodiscard]] auto driver_data() const noexcept -> const void* { return mMode.driverdata; }

 private:
  SDL_DisplayMode mMode{};

  explicit display_mode(const SDL_DisplayMode mode) : mMode{mode} {}
};

/// Describes how a blend mode factors should be combined.
struct blend_task final
{
  blend_factor src;  ///< The blend factor applied to the source pixels.
  blend_factor dst;  ///< The blend factor applied to the destination pixels.
  blend_op op;       ///< The operation used to combine the source and destination pixels.
};

struct dpi_info final
{
  float diagonal{};
  float horizontal{};
  float vertical{};
};

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

inline void set_screen_saver_enabled(const bool enabled) noexcept
{
  if (enabled) {
    SDL_EnableScreenSaver();
  }
  else {
    SDL_DisableScreenSaver();
  }
}

[[nodiscard]] inline auto is_screen_saver_enabled() noexcept -> bool
{
  return SDL_IsScreenSaverEnabled();
}

[[nodiscard]] inline auto display_count() noexcept -> maybe<int>
{
  const auto count = SDL_GetNumVideoDisplays();
  if (count >= 1) {
    return count;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_name(const int index = 0) -> maybe<std::string>
{
  if (const char* name = SDL_GetDisplayName(index)) {
    return std::string{name};
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_orientation(const int index = 0) noexcept -> orientation
{
  return static_cast<orientation>(SDL_GetDisplayOrientation(index));
}

[[nodiscard]] inline auto display_dpi(const int index = 0) noexcept -> maybe<dpi_info>
{
  dpi_info info;
  if (SDL_GetDisplayDPI(index, &info.diagonal, &info.horizontal, &info.vertical) == 0) {
    return info;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_bounds(const int index = 0) noexcept -> maybe<irect>
{
  irect result;
  if (SDL_GetDisplayBounds(index, result.data()) == 0) {
    return result;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_usable_bounds(const int index = 0) noexcept -> maybe<irect>
{
  irect result;
  if (SDL_GetDisplayUsableBounds(index, result.data()) == 0) {
    return result;
  }
  else {
    return nothing;
  }
}

#if SDL_VERSION_ATLEAST(2, 24, 0)

[[nodiscard]] inline auto display_with(const ipoint& point) noexcept -> maybe<int>
{
  const auto index = SDL_GetPointDisplayIndex(point.data());
  if (index >= 0) {
    return index;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto display_with(const irect& rect) noexcept -> maybe<int>
{
  const auto index = SDL_GetRectDisplayIndex(rect.data());
  if (index >= 0) {
    return index;
  }
  else {
    return nothing;
  }
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)

}  // namespace cen

#endif  // CENTURION_VIDEO_HPP_
