#ifndef CENTURION_CPU_SOURCE
#define CENTURION_CPU_SOURCE

#include "cpu.h"

namespace centurion {
namespace system {

CENTURION_DEF
int CPU::get_cache_line_size() noexcept
{
  return SDL_GetCPUCacheLineSize();
}

CENTURION_DEF
int CPU::get_cores() noexcept
{
  return SDL_GetCPUCount();
}

CENTURION_DEF
bool CPU::has_rdtsc() noexcept
{
  return SDL_HasRDTSC();
}

CENTURION_DEF
bool CPU::has_altivec() noexcept
{
  return SDL_HasAltiVec();
}

CENTURION_DEF
bool CPU::has_mmx() noexcept
{
  return SDL_HasMMX();
}

CENTURION_DEF
bool CPU::has_3dnow() noexcept
{
  return SDL_Has3DNow();
}

CENTURION_DEF
bool CPU::has_sse() noexcept
{
  return SDL_HasSSE();
}

CENTURION_DEF
bool CPU::has_sse2() noexcept
{
  return SDL_HasSSE2();
}

CENTURION_DEF
bool CPU::has_sse3() noexcept
{
  return SDL_HasSSE3();
}

CENTURION_DEF
bool CPU::has_sse41() noexcept
{
  return SDL_HasSSE41();
}

CENTURION_DEF
bool CPU::has_sse42() noexcept
{
  return SDL_HasSSE42();
}

CENTURION_DEF
bool CPU::has_avx() noexcept
{
  return SDL_HasAVX();
}

CENTURION_DEF
bool CPU::has_avx2() noexcept
{
  return SDL_HasAVX2();
}

CENTURION_DEF
bool CPU::has_avx512f() noexcept
{
  return SDL_HasAVX512F();
}

CENTURION_DEF
bool CPU::has_neon() noexcept
{
  return SDL_HasNEON();
}

}  // namespace system
}  // namespace centurion

#endif  // CENTURION_CPU_SOURCE