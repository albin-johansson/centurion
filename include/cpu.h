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
 * @brief Provides the @link centurion::CPU @endlink class.
 *
 * @file cpu.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_CPU_HEADER
#define CENTURION_CPU_HEADER

#include <SDL.h>

#include "centurion_api.h"

namespace centurion {

/**
 * @class CPU
 * @brief A utility class for obtaining information about the processor.
 * @details Use this class to determine whether or not the system processor
 * supports different instruction sets, the cache line size, amount of cores,
 * etc.
 * @headerfile cpu.h
 * @since 3.0.0
 */
class CPU final {
 public:
  CPU() = delete;

  /**
   * Returns the CPU L1 cache line size.
   *
   * @return the CPU L1 cache line size, in bytes.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int cache_line_size() noexcept;

  /**
   * Returns the amount of cores that the CPU has.
   *
   * @return the amount of cores that the CPU has.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int cores() noexcept;

  /**
   * Indicates whether or not the CPU has the RDTSC instruction.
   *
   * @return true if the CPU has the RDTSC instruction; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_rdtsc() noexcept;

  /**
   * Indicates whether or not the CPU has AltiVec features.
   *
   * @return true if the CPU has AltiVec features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_altivec() noexcept;

  /**
   * Indicates whether or not the CPU has MMX features.
   *
   * @return true if the CPU has MMX features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_mmx() noexcept;

  /**
   * Indicates whether or not the CPU has 3DNow! features.
   *
   * @return true if the CPU has 3DNow! features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_3dnow() noexcept;

  /**
   * Indicates whether or not the CPU has SSE features.
   *
   * @return true if the CPU has SSE features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_sse() noexcept;

  /**
   * Indicates whether or not the CPU has SSE2 features.
   *
   * @return true if the CPU has SSE2 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_sse2() noexcept;

  /**
   * Indicates whether or not the CPU has SSE3 features.
   *
   * @return true if the CPU has SSE3 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_sse3() noexcept;

  /**
   * Indicates whether or not the CPU has SSE4.1 features.
   *
   * @return true if the CPU has SSE4.1 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_sse41() noexcept;

  /**
   * Indicates whether or not the CPU has SSE4.2 features.
   *
   * @return true if the CPU has SSE4.2 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_sse42() noexcept;

  /**
   * Indicates whether or not the CPU has AVX features.
   *
   * @return true if the CPU has AVX features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_avx() noexcept;

  /**
   * Indicates whether or not the CPU has AVX2 features.
   *
   * @return true if the CPU has AVX2 features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_avx2() noexcept;

  /**
   * Indicates whether or not the CPU has AVX-512F (foundation) features.
   *
   * @return true if the CPU has AVX-512F (foundation) features; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_avx512f() noexcept;

  /**
   * Indicates whether or not the CPU has NEON (ARM SIMD) features.
   *
   * @return true if the CPU has NEON (ARM SIMD) features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_neon() noexcept;

  /**
   * Indicates whether or not the CPU has ARM SIMD (ARMv6+) features.
   *
   * @return true if the CPU has ARM SIMD (ARMv6+) features; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static bool has_arm_simd() noexcept;

  /**
   * Returns the minimum number of bytes to which a pointer must be
   * aligned to be compatible with SIMD instructions on the current CPU.
   *
   * @return the minimum number of bytes to which a pointer must be
   * aligned to be compatible with SIMD instructions.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static std::size_t simd_alignment() noexcept;

  /**
   * Indicates whether or not the CPU uses big-endian byte ordering.
   *
   * @return true if the CPU uses big-endian byte ordering; false otherwise.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  constexpr static bool is_big_endian() noexcept
  {
    return SDL_BYTEORDER == SDL_BIG_ENDIAN;
  }

  /**
   * Indicates whether or not the CPU uses little-endian byte ordering.
   *
   * @return true if the CPU uses little-endian byte ordering; false otherwise.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  constexpr static bool is_little_endian() noexcept
  {
    return SDL_BYTEORDER == SDL_LIL_ENDIAN;
  }
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "cpu.cpp"
#endif

#endif  // CENTURION_CPU_HEADER