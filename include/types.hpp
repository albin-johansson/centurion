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
 * \file types.hpp
 *
 * \deprecated Since 5.1.0, use more explicit includes instead.
 *
 * \todo Centurion 6: Remove this file.
 */

#ifndef CENTURION_TYPES_HEADER
#define CENTURION_TYPES_HEADER

#include <SDL.h>

#include <array>        // array
#include <chrono>       // duration
#include <cstddef>      // byte
#include <optional>     // optional
#include <type_traits>  // enable_if, is_pointer

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "integers.hpp"
#include "not_null.hpp"
#include "owner.hpp"
#include "time.hpp"
#include "unicode_string.hpp"  // for unicode alias

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

// TODO Centurion 6: Remove this alias.
using font_id [[deprecated]] = std::size_t;

/**
 * \typedef buffer
 *
 * \brief Alias for an array of `std::byte` instances, meant to be used with
 * `pmr` containers.
 *
 * \deprecated Since 5.1.0.
 *
 * \todo Centurion 6: Remove this alias.
 *
 * \since 5.0.0
 */
template <std::size_t size>
using buffer [[deprecated]] = std::array<std::byte, size>;

}  // namespace cen

#endif  // CENTURION_TYPES_HEADER