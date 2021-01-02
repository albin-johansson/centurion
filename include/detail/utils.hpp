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

/**
 * \defgroup misc Miscellaneous
 *
 * \brief Provides miscellaneous components used throughout the library.
 */

#ifndef CENTURION_CENTURION_UTILS_HEADER
#define CENTURION_CENTURION_UTILS_HEADER

#include <SDL.h>

#include <array>        // array
#include <cstring>      // strcmp
#include <sstream>      // ostringstream
#include <string>       // string
#include <type_traits>  // is_enum_v, enable_if_t, true_type, false_type
#include <utility>      // pair

#include "centurion_api.hpp"
#include "exception.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \cond FALSE

/**
 * \namespace cen::detail
 *
 * \brief The main namespace used for implementation details of the library.
 *
 * \warning Do not use anything that resides in this namespace, the contents
 * may change at any time without warning.
 */
namespace detail {

/**
 * \brief Returns a string that represents the memory address of the supplied
 * pointer.
 *
 * \details The empty string is returned if the supplied pointer is null.
 *
 * \tparam T the type of the pointer.
 * \param ptr the pointer that will be converted.
 *
 * \return a string that represents the memory address of the supplied
 * pointer.
 *
 * \since 3.0.0
 */
template <typename T>
[[nodiscard]] auto address_of(T* ptr) -> std::string
{
  if (ptr) {
    std::ostringstream address;
    address << static_cast<const void*>(ptr);
    return address.str();
  } else {
    return "";
  }
}

template <typename T>
using is_owner = std::enable_if_t<std::is_same_v<T, std::true_type>, bool>;

template <typename T>
using is_handle = std::enable_if_t<std::is_same_v<T, std::false_type>, bool>;

template <typename T>
[[nodiscard]] constexpr auto is_owning() noexcept -> bool
{
  return std::is_same_v<T, std::true_type>;
}

}  // namespace detail

/// \endcond

}  // namespace cen

#endif  // CENTURION_CENTURION_UTILS_HEADER