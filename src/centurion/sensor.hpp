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

#ifndef CENTURION_SENSOR_HPP_
#define CENTURION_SENSOR_HPP_

#include <SDL.h>

#include <array>        // array
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

using sensor_id = SDL_SensorID;

[[nodiscard]] constexpr auto standard_gravity() noexcept -> float
{
  return SDL_STANDARD_GRAVITY;
}

enum class sensor_type
{
  invalid = SDL_SENSOR_INVALID,      ///< Invalid sensor.
  unknown = SDL_SENSOR_UNKNOWN,      ///< Unknown sensor.
  accelerometer = SDL_SENSOR_ACCEL,  ///< Accelerometer.
  gyroscope = SDL_SENSOR_GYRO        ///< Gyroscope.
};

[[nodiscard]] constexpr auto to_string(const sensor_type type) -> std::string_view
{
  switch (type) {
    case sensor_type::invalid:
      return "invalid";

    case sensor_type::unknown:
      return "unknown";

    case sensor_type::accelerometer:
      return "accelerometer";

    case sensor_type::gyroscope:
      return "gyroscope";

    default:
      throw exception{"Did not recognize sensor type!"};
  }
}

inline auto operator<<(std::ostream& stream, const sensor_type type) -> std::ostream&
{
  return stream << to_string(type);
}

template <typename T>
class basic_sensor;

using sensor = basic_sensor<detail::owner_tag>;
using sensor_handle = basic_sensor<detail::handle_tag>;

/**
 * Represents a sensor device.
 *
 * \see sensor
 * \see sensor_handle
 */
template <typename T>
class basic_sensor final
{
 public:
  using device_index = int;
  using size_type = usize;

  template <size_type Size>
  using data_type = std::array<float, Size>;

  /**
   * Creates a sensor instance based on an existing SDL sensor.
   *
   * Ownership of the pointer is claimed if the class has owning semantics.
   *
   * \param sensor a pointer to the SDL sensor data.
   */
  explicit basic_sensor(maybe_owner<SDL_Sensor*> sensor) noexcept(detail::is_handle<T>)
      : mSensor{sensor}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mSensor) {
        throw exception{"Null sensor pointer!"};
      }
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sensor(const device_index index = 0) : mSensor{SDL_SensorOpen(index)}
  {
    if (!mSensor) {
      throw sdl_error{};
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_sensor(const sensor& owner) noexcept : mSensor{owner.get()}
  {}

  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_SensorGetName(mSensor);
  }

  [[nodiscard]] static auto name(const device_index index) noexcept -> const char*
  {
    return SDL_SensorGetDeviceName(index);
  }

  [[nodiscard]] auto type() const noexcept -> sensor_type
  {
    return static_cast<sensor_type>(SDL_SensorGetType(mSensor));
  }

  [[nodiscard]] static auto type(const device_index index) noexcept -> sensor_type
  {
    return static_cast<sensor_type>(SDL_SensorGetDeviceType(index));
  }

  [[nodiscard]] auto non_portable_type() const noexcept -> maybe<int>
  {
    const auto type = SDL_SensorGetNonPortableType(mSensor);
    if (type != -1) {
      return type;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] static auto non_portable_type(const device_index index) noexcept -> maybe<int>
  {
    const auto type = SDL_SensorGetDeviceNonPortableType(index);
    if (type != -1) {
      return type;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto id() const noexcept -> maybe<sensor_id>
  {
    const auto id = SDL_SensorGetInstanceID(mSensor);
    if (id != -1) {
      return id;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] static auto id(const device_index index) noexcept -> maybe<sensor_id>
  {
    const auto id = SDL_SensorGetDeviceInstanceID(index);
    if (id != -1) {
      return id;
    }
    else {
      return nothing;
    }
  }

  template <size_type Size>
  [[nodiscard]] auto data() const noexcept -> maybe<data_type<Size>>
  {
    data_type<Size> array{};
    if (SDL_SensorGetData(mSensor, array.data(), isize(array)) != -1) {
      return array;
    }
    else {
      return nothing;
    }
  }

  static void update() noexcept { SDL_SensorUpdate(); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  static void lock() noexcept { SDL_LockSensors(); }

  static void unlock() noexcept { SDL_UnlockSensors(); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] static auto count() noexcept -> int { return SDL_NumSensors(); }

  [[nodiscard]] auto get() const noexcept -> SDL_Sensor* { return mSensor.get(); }

  /// Indicates whether a handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mSensor != nullptr;
  }

 private:
  detail::pointer<T, SDL_Sensor> mSensor;
};

template <typename T>
[[nodiscard]] auto to_string(const basic_sensor<T>& sensor) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("sensor(data: {}, id: {}, name: '{}')",
                     detail::address_of(sensor.get()),
                     sensor.id().value(),
                     str_or_na(sensor.name()));
#else
  return "sensor(data: " + detail::address_of(sensor.get()) +
         ", id: " + std::to_string(sensor.id().value()) + ", name: '" +
         str_or_na(sensor.name()) + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_sensor<T>& sensor) -> std::ostream&
{
  return stream << to_string(sensor);
}

}  // namespace cen

#endif  // CENTURION_SENSOR_HPP_
