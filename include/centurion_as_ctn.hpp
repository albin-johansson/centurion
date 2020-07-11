/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
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
 * @file centurion_as_ctn.hpp
 *
 * @brief Convenience header that defines the `::ctn` namespace alias.
 *
 * @details Includes the `centurion.hpp` header whilst also defining a
 * namespace alias for the `::centurion` namespace, `::ctn`.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_AS_CTN_HEADER
#define CENTURION_AS_CTN_HEADER

#include "centurion.hpp"

/**
 * @namespace ctn
 *
 * @brief Alias for `::centurion`.
 *
 * @details This alias can make header files look a bit nicer when dealing with
 * centurion components.
 *
 * @since 4.1.0
 *
 * @headerfile centurion_as_ctn.hpp
 */
namespace ctn = centurion;

#endif  // CENTURION_AS_CTN_HEADER