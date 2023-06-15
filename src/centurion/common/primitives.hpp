/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_COMMON_PRIMITIVES_HPP_
#define CENTURION_COMMON_PRIMITIVES_HPP_

#include <SDL.h>

#include <chrono>    // duration
#include <cstddef>   // size_t
#include <optional>  // optional, nullopt
#include <ratio>     // ratio, milli

#include "traits.hpp"
#include "version.hpp"

namespace cen {

#ifdef NDEBUG
inline constexpr bool is_debug_build = false;
inline constexpr bool is_release_build = true;
#else
inline constexpr bool is_debug_build = true;
inline constexpr bool is_release_build = false;
#endif  // NDEBUG

#ifdef _MSC_VER
inline constexpr bool on_msvc = true;
#else
inline constexpr bool on_msvc = false;
#endif  // _MSC_VER

#ifdef __GNUC__
inline constexpr bool on_gcc = true;
#else
inline constexpr bool on_gcc = false;
#endif  // __GNUC__

#ifdef __clang__
inline constexpr bool on_clang = true;
#else
inline constexpr bool on_clang = false;
#endif  // __clang__

using usize = std::size_t;
using uint = unsigned int;
using ulonglong = unsigned long long int;

using uint8 = Uint8;
using uint16 = Uint16;
using uint32 = Uint32;
using uint64 = Uint64;

using int8 = Sint8;
using int16 = Sint16;
using int32 = Sint32;
using int64 = Sint64;

using unicode_t = uint16;
using unicode32_t = uint32;

template <typename T>
using seconds = std::chrono::duration<T>;

template <typename T>
using millis = std::chrono::duration<T, std::milli>;

template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

using u16ms = millis<uint16>;
using u32ms = millis<uint32>;
using u64ms = millis<uint64>;

template <typename T, usize Size>
using bounded_array_ref = T (&)[Size];

template <typename T, enable_for_pointer_t<T> = 0>
using owner = T;

template <typename T, enable_for_pointer_t<T> = 0>
using maybe_owner = T;

template <typename T>
using maybe = std::optional<T>;

inline constexpr auto nothing = std::nullopt;

}  // namespace cen

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

/* Workaround for the enum being completely anonymous in SDL 2.0.10. Included here because
   multiple files depend on this definition. */
using SDL_KeyCode = decltype(SDLK_UNKNOWN);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

#endif  // CENTURION_COMMON_PRIMITIVES_HPP_
