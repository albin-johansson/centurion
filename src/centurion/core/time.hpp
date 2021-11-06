#ifndef CENTURION_TIME_HEADER
#define CENTURION_TIME_HEADER

#include <SDL.h>

#include <chrono>  // duration
#include <ratio>   // milli, micro, nano

#include "integers.hpp"

namespace cen {

/// \addtogroup core
/// \{

/// \name Time (std::chrono) aliases
/// \{

/// \brief Templated alias for durations in seconds.
template <typename T>
using seconds = std::chrono::duration<T>;

/// \brief Templated alias for durations in milliseconds.
template <typename T>
using milliseconds = std::chrono::duration<T, std::milli>;

/// \brief Templated alias for durations in microseconds.
template <typename T>
using microseconds = std::chrono::duration<T, std::micro>;

/// \brief Templated alias for durations in nanoseconds.
template <typename T>
using nanoseconds = std::chrono::duration<T, std::nano>;

/// \brief Templated alias for durations in minutes.
template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

/* u32-based convenience chrono aliases*/
using u32_s = seconds<u32>;
using u32_ms = milliseconds<u32>;
using u32_us = microseconds<u32>;
using u32_ns = nanoseconds<u32>;

/* u64-based convenience chrono aliases */
using u64_s = seconds<u64>;
using u64_ms = milliseconds<u64>;
using u64_us = microseconds<u64>;
using u64_ns = nanoseconds<u64>;

/// \} End of time (std::chrono) aliases

namespace literals {
inline namespace time_literals {

namespace legacy {

[[nodiscard]] constexpr auto operator"" _ns(const ulonglong value) noexcept(noexcept(u32_ns{}))
    -> u32_ns
{
  return u32_ns{static_cast<u32>(value)};
}

[[nodiscard]] constexpr auto operator"" _us(const ulonglong value) noexcept(noexcept(u32_us{}))
    -> u32_us
{
  return u32_us{static_cast<u32>(value)};
}

[[nodiscard]] constexpr auto operator"" _ms(const ulonglong value) noexcept(noexcept(u32_ms{}))
    -> u32_ms
{
  return u32_ms{static_cast<u32>(value)};
}

[[nodiscard]] constexpr auto operator"" _s(const ulonglong value) noexcept(noexcept(u32_s{}))
    -> u32_s
{
  return u32_s{static_cast<u32>(value)};
}

}  // namespace legacy

[[nodiscard]] constexpr auto operator"" _ns(const ulonglong value) noexcept(noexcept(u64_ns{}))
    -> u64_ns
{
  return u64_ns{static_cast<u64>(value)};
}

[[nodiscard]] constexpr auto operator"" _us(const ulonglong value) noexcept(noexcept(u64_us{}))
    -> u64_us
{
  return u64_us{static_cast<u64>(value)};
}

[[nodiscard]] constexpr auto operator"" _ms(const ulonglong value) noexcept(noexcept(u64_ms{}))
    -> u64_ms
{
  return u64_ms{static_cast<u64>(value)};
}

[[nodiscard]] constexpr auto operator"" _s(const ulonglong value) noexcept(noexcept(u64_s{}))
    -> u64_s
{
  return u64_s{static_cast<u64>(value)};
}

}  // namespace time_literals
}  // namespace literals

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_TIME_HEADER
