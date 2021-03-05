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

#ifndef CENTURION_CFG_HEADER
#define CENTURION_CFG_HEADER

#include <SDL.h>

/// \addtogroup core
/// \{

/**
 * \def CENTURION_USE_PRAGMA_ONCE
 *
 * \brief This macro indicates whether or not Centurion headers will use
 * `#pragma once` in addition with the traditional include guards. By
 * default, this macro is defined.
 *
 * \since 5.0.0
 */
#define CENTURION_USE_PRAGMA_ONCE

/**
 * \def CENTURION_USE_DEBUG_LOGGING_MACROS
 *
 * \brief This macro indicates whether or not debug-only logging macros will
 * be defined. These can be found in the `log.hpp` header. By default, this
 * macro is defined.
 *
 * \since 5.0.0
 */
#define CENTURION_USE_DEBUG_LOGGING_MACROS

/**
 * \def CENTURION_SDL_VERSION_IS
 *
 * \brief This macro is meant to be used when conditionally including code for a
 * specific version of SDL. It is useful for applying workarounds.
 *
 * \since 5.3.0
 */
#define CENTURION_SDL_VERSION_IS(x, y, z)                      \
  ((SDL_MAJOR_VERSION == (x)) && (SDL_MINOR_VERSION == (y)) && \
   (SDL_PATCHLEVEL == (z)))

/// \} End of group core

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

// Workaround for this enum being completely anonymous in SDL 2.0.10. We include
// this here because multiple files (key_code.hpp and scan_code.hpp) depend on
// this definition.
using SDL_KeyCode = decltype(SDLK_UNKNOWN);

#endif

#endif  // CENTURION_CFG_HEADER