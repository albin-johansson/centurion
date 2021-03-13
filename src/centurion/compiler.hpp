#ifndef CENTURION_COMPILER_HEADER
#define CENTURION_COMPILER_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup system
/// \{

[[nodiscard]] constexpr auto on_msvc() noexcept -> bool
{
#ifdef _MSC_VER
  return true;
#else
  return false;
#endif  // _MSC_VER
}

[[nodiscard]] constexpr auto on_gcc() noexcept -> bool
{
#ifdef __GNUC__
  return true;
#else
  return false;
#endif  // __GNUC__
}

[[nodiscard]] constexpr auto on_clang() noexcept -> bool
{
#ifdef __clang__
  return true;
#else
  return false;
#endif  // __clang__
}

[[nodiscard]] constexpr auto on_emscripten() noexcept -> bool
{
#ifdef __EMSCRIPTEN__
  return true;
#else
  return false;
#endif  // __EMSCRIPTEN__
}

[[nodiscard]] constexpr auto on_intel_cpp() noexcept -> bool
{
#ifdef __INTEL_COMPILER
  return true;
#else
  return false;
#endif  // __INTEL_COMPILER
}

/// \} End of system group

}  // namespace cen

#endif  // CENTURION_COMPILER_HEADER
