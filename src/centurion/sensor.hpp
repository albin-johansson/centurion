/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_SENSOR_HEADER
#define CENTURION_SENSOR_HEADER

#include <SDL.h>

#include <array>        // array
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <type_traits>  // true_type, false_type

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "detail/address_of.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/to_string.hpp"
#include "exception.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup input
/// \{

/**
 * \typedef sensor_id
 *
 * \brief Used for unique sensor instance identifiers.
 *
 * \since 5.2.0
 */
using sensor_id = SDL_SensorID;

/**
 * \enum sensor_type
 *
 * \brief Provides values that represent different sensor types.
 *
 * \see SDL_SensorType
 *
 * \since 5.2.0
 */
enum class sensor_type
{
  invalid = SDL_SENSOR_INVALID,      ///< Invalid sensor
  unknown = SDL_SENSOR_UNKNOWN,      ///< Unknown sensor
  accelerometer = SDL_SENSOR_ACCEL,  ///< Accelerometer
  gyroscope = SDL_SENSOR_GYRO        ///< Gyroscope
};

template <typename B>
class basic_sensor;

/**
 * \typedef sensor
 *
 * \brief Represents an owning sensor device.
 *
 * \since 5.2.0
 */
using sensor = basic_sensor<std::true_type>;

/**
 * \typedef sensor_handle
 *
 * \brief Represents a non-owning sensor device.
 *
 * \since 5.2.0
 */
using sensor_handle = basic_sensor<std::false_type>;

/**
 * \class basic_sensor
 *
 * \brief Represents a sensor device.
 *
 * \see sensor
 * \see sensor_handle
 *
 * \tparam B `std::true_type` for owning sensors; `std::false_type` for
 * non-owning sensors.
 *
 * \since 5.2.0
 *
 * \headerfile sensor.hpp
 */
