#ifndef CENTURION_CPU_HEADER
#define CENTURION_CPU_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "../core/integers.hpp"

namespace cen {

/// \addtogroup system
/// \{

/**
 * \class simd_block
 *
 * \brief Represents a block of memory, allocated in SIMD-friendly way.
 *
 * \since 5.2.0
 */
class simd_block final
{
 public:
  /**
   * \brief Allocates a block of SIMD-friendly memory.
   *
   * \note The allocation might fail, in which case the internal pointer is null.
   *
   * \param size the size of the memory block.
   *
   * \since 5.2.0
   */
  explicit simd_block(const usize size) noexcept : m_data{SDL_SIMDAlloc(size)}
  {}

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Reallocates the associated memory block.
   *
   * \param size the size of the new memory block.
   *
   * \since 5.2.0
   */
  void reallocate(const usize size) noexcept
  {
    /* We temporarily release the ownership of the pointer in order to avoid a double
       delete, since the reallocation will free the previously allocated memory. */
    auto* ptr = m_data.release();
    m_data.reset(SDL_SIMDRealloc(ptr, size));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns a pointer to the associated memory block.
   *
   * \return a pointer to the memory block.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto data() noexcept -> void*
  {
    return m_data.get();
  }

  /// \copydoc data()
  [[nodiscard]] auto data() const noexcept -> const void*
  {
    return m_data.get();
  }

  /**
   * \brief Returns a reinterpreted pointer to the associated memory block.
   *
   * \warning It's your responsibility to make sure to avoid any potential undefined
   * behaviour using this function, since it uses `reinterpret_cast`.
   *
   * \tparam T the type used when reinterpreting the internal pointer.
   *
   * \return a pointer to the associated memory block.
   *
   * \since 5.2.0
   */
  template <typename T>
  [[nodiscard]] auto cast_data() noexcept -> T*
  {
    return reinterpret_cast<T*>(data());
  }

  /// \copydoc cast_data()
  template <typename T>
  [[nodiscard]] auto cast_data() const noexcept -> const T*
  {
    return reinterpret_cast<const T*>(data());
  }

  /**
   * \brief Indicates whether or not the internal pointer isn't null.
   *
   * \return `true` if the internal pointer is non-null; `false` otherwise.
   *
   * \since 5.2.0
   */
  explicit operator bool() const noexcept
  {
    return m_data.operator bool();
  }

 private:
  struct deleter final
  {
    void operator()(void* ptr) noexcept
    {
      SDL_SIMDFree(ptr);
    }
  };
  std::unique_ptr<void, deleter> m_data;
};

/// \} End of group system

}  // namespace cen

/**
 * \namespace cen::cpu
 *
 * \brief Provides methods for obtaining information about the processor.
 *
 * \since 5.0.0
 */
namespace cen::cpu {

/// \addtogroup system
/// \{

/// \name CPU functions
/// \{

/**
 * \brief Returns the CPU L1 cache line size.
 *
 * \return the L1 cache line size, in bytes.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto cache_line_size() noexcept -> int
{
  return SDL_GetCPUCacheLineSize();
}

/**
 * \brief Returns the amount of cores that the CPU has.
 *
 * \return the amount of cores.
 *
 * \since 3.0.0
 */
[[nodiscard]] inline auto cores() noexcept -> int
{
  return SDL_GetCPUCount();
}

/**
 * \brief Indicates whether or not the CPU has the RDTSC instruction.
 *
 * \return `true` if the CPU has the RDTSC instruction; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_rdtsc() noexcept -> bool
{
  return SDL_HasRDTSC();
}

/**
 * \brief Indicates whether or not the CPU has AltiVec features.
 *
 * \return `true` if the CPU has AltiVec features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_altivec() noexcept -> bool
{
  return SDL_HasAltiVec();
}

/**
 * \brief Indicates whether or not the CPU has MMX features.
 *
 * \return `true` if the CPU has MMX features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_mmx() noexcept -> bool
{
  return SDL_HasMMX();
}

/**
 * \brief Indicates whether or not the CPU has 3DNow! features.
 *
 * \return `true` if the CPU has 3DNow! features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_3dnow() noexcept -> bool
{
  return SDL_Has3DNow();
}

/**
 * \brief Indicates whether or not the CPU has SSE features.
 *
 * \return `true` if the CPU has SSE features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_sse() noexcept -> bool
{
  return SDL_HasSSE();
}

/**
 * \brief Indicates whether or not the CPU has SSE2 features.
 *
 * \return `true` if the CPU has SSE2 features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_sse2() noexcept -> bool
{
  return SDL_HasSSE2();
}
/**
 * \brief Indicates whether or not the CPU has SSE3 features.
 *
 * \return `true` if the CPU has SSE3 features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_sse3() noexcept -> bool
{
  return SDL_HasSSE3();
}

/**
 * \brief Indicates whether or not the CPU has SSE4.1 features.
 *
 * \return `true` if the CPU has SSE4.1 features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_sse41() noexcept -> bool
{
  return SDL_HasSSE41();
}

/**
 * \brief Indicates whether or not the CPU has SSE4.2 features.
 *
 * \return `true` if the CPU has SSE4.2 features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_sse42() noexcept -> bool
{
  return SDL_HasSSE42();
}

/**
 * \brief Indicates whether or not the CPU has AVX features.
 *
 * \return `true` if the CPU has AVX features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_avx() noexcept -> bool
{
  return SDL_HasAVX();
}

/**
 * \brief Indicates whether or not the CPU has AVX2 features.
 *
 * \return `true` if the CPU has AVX2 features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_avx2() noexcept -> bool
{
  return SDL_HasAVX2();
}

/**
 * \brief Indicates whether or not the CPU has AVX-512F (foundation) features.
 *
 * \return `true` if the CPU has AVX-512F (foundation) features; `false`
 * otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_avx512f() noexcept -> bool
{
  return SDL_HasAVX512F();
}

/**
 * \brief Indicates whether or not the CPU has NEON (ARM SIMD) features.
 *
 * \return `true` if the CPU has NEON (ARM SIMD) features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_neon() noexcept -> bool
{
  return SDL_HasNEON();
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

/**
 * \brief Indicates whether or not the CPU has ARM SIMD (ARMv6+) features.
 *
 * \return `true` if the CPU has ARM SIMD (ARMv6+) features; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto has_arm_simd() noexcept -> bool
{
  return SDL_HasARMSIMD();
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

/**
 * \brief Returns the minimum number of bytes to which a pointer must be aligned to be
 * compatible with SIMD instructions on the current CPU.
 *
 * \return the minimum number of bytes to which a pointer must be aligned to be compatible
 * with SIMD instructions.
 *
 * \since 4.0.0
 */
[[nodiscard]] inline auto simd_alignment() noexcept -> usize
{
  return SDL_SIMDGetAlignment();
}

/**
 * \brief Indicates whether or not the CPU uses big-endian byte ordering.
 *
 * \return `true` if the CPU uses big-endian byte ordering; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto is_big_endian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_BIG_ENDIAN;
}

/**
 * \brief Indicates whether or not the CPU uses little-endian byte ordering.
 *
 * \return `true` if the CPU uses little-endian byte ordering; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto is_little_endian() noexcept -> bool
{
  return SDL_BYTEORDER == SDL_LIL_ENDIAN;
}

/// \} End of CPU functions

/// \} End of group system

}  // namespace cen::cpu

#endif  // CENTURION_CPU_HEADER