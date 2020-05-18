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

#ifndef CENTURION_RAM_HEADER
#define CENTURION_RAM_HEADER

#include <SDL.h>

#include "centurion_api.h"

namespace centurion {

/**
 * The RAM class is a utility class that provides information related to,
 * unsurprisingly, the system RAM.
 *
 * @since 3.0.0
 */
class RAM final {
 public:
  RAM() = delete;

  /**
   * Returns the total amount of system RAM in megabytes.
   *
   * @return the total amount of system RAM in megabytes.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int size_mb() noexcept;

  /**
   * Returns the total amount of system RAM in gigabytes.
   *
   * @return the total amount of system RAM in gigabytes.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int size_gb() noexcept;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "ram.cpp"
#endif

#endif  // CENTURION_RAM_HEADER