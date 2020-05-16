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

#ifndef CENTURION_ERROR_HEADER
#define CENTURION_ERROR_HEADER

#include "centurion_api.h"
#include "centurion_exception.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * The Error class is a utility for dealing with SDL errors. The main idea is
 * to provide a simple way to combine error messages from the Centurion
 * library and SDL.
 *
 * @since 3.0.0
 */
class Error final {
 public:
  CENTURION_API explicit Error(std::string message);

  CENTURION_NODISCARD
  CENTURION_API std::string core_message() const;

  CENTURION_NODISCARD
  CENTURION_API std::string img_message() const;

  CENTURION_NODISCARD
  CENTURION_API std::string ttf_message() const;

  CENTURION_NODISCARD
  CENTURION_API std::string mix_message() const;

  CENTURION_NODISCARD
  CENTURION_API static CenturionException from_core(std::string message);

  CENTURION_NODISCARD
  CENTURION_API static CenturionException from_img(std::string message);

  CENTURION_NODISCARD
  CENTURION_API static CenturionException from_ttf(std::string message);

  CENTURION_NODISCARD
  CENTURION_API static CenturionException from_mix(std::string message);

  /**
   * Returns a raw string literal that describes the last error. This method
   * will never return null.
   *
   * @return a raw string literal that describes the last error. The empty
   * string is returned if no error has been set.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  CENTURION_DEPRECATED static CZString descriptionf() noexcept;

  /**
   * Returns a string that describes the last error.
   *
   * @return a string that describes the last error.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  CENTURION_DEPRECATED static std::string description() noexcept;

  /**
   * Returns a string that holds the last error message. The returned string
   * will have the format "Error: ...", where ... is the description of the
   * error.
   *
   * @return a string that holds the last error message.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  CENTURION_DEPRECATED static std::string msg() noexcept;

 private:
  std::string m_message;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Error>::value, "Error isn't final!");
#endif

static_assert(std::is_nothrow_destructible<Error>::value,
              "Error isn't nothrow destructible!");

static_assert(!std::is_constructible<Error>::value, "Error is constructible!");
//
// static_assert(!std::is_copy_constructible<Error>::value, "Error is
// copyable!");
//
// static_assert(!std::is_move_constructible<Error>::value, "Error is
// movable!");
//
// static_assert(!std::is_copy_assignable<Error>::value,
//              "Error is copy assignable!");
//
// static_assert(!std::is_move_assignable<Error>::value,
//              "Error is move assignable!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "error.cpp"
#endif

#endif  // CENTURION_ERROR_HEADER
