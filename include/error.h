/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
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

#pragma once
#include <string>
#include "centurion_api.h"

namespace centurion {

/**
 * The Error class is a utility for dealing with SDL errors.
 *
 * @since 3.0.0
 */
class CENTURION_API Error final {
 public:
  Error() = delete;

  Error(const Error&) = delete;

  Error(Error&&) = delete;

  Error& operator=(const Error&) = delete;

  Error& operator=(Error&&) = delete;

  /**
   * Returns a raw string literal that describes the last error. This methods will never return
   * null.
   *
   * @return a raw string literal that describes the last error. The empty string is returned if
   * no error has been set.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static const char* descriptionf() noexcept;

  /**
   * Returns a string that describes the last error.
   *
   * @return a string that describes the last error.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::string description() noexcept;

  /**
   * Returns a string that holds the last error message. The returned string will have the format
   * "Error: ...", where ... is the description of the error.
   *
   * @return a string that holds the last error message.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::string msg() noexcept;

};

}
