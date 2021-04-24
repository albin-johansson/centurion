#ifndef CENTURION_TIME_HEADER
#define CENTURION_TIME_HEADER

#include <chrono>  // duration
#include <ratio>   // milli, micro, nano

#include "integers.hpp"

namespace cen {

/// \addtogroup core
/// \{

/// \name Time (std::chrono) aliases
/// \{

/**
 * \typedef seconds
 *
 * \brief Templated alias for durations in seconds.
 */
template <typename T>
using seconds = std::chrono::duration<T>;

/**
 * \typedef milliseconds
 *
 * \brief Templated alias for durations in milliseconds.
 */
template <typename T>
using milliseconds = std::chrono::duration<T, std::milli>;

/**
 * \typedef microseconds
 *
 * \brief Templated alias for durations in microseconds.
 */
template <typename T>
using microseconds = std::chrono::duration<T, std::micro>;

/**
 * \typedef nanoseconds
 *
 * \brief Templated alias for durations in nanoseconds.
 */
template <typename T>
using nanoseconds = std::chrono::duration<T, std::nano>;

/**
 * \typedef minutes
 *
 * \brief Templated alias for durations in minutes.
 */
template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

/// \} End of time (std::chrono) aliases

namespace literals {

constexpr auto operator"" _ns(const unsigned long long int value) noexcept
    -> nanoseconds<u32>
{
  return nanoseconds<u32>{value};
}

constexpr auto operator"" _us(const unsigned long long int value) noexcept
    -> microseconds<u32>
{
  return microseconds<u32>{value};
}

constexpr auto operator"" _ms(const unsigned long long int value) noexcept
    -> milliseconds<u32>
{
  return milliseconds<u32>{value};
}

constexpr auto operator"" _s(const unsigned long long int value) noexcept -> seconds<u32>
{
  return seconds<u32>{value};
}

}  // namespace literals

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_TIME_HEADER
