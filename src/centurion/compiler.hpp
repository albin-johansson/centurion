#ifndef CENTURION_COMPILER_HEADER
#define CENTURION_COMPILER_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup compiler
/// \{

/**
 * \brief Indicates whether or not the compiler is MSVC.
 *
 * \return `true` if MSVC is detected as the current compiler; `false`
 * otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_msvc() noexcept -> bool
{
#ifdef _MSC_VER
  return true;
#else
  return false;
#endif  // _MSC_VER
}

/**
 * \brief Indicates whether or not the compiler is GCC.
 *
 * \return `true` if GCC is detected as the current compiler; `false`
 * otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_gcc() noexcept -> bool
{
#ifdef __GNUC__
  return true;
#else
  return false;
#endif  // __GNUC__
}

/**
 * \brief Indicates whether or not the compiler is Clang.
 *
 * \return `true` if Clang is detected as the current compiler; `false`
 * otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_clang() noexcept -> bool
{
#ifdef __clang__
  return true;
#else
  return false;
#endif  // __clang__
}

/**
 * \brief Indicates whether or not the compiler is Emscripten.
 *
 * \return `true` if Emscripten is detected as the current compiler; `false`
 * otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_emscripten() noexcept -> bool
{
#ifdef __EMSCRIPTEN__
  return true;
#else
  return false;
#endif  // __EMSCRIPTEN__
}

/**
 * \brief Indicates whether or not the compiler is Intel C++.
 *
 * \return `true` if Intel C++ is detected as the current compiler; `false`
 * otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_intel_cpp() noexcept -> bool
{
#ifdef __INTEL_COMPILER
  return true;
#else
  return false;
#endif  // __INTEL_COMPILER
}

/// \} End of compiler group

}  // namespace cen

#endif  // CENTURION_COMPILER_HEADER
