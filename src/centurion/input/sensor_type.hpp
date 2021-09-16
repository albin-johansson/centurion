#ifndef CENTURION_SENSOR_TYPE_HEADER
#define CENTURION_SENSOR_TYPE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup input
/// \{

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
      throw cen_error{"Did not recognize sensor type!"};
  }
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

/// \} End of streaming

/// \name Sensor type comparison operators
/// \{

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
                                        const SDL_SensorType rhs) noexcept -> bool
{
  return static_cast<SDL_SensorType>(lhs) == rhs;
}

/// \copydoc operator==(const sensor_type, const SDL_SensorType)
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
                                        const SDL_SensorType rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(const sensor_type, const SDL_SensorType)
[[nodiscard]] constexpr auto operator!=(const SDL_SensorType lhs,
                                        const sensor_type rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of sensor type comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_SENSOR_TYPE_HEADER
