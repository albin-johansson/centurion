#ifndef CENTURION_INTEGERS_HEADER
#define CENTURION_INTEGERS_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \typedef u64
 *
 * \brief Alias for a 64-bit unsigned integer.
 */
using u64 = Uint64;

/**
 * \typedef u32
 *
 * \brief Alias for a 32-bit unsigned integer.
 */
using u32 = Uint32;

/**
 * \typedef u16
 *
 * \brief Alias for a 16-bit unsigned integer.
 */
using u16 = Uint16;

/**
 * \typedef u8
 *
 * \brief Alias for an 8-bit unsigned integer.
 */
using u8 = Uint8;

/**
 * \typedef i64
 *
 * \brief Alias for a 64-bit signed integer.
 */
using i64 = Sint64;

/**
 * \typedef i32
 *
 * \brief Alias for a 32-bit signed integer.
 */
using i32 = Sint32;

/**
 * \typedef i16
 *
 * \brief Alias for a 16-bit signed integer.
 */
using i16 = Sint16;

/**
 * \typedef i8
 *
 * \brief Alias for an 8-bit signed integer.
 */
using i8 = Sint8;

// clang-format off

/**
 * \brief Obtains the size of a container as an `int`.
 *
 * \tparam T a "container" that provides a `size()` member function.
 *
 * \param container the container to query the size of.
 *
 * \return the size of the container as an `int` value.
 *
 * \since 5.3.0
 */
template <typename T>
[[nodiscard]] constexpr auto isize(const T& container) noexcept(noexcept(container.size()))
    -> int
{
  return static_cast<int>(container.size());
}

// clang-format on

namespace literals {

/**
 * \brief Creates an 8-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return an 8-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u8(unsigned long long value) noexcept
    -> u8
{
  return static_cast<u8>(value);
}

/**
 * \brief Creates a 16-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 16-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u16(unsigned long long value) noexcept
    -> u16
{
  return static_cast<u16>(value);
}

/**
 * \brief Creates a 32-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 32-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u32(unsigned long long value) noexcept
    -> u32
{
  return static_cast<u32>(value);
}

/**
 * \brief Creates a 64-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 64-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u64(unsigned long long value) noexcept
    -> u64
{
  return static_cast<u64>(value);
}

/**
 * \brief Creates an 8-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return an 8-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i8(unsigned long long value) noexcept
    -> i8
{
  return static_cast<i8>(value);
}

/**
 * \brief Creates a 16-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 16-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i16(unsigned long long value) noexcept
    -> i16
{
  return static_cast<i16>(value);
}

/**
 * \brief Creates a 32-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 32-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i32(unsigned long long value) noexcept
    -> i32
{
  return static_cast<i32>(value);
}

/**
 * \brief Creates a 64-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 64-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i64(unsigned long long value) noexcept
    -> i64
{
  return static_cast<i64>(value);
}

}  // namespace literals
}  // namespace cen

#endif  // CENTURION_INTEGERS_HEADER
