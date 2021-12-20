#ifndef CENTURION_CORE_TIME_HPP_
#define CENTURION_CORE_TIME_HPP_

#include <SDL.h>

#include <chrono>  // duration
#include <ratio>   // ratio, milli, micro, nano

#include "../common.hpp"

namespace cen {

template <typename T>
using Seconds = std::chrono::duration<T>;

template <typename T>
using Millis = std::chrono::duration<T, std::milli>;

template <typename T>
using Micros = std::chrono::duration<T, std::micro>;

template <typename T>
using Nanos = std::chrono::duration<T, std::nano>;

template <typename T>
using Minutes = std::chrono::duration<T, std::ratio<60>>;

using U16_Millis = Millis<Uint16>;
using U32_Millis = Millis<Uint32>;
using U64_Millis = Millis<Uint64>;

namespace literals {
inline namespace time_literals {

#if SDL_VERSION_ATLEAST(2, 0, 18)

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> U64_Millis
{
  return U64_Millis{static_cast<Uint64>(ms)};
}

#else

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> U32_Millis
{
  return U32_Millis{static_cast<Uint32>(ms)};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

}  // namespace time_literals
}  // namespace literals

}  // namespace cen

#endif  // CENTURION_CORE_TIME_HPP_
