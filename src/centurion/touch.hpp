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

#ifndef CENTURION_TOUCH_HPP_
#define CENTURION_TOUCH_HPP_

#include <SDL.h>

#include <optional>     // optional
#include <ostream>      // ostream
#include <string_view>  // string_view

#include "common.hpp"
#include "input.hpp"

namespace cen {

using touch_id = SDL_TouchID;

[[nodiscard]] constexpr auto touch_mouse_id() noexcept -> uint32 { return SDL_TOUCH_MOUSEID; }

[[nodiscard]] constexpr auto mouse_touch_id() noexcept -> touch_id
{
  return SDL_MOUSE_TOUCHID;
}

enum class touch_device_type
{
  invalid = SDL_TOUCH_DEVICE_INVALID,
  direct = SDL_TOUCH_DEVICE_DIRECT,
  indirect_absolute = SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE,
  indirect_relative = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE
};

[[nodiscard]] constexpr auto to_string(const touch_device_type type) -> std::string_view
{
  switch (type) {
    case touch_device_type::invalid:
      return "invalid";

    case touch_device_type::direct:
      return "direct";

    case touch_device_type::indirect_absolute:
      return "indirect_absolute";

    case touch_device_type::indirect_relative:
      return "indirect_relative";

    default:
      throw exception{"Did not recognize touch device type!"};
  }
}

inline auto operator<<(std::ostream& stream, const touch_device_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// Provides a view into the state of a touch finger.
class finger final
{
 public:
  using id_type = SDL_FingerID;

  [[nodiscard]] static auto find(const touch_id id, const int index) noexcept -> maybe<finger>
  {
    if (const auto* data = SDL_GetTouchFinger(id, index)) {
      return finger{*data};
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto id() const noexcept -> id_type { return mFinger.id; }
  [[nodiscard]] auto x() const noexcept -> float { return mFinger.x; }
  [[nodiscard]] auto y() const noexcept -> float { return mFinger.y; }
  [[nodiscard]] auto pressure() const noexcept -> float { return mFinger.pressure; }

  [[nodiscard]] auto get() const noexcept -> const SDL_Finger& { return mFinger; }

 private:
  SDL_Finger mFinger{};

  explicit finger(const SDL_Finger& other) noexcept : mFinger{other} {}
};

[[nodiscard]] inline auto touch_device_count() noexcept -> int
{
  return SDL_GetNumTouchDevices();
}

[[nodiscard]] inline auto get_touch_device(const int index) noexcept -> maybe<touch_id>
{
  const auto device = SDL_GetTouchDevice(index);
  if (device != 0) {
    return device;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto get_touch_type(const touch_id id) noexcept -> touch_device_type
{
  return static_cast<touch_device_type>(SDL_GetTouchDeviceType(id));
}

[[nodiscard]] inline auto get_touch_finger_count(const touch_id id) noexcept -> int
{
  return SDL_GetNumTouchFingers(id);
}

}  // namespace cen

#endif  // CENTURION_TOUCH_HPP_