template <typename B>
class basic_sensor final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a sensor instance based on an existing pointer.
   *
   * \note The created instance will claim ownership of the supplied pointer if
   * the class has owning semantics.
   *
   * \param sensor a pointer to the SDL sensor data.
   *
   * \throws exception if the supplied pointer is null and the class has owning
   * semantics.
   *
   * \since 5.2.0
   */
  explicit basic_sensor(SDL_Sensor* sensor) noexcept(!B::value)
      : m_sensor{sensor}
  {
    if constexpr (B::value) {
      if (!m_sensor) {
        throw exception{"Null sensor pointer!"};
      }
    }
  }

  /**
   * \brief Creates an owning sensor instance based on a device index.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param index the device index of the sensor.
   *
   * \throws sdl_error if the sensor cannot be opened.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  explicit basic_sensor(const int index = 0) : m_sensor{SDL_SensorOpen(index)}
  {
    if (!m_sensor) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a sensor handle based on an owning sensor.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param owner the associated owning sensor.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit basic_sensor(const sensor& owner) noexcept : m_sensor{owner.get()}
  {}

  /// \} End of construction

  /// \name Instance-based queries
  /// \{

  /**
   * \brief Returns the unique identifier associated with the sensor instance.
   *
   * \return a unique instance ID.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto id() const noexcept -> sensor_id
  {
    return SDL_SensorGetInstanceID(m_sensor);
  }

  /**
   * \brief Returns the name associated with the sensor device.
   *
   * \return the name of the sensor device; a null pointer is returned if the
   * name isn't available.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto name() const noexcept -> czstring
  {
    return SDL_SensorGetName(m_sensor);
  }

  /**
   * \brief Returns the type associated with the sensor device.
   *
   * \return the type of the sensor device.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto type() const noexcept -> sensor_type
  {
    return static_cast<sensor_type>(SDL_SensorGetType(m_sensor));
  }

  /**
   * \brief Returns the non-portable type associated with the sensor.
   *
   * \return a non-portable sensor type value.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto non_portable_type() const noexcept -> int
  {
    return SDL_SensorGetNonPortableType(m_sensor);
  }

  /**
   * \brief Returns the sensor-dependent data.
   *
   * \tparam size the number of data elements, varies from sensor to sensor.
   *
   * \return the data associated with the sensor; `std::nullopt` if something
   * goes wrong.
   *
   * \since 5.2.0
   */
  template <std::size_t size>
  [[nodiscard]] auto data() const noexcept
      -> std::optional<std::array<float, size>>
  {
    std::array<float, size> array{};
    const auto result = SDL_SensorGetData(m_sensor, array.data(), array.size());
    if (result != -1) {
      return array;
    } else {
      return std::nullopt;
    }
  }

  /// \} End of instance-based queries

  /// \name Index-based queries
  /// \{

  /**
   * \brief Returns the unique identifier associated with a sensor instance.
   *
   * \param index the index of the sensor device that will be queried.
   *
   * \return the unique instance ID associated with a sensor; `std::nullopt` if
   * the index is invalid.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto id(const int index) noexcept
      -> std::optional<sensor_id>
  {
    const auto id = SDL_SensorGetDeviceInstanceID(index);
    if (id != -1) {
      return id;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the name associated with a sensor device.
   *
   * \param index the index of the sensor device that will be queried.
   *
   * \return the name of the sensor device; a null pointer is returned if the
   * name isn't available or if the index was invalid.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto name(const int index) noexcept -> czstring
  {
    return SDL_SensorGetDeviceName(index);
  }

  /**
   * \brief Returns the type associated with a sensor device.
   *
   * \param index the index of the sensor device that will be queried.
   *
   * \return the type of the sensor device.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto type(const int index) noexcept -> sensor_type
  {
    return static_cast<sensor_type>(SDL_SensorGetDeviceType(index));
  }

  /**
   * \brief Returns the non-portable type associated with a sensor.
   *
   * \param index the index of the sensor device that will be queried.
   *
   * \return a non-portable sensor type value; `std::nullopt` if the index is
   * invalid.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto non_portable_type(const int index) noexcept
      -> std::optional<int>
  {
    const auto type = SDL_SensorGetDeviceNonPortableType(index);
    if (type != -1) {
      return type;
    } else {
      return std::nullopt;
    }
  }

  /// \} End of index-based queries

  /**
   * \brief Updates the state of all open sensors.
   *
   * \note This is done automatically by the event loop if sensor events are
   * enabled.
   *
   * \since 5.2.0
   */
  static void update() noexcept
  {
    SDL_SensorUpdate();
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Locks access to the sensors for multi-threading.
   *
   * \note Refer to the SDL documentation for more details regarding this.
   *
   * \see SDL_LockSensors
   *
   * \since 5.2.0
   */
  static void lock() noexcept
  {
    SDL_LockSensors();
  }

  /**
   * \brief Unlocks access to the sensors.
   *
   * \note Refer to the SDL documentation for more details regarding this.
   *
   * \see SDL_UnlockSensors
   *
   * \since 5.2.0
   */
  static void unlock() noexcept
  {
    SDL_UnlockSensors();
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the amount of sensors currently attached to the system.
   *
   * \return the current amount of system sensors.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto count() noexcept -> int
  {
    return SDL_NumSensors();
  }

  /**
   * \brief Indicates whether or not the handle holds a non-null pointer.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit operator bool() const noexcept
  {
    return m_sensor != nullptr;
  }

  /**
   * \brief Returns a pointer to the associated SDL sensor.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated SDL sensor.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Sensor*
  {
    return m_sensor.get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_Sensor* sensor) noexcept
    {
      SDL_SensorClose(sensor);
    }
  };
  detail::pointer_manager<B, SDL_Sensor, deleter> m_sensor;
};

/**
 * \brief Returns a textual representation of a sensor instance.
 *
 * \tparam B the ownership semantics type of the sensor class.
 *
 * \param sensor the sensor that will be converted.
 *
 * \return a string that represents a sensor instance.
 *
 * \since 5.2.0
 */
template <typename B>
[[nodiscard]] auto to_string(const basic_sensor<B>& sensor) -> std::string
{
  const auto name = sensor.name();
  const std::string nameStr = name ? name : "N/A";
  return "[sensor | data: " + detail::address_of(sensor.get()) +
         ", id: " + detail::to_string(sensor.id()).value() +
         ", name: " + nameStr + "]";
}

/**
 * \brief Prints a textual representation of a sensor instance using a stream.
 *
 * \tparam B the ownership semantics type of the sensor class.
 *
 * \param stream the stream that will be used.
 * \param sensor the sensor that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.2.0
 */
template <typename B>
auto operator<<(std::ostream& stream, const basic_sensor<B>& sensor)
    -> std::ostream&
{
  stream << to_string(sensor);
  return stream;
}

/**
 * \brief Returns the standard gravity value.
 *
 * \return the standard gravity value.
 *
 * \since 5.2.0
 */
[[nodiscard]] constexpr auto standard_gravity() noexcept -> float
{
  return SDL_STANDARD_GRAVITY;
}

/**
 * \brief Indicates whether or not two sensor types values are equal.
 *
 * \param lhs the left-hand side sensor type.
 * \param rhs the right-hand side sensor type.
 *
 * \return `true` if the two sensor types are equal; `false` otherwise.
 *
 * \since 5.2.0
 */
[[nodiscard]] constexpr auto operator==(const sensor_type lhs,
                                        const SDL_SensorType rhs) noexcept
    -> bool
{
  return static_cast<SDL_SensorType>(lhs) == rhs;
}

/**
 * \copydoc operator==(const sensor_type, const SDL_SensorType)
 */
[[nodiscard]] constexpr auto operator==(const SDL_SensorType lhs,
                                        const sensor_type rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two sensor types values aren't equal.
 *
 * \param lhs the left-hand side sensor type.
 * \param rhs the right-hand side sensor type.
 *
 * \return `true` if the two sensor types aren't equal; `false` otherwise.
 *
 * \since 5.2.0
 */
[[nodiscard]] constexpr auto operator!=(const sensor_type lhs,
                                        const SDL_SensorType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * \copydoc operator!=(const sensor_type, const SDL_SensorType)
 */
[[nodiscard]] constexpr auto operator!=(const SDL_SensorType lhs,
                                        const sensor_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of input group

}  // namespace cen

#endif  // CENTURION_SENSOR_HEADER
