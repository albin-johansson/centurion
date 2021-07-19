#ifndef CENTURION_SENSOR_TYPE_HEADER
#define CENTURION_SENSOR_TYPE_HEADER

#include <SDL.h>

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
