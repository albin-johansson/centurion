/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_CAST_HEADER
#define CENTURION_CAST_HEADER

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \brief Casts a value to a value of another type.
 *
 * \ingroup misc
 *
 * \details This is the default implementation, which simply attempts to use
 * `static_cast`. The idea is that this function will be specialized for
 * various Centurion and SDL types. This is useful because it isn't always
 * possible to implement conversion operators as members.
 *
 * \tparam To the type of the value that will be converted.
 * \tparam From the type that the value will be casted to.
 *
 * \param from the value that will be converted.
 *
 * \return the result of casting the supplied value to the specified type.
 *
 * \since 5.0.0
 */
template <typename To, typename From>
[[nodiscard]] constexpr auto cast(const From& from) noexcept -> To
{
  return static_cast<To>(from);
}

}  // namespace cen

#endif  // CENTURION_CAST_HEADER
