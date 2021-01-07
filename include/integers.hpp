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

#ifndef CENTURION_INTEGERS_HEADER
#define CENTURION_INTEGERS_HEADER

#include <SDL.h>

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \typedef u64
 *
 * \brief Alias for a 64-bit unsigned integer.
 */
using u64 = Uint64;

/**
 * \typedef u32
 *
 * \brief Alias for a 32-bit unsigned integer.
 */
using u32 = Uint32;

/**
 * \typedef u16
 *
 * \brief Alias for a 16-bit unsigned integer.
 */
using u16 = Uint16;

/**
 * \typedef u8
 *
 * \brief Alias for an 8-bit unsigned integer.
 */
using u8 = Uint8;

/**
 * \typedef i64
 *
 * \brief Alias for a 64-bit signed integer.
 */
using i64 = Sint64;

/**
 * \typedef i32
 *
 * \brief Alias for a 32-bit signed integer.
 */
using i32 = Sint32;

/**
 * \typedef i16
 *
 * \brief Alias for a 16-bit signed integer.
 */
using i16 = Sint16;

/**
 * \typedef i8
 *
 * \brief Alias for an 8-bit signed integer.
 */
using i8 = Sint8;

}  // namespace cen

#endif  // CENTURION_INTEGERS_HEADER
