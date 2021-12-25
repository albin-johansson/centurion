#ifndef CENTURION_INPUT_SENSOR_HPP_
#define CENTURION_INPUT_SENSOR_HPP_

#include <SDL.h>

#include <array>     // array
#include <cstddef>   // size_t
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, to_string

#include "../common.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup input
/// \{

/**
 * \brief Provides values that represent different sensor types.
 *
 * \see SDL_SensorType
 *
 * \since 5.2.0
 */
enum class sensor_type {
  invalid = SDL_SENSOR_INVALID,      ///< Invalid sensor
  unknown = SDL_SENSOR_UNKNOWN,      ///< Unknown sensor
  accelerometer = SDL_SENSOR_ACCEL,  ///< Accelerometer
  gyroscope = SDL_SENSOR_GYRO        ///< Gyroscope
};

/// \brief Used for unique sensor instance identifiers.
/// \since 5.2.0
using sensor_id = SDL_SensorID;

template <typename T>
class basic_sensor;

/// \brief Represents an owning sensor device.
/// \since 5.2.0
using sensor = basic_sensor<detail::OwnerTag>;

/// \brief Represents a non-owning sensor device.
/// \since 5.2.0
using sensor_handle = basic_sensor<detail::HandleTag>;

/**
 * \brief Represents a sensor device.
 *
 * \ownerhandle `sensor`/`sensor_handle`
 *
 * \see `sensor`
 * \see `sensor_handle`
 *
 * \since 5.2.0
 */
template <typename T>
class basic_sensor final {
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a sensor instance based on an existing pointer.
   *
   * \note The created instance will claim ownership of the supplied pointer if the class
   * has owning semantics.
   *
   * \param sensor a pointer to the SDL sensor data.
   *
   * \throws cen_error if the supplied pointer is null and the class has owning semantics.
   *
   * \since 5.2.0
   */
  explicit basic_sensor(MaybeOwner<SDL_Sensor*> sensor) noexcept(detail::is_handle<T>)
      : m_sensor{sensor}
  {
    if constexpr (detail::is_owner<T>) {
      if (!m_sensor) {
        throw Error{"Null sensor pointer!"};
      }
    }
  }

  /**
   * \brief Creates an owning sensor instance based on a device index.
   *
   * \param index the device index of the sensor.
   *
   * \throws sdl_error if the sensor cannot be opened.
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit basic_sensor(const int index = 0) : m_sensor{SDL_SensorOpen(index)}
  {
    if (!m_sensor) {
      throw SDLError{};
    }
  }

  /**
   * \brief Creates a sensor handle based on an owning sensor.
   *
   * \param owner the associated owning sensor.
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit basic_sensor(const sensor& owner) noexcept : m_sensor{owner.get()}
  {}

  /// \} End of construction

  /**
   * \brief Updates the state of all open sensors.
   *
   * \note This is done automatically by the event loop if sensor events are enabled.
   *
   * \since 5.2.0
   */
  static void update() noexcept { SDL_SensorUpdate(); }

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
  static void lock() noexcept { SDL_LockSensors(); }

  /**
   * \brief Unlocks access to the sensors.
   *
   * \note Refer to the SDL documentation for more details regarding this.
   *
   * \see SDL_UnlockSensors
   *
   * \since 5.2.0
   */
  static void unlock() noexcept { SDL_UnlockSensors(); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns the amount of sensors currently attached to the system.
   *
   * \return the current amount of system sensors.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto count() noexcept -> int { return SDL_NumSensors(); }

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
   * \return the name of the sensor device; a null pointer is returned if the name isn't
   * available.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto name() const noexcept -> const char*
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
   * \tparam Size the number of data elements, varies from sensor to sensor.
   *
   * \return the data associated with the sensor; `std::nullopt` if something goes wrong.
   *
   * \since 5.2.0
   */
  template <std::size_t Size>
  [[nodiscard]] auto data() const noexcept -> std::optional<std::array<float, Size>>
  {
    std::array<float, Size> array{};
    if (SDL_SensorGetData(m_sensor, array.data(), isize(array)) != -1) {
      return array;
    }
    else {
      return std::nullopt;
    }
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
  [[nodiscard]] auto get() const noexcept -> SDL_Sensor* { return m_sensor.get(); }

  /// \} End of instance-based queries

  /// \name Index-based queries
  /// \{

  /**
   * \brief Returns the unique identifier associated with a sensor instance.
   *
   * \param index the index of the sensor device that will be queried.
   *
   * \return the unique instance ID associated with a sensor; `std::nullopt` if the index
   * is invalid.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto id(const int index) noexcept -> std::optional<sensor_id>
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
   * \brief Returns the name associated with a sensor device.
   *
   * \param index the index of the sensor device that will be queried.
   *
   * \return the name of the sensor device; a null pointer is returned if the name isn't
   * available or if the index was invalid.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto name(const int index) noexcept -> const char*
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
   * \return a non-portable sensor type value; `std::nullopt` if the index is invalid.
   *
   * \since 5.2.0
   */
  [[nodiscard]] static auto non_portable_type(const int index) noexcept -> std::optional<int>
  {
    const auto type = SDL_SensorGetDeviceNonPortableType(index);
    if (type != -1) {
      return type;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of index-based queries

  /// \name Conversions
  /// \{

  /**
   * \brief Indicates whether or not the handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return m_sensor != nullptr;
  }

  /// \} End of conversions

 private:
  detail::Pointer<T, SDL_Sensor> m_sensor;
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied sensor type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(sensor_type::gyroscope) == "gyroscope"`.
 *
 * \param type the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
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
      throw Error{"Did not recognize sensor type!"};
  }
}

/**
 * \brief Returns a textual representation of a sensor instance.
 *
 * \param sensor the sensor that will be converted.
 *
 * \return a string that represents a sensor instance.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_sensor<T>& sensor) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("sensor{{data: {}, id: {}, name: {}}}",
                     detail::address_of(sensor.get()),
                     sensor.id(),
                     str_or_na(sensor.name()));
#else
  return "sensor{data: " + detail::address_of(sensor.get()) +
         ", id: " + std::to_string(sensor.id()) + ", name: " + str_or_na(sensor.name()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a sensor type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the enumerator that will be printed.
 *
 * \see `to_string(sensor_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const sensor_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/**
 * \brief Prints a textual representation of a sensor instance using a stream.
 *
 * \param stream the stream that will be used.
 * \param sensor the sensor that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.2.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_sensor<T>& sensor) -> std::ostream&
{
  return stream << to_string(sensor);
}

/// \} End of streaming

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

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_INPUT_SENSOR_HPP_
