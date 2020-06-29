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
 * @brief Used for configuring the behaviour of the library.
 * @note You don't need to explicitly include this file!
 * @file centurion_cfg.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 * @since 4.0.0
 */

#ifndef CENTURION_CFG_HEADER
#define CENTURION_CFG_HEADER

//#define CENTURION_HEADER_ONLY

#ifdef CENTURION___DOXYGEN
/**
 * @def CENTURION_HEADER_ONLY
 * @brief Indicates whether or not the header-only mode should be used.
 * @details If defined, the library will be usable without compiling it as a
 * shared library.
 * @note You have to include the source files of the library when using the
 * library in the "header-only" mode.
 * @headerfile centurion_cfg.h
 */
#define CENTURION_HEADER_ONLY
#endif  // CENTURION___DOXYGEN

#endif  // CENTURION_CFG_HEADER