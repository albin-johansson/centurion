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

#ifndef CENTURION_DETAIL_ANY_EQ_HEADER
#define CENTURION_DETAIL_ANY_EQ_HEADER

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \cond FALSE
namespace cen::detail {

// clang-format off

/**
 * \brief Indicates whether or not any of the supplied values are equal to a
 * specific value.
 *
 * \tparam T the type of the value to look for.
 *
 * \tparam Args the type of the arguments that will be checked.
 *
 * \param value the value to look for.
 * \param args the arguments that will be compared with the value.
 *
 * \return `true` if any of the supplied values are equal to `value`; `false`
 * otherwise.
 *
 * \since 5.1.0
 */
template <typename T, typename... Args>
[[nodiscard]] constexpr auto any_eq(const T& value, Args&&... args)
    noexcept(noexcept( ((value == args) || ...) )) -> bool
{
  return ((value == args) || ...);
}

// clang-format on

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_ANY_EQ_HEADER
