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

#ifndef CENTURION_EXCEPTION_HEADER
#define CENTURION_EXCEPTION_HEADER

#include <exception>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * A general exception used by the Centurion library.
 *
 * @since 3.0.0
 */
class CenturionException final : public std::exception {
 public:
  /**
   * @since 3.0.0
   */
  CenturionException() = default;

  /**
   * @param what the message of the exception. If the string is null, "N/A" is
   * used.
   * @since 3.0.0
   */
  CENTURION_API
  explicit CenturionException(CZString what) noexcept;

  /**
   * @param what the message of the exception. If the string is empty, "N/A"
   * is used.
   * @since 3.0.0
   */
  CENTURION_API
  explicit CenturionException(std::string what) noexcept;

  CENTURION_API
  CenturionException(const CenturionException& other) noexcept;

  ~CenturionException() noexcept override = default;

  CENTURION_NODISCARD
  CZString what() const noexcept override { return m_what.c_str(); }

 private:
  std::string m_what;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<CenturionException>::value,
              "CenturionException isn't final!");
#endif

static_assert(std::is_default_constructible<CenturionException>::value,
              "CenturionException isn't default constructible!");

static_assert(std::is_nothrow_copy_constructible<CenturionException>::value,
              "CenturionException isn't nothrow copy constructible!");

static_assert(std::is_nothrow_destructible<CenturionException>::value,
              "CenturionException isn't nothrow destructible!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "centurion_exception.cpp"
#endif

#endif  // CENTURION_EXCEPTION_HEADER