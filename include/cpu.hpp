/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
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

/**
 * @file cpu.hpp
 *
 * @brief Provides an API for querying information about the processor.
 *
 * @details Provides information about the system processor, such as whether it
 * supports different instruction sets, the cache line size, amount of cores,
 * etc.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_CPU_HEADER
#define CENTURION_CPU_HEADER

#include <SDL.h>

#include "centurion_api.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * @namespace cen::cpu
 *
 * @ingroup system
 *
 * @brief Provides methods for obtaining information about the processor.
 *
 * @since 5.0.0
 *
 * @headerfile cpu.hpp
 */
namespace cen::cpu {

/**
 * @brief Returns the CPU L1 cache line size.
 *
 * @return the L1 cache line size, in bytes.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline auto cache_line_size() noexcept -> int
{
  return SDL_GetCPUCacheLineSize();
}

/**
 * @brief Returns the amount of cores that the CPU has.
 *
 * @return the amount of cores.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline auto cores() noexcept -> int
{
  return SDL_GetCPUCount();
}

/**
 * @brief Indicates whether or not the CPU has the RDTSC instruction.
 *
 * @return `true` if the CPU has the RDTSC instruction; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_rdtsc() noexcept -> bool
{
  return SDL_HasRDTSC();
}

/**
 * @brief Indicates whether or not the CPU has AltiVec features.
 *
 * @return `true` if the CPU has AltiVec features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_altivec() noexcept -> bool
{
  return SDL_HasAltiVec();
}

/**
 * @brief Indicates whether or not the CPU has MMX features.
 *
 * @return `true` if the CPU has MMX features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_mmx() noexcept -> bool
{
  return SDL_HasMMX();
}

/**
 * @brief Indicates whether or not the CPU has 3DNow! features.
 *
 * @return `true` if the CPU has 3DNow! features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_3dnow() noexcept -> bool
{
  return SDL_Has3DNow();
}

/**
 * @brief Indicates whether or not the CPU has SSE features.
 *
 * @return `true` if the CPU has SSE features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_sse() noexcept -> bool
{
  return SDL_HasSSE();
}

/**
 * @brief Indicates whether or not the CPU has SSE2 features.
 *
 * @return `true` if the CPU has SSE2 features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_sse2() noexcept -> bool
{
  return SDL_HasSSE2();
}
/**
 * @brief Indicates whether or not the CPU has SSE3 features.
 *
 * @return `true` if the CPU has SSE3 features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_sse3() noexcept -> bool
{
  return SDL_HasSSE3();
}

/**
 * @brief Indicates whether or not the CPU has SSE4.1 features.
 *
 * @return `true` if the CPU has SSE4.1 features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_sse41() noexcept -> bool
{
  return SDL_HasSSE41();
}

/**
 * @brief Indicates whether or not the CPU has SSE4.2 features.
 *
 * @return `true` if the CPU has SSE4.2 features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_sse42() noexcept -> bool
{
  return SDL_HasSSE42();
}

/**
 * @brief Indicates whether or not the CPU has AVX features.
 *
 * @return `true` if the CPU has AVX features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_avx() noexcept -> bool
{
  return SDL_HasAVX();
}

/**
 * @brief Indicates whether or not the CPU has AVX2 features.
 *
 * @return `true` if the CPU has AVX2 features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_avx2() noexcept -> bool
{
  return SDL_HasAVX2();
}

/**
 * @brief Indicates whether or not the CPU has AVX-512F (foundation) features.
 *
 * @return `true` if the CPU has AVX-512F (foundation) features; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_avx512f() noexcept -> bool
{
  return SDL_HasAVX512F();
}

/**
 * @brief Indicates whether or not the CPU has NEON (ARM SIMD) features.
 *
 * @return `true` if the CPU has NEON (ARM SIMD) features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_neon() noexcept -> bool
{
  return SDL_HasNEON();
}

/**
 * @brief Indicates whether or not the CPU has ARM SIMD (ARMv6+) features.
 *
 * @return `true` if the CPU has ARM SIMD (ARMv6+) features; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto has_arm_simd() noexcept -> bool
{
  return SDL_HasARMSIMD();
}

/**
 * @brief Returns the minimum number of bytes to which a pointer must be
 * aligned to be compatible with SIMD instructions on the current CPU.
 *
 * @return the minimum number of bytes to which a pointer must be
 * aligned to be compatible with SIMD instructions.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline auto simd_alignment() noexcept -> std::size_t
{
  return SDL_SIMDGetAlignment();
}

/**
 * @brief Indicates whether or not the CPU uses big-endian byte ordering.
 *
 * @return `true` if the CPU uses big-endian byte ordering; `false` otherwise.
 *
 * @since 3.1.0
 */
[[nodiscard]] inline constexpr auto is_big_endian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_BIG_ENDIAN;
}

/**
 * @brief Indicates whether or not the CPU uses little-endian byte ordering.
 *
 * @return `true` if the CPU uses little-endian byte ordering; `false`
 * otherwise.
 *
 * @since 3.1.0
 */
[[nodiscard]] inline constexpr auto is_little_endian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_LIL_ENDIAN;
}

}  // namespace cen::cpu

#endif  // CENTURION_CPU_HEADER