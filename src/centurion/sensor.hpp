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

/**
 * \ingroup input
 * \defgroup sensor Sensor
 *
 * \brief Provides the sensor input API.
 */

/// \addtogroup sensor
/// \{

using sensor_id = SDL_SensorID;

/**
 * \brief Returns the standard gravity value.
 *
 * \return the standard gravity.
 */
[[nodiscard]] constexpr auto standard_gravity() noexcept -> float
{
  return SDL_STANDARD_GRAVITY;
}

/**
 * \brief Represents different sensor types.
 *
 * \see `SDL_SensorType`
 */
enum class sensor_type
{
  invalid = SDL_SENSOR_INVALID,      ///< Invalid sensor.
  unknown = SDL_SENSOR_UNKNOWN,      ///< Unknown sensor.
  accelerometer = SDL_SENSOR_ACCEL,  ///< Accelerometer.
  gyroscope = SDL_SENSOR_GYRO        ///< Gyroscope.
};

/// \name Sensor type functions
/// \{

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

/// \} End of sensor type functions

template <typename T>
class basic_sensor;

using sensor = basic_sensor<detail::owner_tag>;          ///< An owning sensor.
using sensor_handle = basic_sensor<detail::handle_tag>;  ///< A non-owning sensor.

/**
 * \brief Represents a sensor device.
 *
 * \ownerhandle `sensor`/`sensor_handle`
 *
 * \see `sensor`
 * \see `sensor_handle`
 *
 * \see `SDL_Sensor`
 */
template <typename T>
class basic_sensor final
{
 public:
  using device_index = int;
  using size_type = std::size_t;

  template <size_type Size>
  using data_type = std::array<float, Size>;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a sensor instance based on an existing SDL sensor.
   *
   * \details Ownership of the pointer is claimed if the class has owning semantics.
   *
   * \param sensor a pointer to the SDL sensor data.
   *
   * \throws exception if the pointer is null and the sensor has owning semantics.
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

  /**
   * \brief Creates an owning sensor instance based on a device index.
   *
   * \param index the device index of the sensor.
   *
   * \throws sdl_error if the sensor cannot be opened.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_sensor(const device_index index = 0) : mSensor{SDL_SensorOpen(index)}
  {
    if (!mSensor) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle to an owning sensor.
   *
   * \param owner the owning sensor.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_sensor(const sensor& owner) noexcept : mSensor{owner.get()}
  {}

  /// \} End of construction

  /// \name General information
  /// \{

  /**
   * \brief Returns the name of the sensor.
   *
   * \return the sensor name; a null string is returned upon failure.
   */
  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_SensorGetName(mSensor);
  }

  /**
   * \brief Returns the name of a sensor.
   *
   * \param index the device index of the sensor that will be queried.
   *
   * \return the sensor name; a null string is returned upon failure.
   */
  [[nodiscard]] static auto name(const device_index index) noexcept -> const char*
  {
    return SDL_SensorGetDeviceName(index);
  }

  /**
   * \brief Returns the type of the sensor.
   *
   * \return the sensor type.
   */
  [[nodiscard]] auto type() const noexcept -> sensor_type
  {
    return static_cast<sensor_type>(SDL_SensorGetType(mSensor));
  }

  /**
   * \brief Returns the type of a sensor.
   *
   * \param index the device index of the sensor that will be queried.
   *
   * \return the sensor type.
   */
  [[nodiscard]] static auto type(const device_index index) noexcept -> sensor_type
  {
    return static_cast<sensor_type>(SDL_SensorGetDeviceType(index));
  }

  /**
   * \brief Returns the non-portable type of the sensor.
   *
   * \return a non-portable sensor type; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto non_portable_type() const noexcept -> std::optional<int>
  {
    const auto type = SDL_SensorGetNonPortableType(mSensor);
    if (type != -1) {
      return type;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the non-portable type of a sensor.
   *
   * \param index the device index of the sensor that will be queried.
   *
   * \return a non-portable sensor type; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto non_portable_type(const device_index index) noexcept
      -> std::optional<int>
  {
    const auto type = SDL_SensorGetDeviceNonPortableType(index);
    if (type != -1) {
      return type;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of general information

  /// \name Queries
  /// \{

  /**
   * \brief Returns the identifier associated with the sensor.
   *
   * \return the sensor identifier; an empty optional is returned upon failure.
   */
  [[nodiscard]] auto id() const noexcept -> std::optional<sensor_id>
  {
    const auto id = SDL_SensorGetInstanceID(mSensor);
    if (id != -1) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the identifier associated with a sensor.
   *
   * \param index the device index of the sensor that will be queried.
   *
   * \return the sensor identifier; an empty optional is returned upon failure.
   */
  [[nodiscard]] static auto id(const device_index index) noexcept -> std::optional<sensor_id>
  {
    const auto id = SDL_SensorGetDeviceInstanceID(index);
    if (id != -1) {
      return id;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns sensor-dependent data.
   *
   * \tparam Size the number of data elements, varies from sensor to sensor.
   *
   * \return the data associated with the sensor; an empty optional is returned upon failure.
   */
  template <size_type Size>
  [[nodiscard]] auto data() const noexcept -> std::optional<data_type<Size>>
  {
    data_type<Size> array{};
    if (SDL_SensorGetData(mSensor, array.data(), isize(array)) != -1) {
      return array;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of queries

  /// \name Sensor management
  /// \{

  /**
   * \brief Updates the state of all open sensors.
   *
   * \note This is done automatically by the event loop if sensor events are enabled.
   */
  static void update() noexcept { SDL_SensorUpdate(); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Locks access to all sensors.
   */
  static void lock() noexcept { SDL_LockSensors(); }

  /**
   * \brief Unlocks access to all sensors.
   */
  static void unlock() noexcept { SDL_UnlockSensors(); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of sensor management

  /// \name Global sensor information
  /// \{

  /**
   * \brief Returns the amount of sensors currently attached to the system.
   *
   * \return the system sensor count.
   */
  [[nodiscard]] static auto count() noexcept -> int { return SDL_NumSensors(); }

  /// \} End of global sensor information

  /// \name Misc functions
  /// \{

  [[nodiscard]] auto get() const noexcept -> SDL_Sensor* { return mSensor.get(); }

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mSensor != nullptr;
  }

  /// \} End of misc functions

 private:
  detail::pointer<T, SDL_Sensor> mSensor;
};

/// \name Sensor functions
/// \{

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

/// \} End of sensor functions

/// \} End of group sensor

}  // namespace cen

#endif  // CENTURION_SENSOR_HPP_
