/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_COMMON_LITERALS_HPP_
#define CENTURION_COMMON_LITERALS_HPP_

#include <SDL.h>

#include "primitives.hpp"

namespace cen::literals {
inline namespace time_literals {

#if SDL_VERSION_ATLEAST(2, 0, 18)

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> u64ms
{
  return u64ms {static_cast<uint64>(ms)};
}

#else

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> u32ms
{
  return u32ms {static_cast<uint32>(ms)};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

}  // namespace time_literals
}  // namespace cen::literals

#endif  // CENTURION_COMMON_LITERALS_HPP_
